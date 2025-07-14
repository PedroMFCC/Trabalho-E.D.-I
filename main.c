#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "fila.h"
#include "hash.h"
#include "lista.h"
#include "pilha.h"


void menuClientes(){
    Hash tabelaClientes;
    iniciaHash(tabelaClientes);
    carregarClientes(tabelaClientes, "clientes.txt");
    int opcao = 0;
    char cpf[15];
    while(opcao != 5 ){
        printf("\n-----------MENU CLIENTES-----------\n");
        printf("Escolha a opcao desejada:\n");
        printf("1. Inserir Cliente\n");
        printf("2. Buscar Cliente\n");
        printf("3. Remover Cliente\n");
        printf("4. Atualizar Cliente\n");
        printf("5. Voltar\n");
        printf("Sua escolha: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1: 
                CLIENTE cliente = lerCliente();
                insereCliente(tabelaClientes, cliente);
            break;
            
            case 2: 
                printf("Digite o CPF para buscar: ");
                scanf("%14s", cpf);
                getchar();
                CLIENTE *c = buscarCliente(tabelaClientes, cpf);
                if (c) {
                    printf("CPF: %s\nNome: %s\nTelefone: %s\nEndereco: %s\n", c->cpf, c->nome, c->telefone, c->endereco);
                } else {
                    printf("Cliente nao encontrado!\n");
                }
            break;
            
            case 3: 
                printf("Digite o CPF para remover: ");
                scanf("%14s", cpf);
                getchar();
                removerCliente(tabelaClientes, cpf);
                salvarClientes(tabelaClientes, "clientes.txt");
            break;
            
            case 4:
                atualizaCliente(tabelaClientes);
                break;
            case 5:
                printf("\nVoltando ao MENU...\n");
            break;

            default:
                printf("opcao invalida!\n");
                opcao = 0;
            break;
        }
    }
}

void menuAgendamento(){
    ListaAgendamento lista;
    inicializaLista(&lista);
    int opcao = 0;
    AGENDAMENTO ag;
    char cpf[15];

    while(opcao != 5){
        printf("\n-----------MENU AGENDAMENTO-----------\n");
        printf("Escolha a opcao desejada:\n");
        printf("1. Agendar Serviço\n");
        printf("2. Visualizar Agendamentos\n");
        printf("3. Cancelar Agendamento\n");
        printf("4. Buscar Agendamento por CPF\n");
        printf("5. Voltar\n");
        printf("Sua escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
                printf("CPF do cliente: ");
                scanf("%14s", ag.cpfCliente); getchar();
                printf("Serviço: ");
                fgets(ag.servico, sizeof(ag.servico), stdin);
                ag.servico[strcspn(ag.servico, "\n")] = 0;
                printf("Data (DD/MM/AAAA): ");
                scanf("%10s", ag.data); getchar();
                printf("Hora (HH:MM): ");
                scanf("%5s", ag.hora); getchar();
                ag.prox = NULL;
                insereAgendamento(&lista, ag);
            break;

            case 2:
                imprimeAgendamentos(&lista);
            break;

            case 3:
                printf("Digite o CPF para cancelar agendamento: ");
                scanf("%14s", cpf); getchar();
                removeAgendamento(&lista, cpf);
            break;

            case 4:
                printf("Digite o CPF para buscar agendamento: ");
                scanf("%14s", cpf); getchar();
                AGENDAMENTO *a = buscaAgendamento(&lista, cpf);
                if (a) {
                    printf("CPF: %s | Serviço: %s | Data: %s | Hora: %s\n", a->cpfCliente, a->servico, a->data, a->hora);
                } else {
                    printf("Agendamento não encontrado!\n");
                }
            break;

            case 5:
                printf("\nVoltando ao MENU...\n");
            break;

            default:
                printf("opcao invalida!\n");
                opcao = 0;
            break;
        }
    }
}

void menuFila(){
    Fila fila;
    inicializaFila(&fila);
    int opcao = 0;
    char cpf[15];
    while(opcao != 4){
        printf("\n-----------MENU FILA DE ATENDIMENTO-----------\n");
        printf("Escolha a opcao desejada:\n");
        printf("1. Adicionar Cliente à Fila\n");
        printf("2. Próximo atendimento\n");
        printf("3. Visualizar Fila\n");
        printf("4. Voltar\n");
        printf("Sua escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
                printf("Digite o CPF do cliente para adicionar à fila: ");
                scanf("%14s", cpf); getchar();
                enfileira(&fila, cpf);
            break;

            case 2:
                if (desenfileira(&fila, cpf)) {
                    printf("Próximo atendimento: CPF %s\n", cpf);
                }
            break;

            case 3:
                imprimeFila(&fila);
            break;

            case 4:
                printf("\nVoltando ao MENU...\n");
            break;

            default:
                printf("opcao invalida!\n");
                opcao = 0;
            break;
        }
    }
}

