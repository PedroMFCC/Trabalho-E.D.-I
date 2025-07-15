#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SERVICOS/arvore.h"
#include "FILA/fila.h"
#include "CLIENTE/hash.h"
#include "AGENDAMENTO/lista.h"
#include "HISTORICO/pilha.h"


void menuClientes() {
    iniciaHash();
    carregarClientes("clientes.txt");
    int opcao = 0;
    
    while(opcao != 5) {
        printf("\n----------- MENU CLIENTES -----------\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Buscar Cliente\n");
        printf("3. Atualizar Cliente\n");
        printf("4. Remover Cliente\n");
        printf("5. Voltar\n");
        printf("Sua escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: 
                inserirCliente();
                salvarClientes("clientes.txt");
                break;
            
            case 2:
                buscarCliente();
                break;
            
            case 3:
                atualizarCliente();
                salvarClientes("clientes.txt");
                break;
            
            case 4:
                removerCliente();
                salvarClientes("clientes.txt");
                break;

            case 5:
                printf("\nVoltando ao MENU...\n");
                salvarClientes("clientes.txt");
                break;

            default:
                printf("Opção inválida!\n");
                break;
        }
    }
}

void menuAgendamentos() {
    carregarAgendamentos();
    int opcao = 0;
    while(opcao != 5) {
        printf("\n------ MENU AGENDAMENTOS ------\n");
        printf("1. Agendar novo serviço\n");
        printf("2. Visualizar agendamentos de cliente\n");
        printf("3. Cancelar agendamento\n");
        printf("4. Atualizar status\n");
        printf("5. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();
        
        switch(opcao) {
            case 1:
                criarAgendamento();
                break;
            case 2:
                visualizarAgendamentos();
                break;
            case 3:
                cancelarAgendamento();
                break;
            case 4:
                atualizarStatus();
                break;
            case 5:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
}

void menuFila(){
    carregarFila();

    int opcao = 0;
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
                entrarNaFila();
            break;

            case 2:
                proxAtendimento();
            break;

            case 3:
                visualizarFila();
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
    int opcao = 0;

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
                registrarAtendimento();
            break;

            case 2:
                visualizarHistorico();
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
    int opcao = 0;
    carregarServicos();
    
    while(opcao != 4) {
        printf("\n-----------MENU RELATÓRIO DE SERVIÇOS-----------\n");
        printf("Escolha a opcao desejada:\n");
        printf("1. Adicionar novo tipo de serviço\n");
        printf("2. Buscar um tipo de serviço\n");
        printf("3. Listar os tipos de serviço em ordem alfabética\n");
        printf("4. Voltar\n");
        printf("Sua escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                adicionarServico();
                break;

            case 2:
                buscarServico();
                break;

            case 3:
                listarServicosOrdem();
                break;

            case 4:
                printf("voltando ao MENU...");
                salvarServicos();
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
                menuAgendamentos();
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

    return 0;
}