void menuHistorico(){
    Pilha historico;
    inicializaPilha(&historico);
    int opcao = 0;
    char cpf[15];
    char descricao[101];
    while(opcao != 3){
        printf("\n-----------MENU HISTÓRICO DE ATENDIMENTOS-----------\n");
        printf("Escolha a opcao desejada:\n");
        printf("1. Registrar um atendimento concluído\n");
        printf("2. Visualizar o histórico de atendimentos de um cliente\n");
        printf("3. Voltar\n");
        printf("Sua escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
                printf("Digite o CPF do cliente: ");
                scanf("%14s", cpf); getchar();
                printf("Descrição do atendimento: ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = 0;
                empilha(&historico, cpf, descricao);
            break;

            case 2:
                printf("Digite o CPF para consultar histórico: ");
                scanf("%14s", cpf); getchar();
                imprimeHistorico(&historico, cpf);
            break;

            case 3:
                printf("\nVoltando ao MENU...\n");
            break;

            default:
                printf("opcao invalida!\n");
                opcao = 0;
            break;
        }
    }
}

void menuRelatorio() {
    ArvoreAVL *arvore = cria_arvore();
    int opcao = 0;
    char nome[MAX_SERVICO];
    Servico servico;
    
    while(opcao != 4) {
        printf("\n-----------MENU RELATÓRIO DE SERVIÇOS-----------\n");
        printf("Escolha a opcao desejada:\n");
        printf("1. Adicionar novo tipo de serviço\n");
        printf("2. Buscar um tipo de serviço\n");
        printf("3. Listar os tipos de serviço em ordem alfabética\n");
        printf("4. Voltar\n");
        printf("Sua escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch(opcao) {
            case 1:
                printf("\n--- Adicionar Serviço ---\n");
                printf("Nome do serviço: ");
                fgets(servico.nome, MAX_SERVICO, stdin);
                servico.nome[strcspn(servico.nome, "\n")] = '\0';
                
                printf("Descrição: ");
                fgets(servico.descricao, MAX_DESCRICAO, stdin);
                servico.descricao[strcspn(servico.descricao, "\n")] = '\0';
                
                printf("Preço: R$");
                scanf("%f", &servico.preco);
                getchar(); // Limpar buffer
                
                if (insere_servico(arvore, servico)) {
                    printf("Serviço adicionado com sucesso!\n");
                } else {
                    printf("Erro ao adicionar serviço.\n");
                }
                break;

            case 2:
                printf("\n--- Buscar Serviço ---\n");
                printf("Nome do serviço: ");
                fgets(nome, MAX_SERVICO, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                
                Servico *s = busca_servico(arvore, nome);
                if (s != NULL) {
                    printf("\nServiço encontrado:\n");
                    printf("Nome: %s\n", s->nome);
                    printf("Descrição: %s\n", s->descricao);
                    printf("Preço: R$%.2f\n", s->preco);
                } else {
                    printf("Serviço não encontrado.\n");
                }
                break;

            case 3:
                printf("\n--- Lista de Serviços (Ordem Alfabética) ---\n");
                if (esta_vazia(arvore)) {
                    printf("Nenhum serviço cadastrado.\n");
                } else {
                    em_ordem(arvore);
                }
                break;

            case 4:
                printf("\nVoltando ao MENU...\n");
                libera_arvore(arvore);
                break;

            default:
                printf("Opção inválida!\n");
                break;
        }
    }
}



int main(){
    int opcao = 0;

    while(opcao != 6){
        printf("\n-----------MENU-----------\n");
        printf("escolha a opcao desejada:\n1.Clientes\n2.Agendamendo de servicos\n3.Fila de Atendimento\n4.Historico de Atendimentos\n5.Relatorio de Servicos\n6.Sair\n");
        printf("sua escolha:");
        
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                menuClientes();
            break;

            case 2:
                menuAgendamento();
            break;

            case 3:
                menuFila();
            break;

            case 4:
                menuHistorico();
            break;

            case 5:
                menuRelatorio();
            break;

            case 6:
                printf("\nOperacao encerrada!");
            break;

            default:
                printf("Opcao invalida!\n");
            break;
        }
    }
}