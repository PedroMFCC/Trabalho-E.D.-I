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
        printf("Escolha a opção desejada:\n");
        printf("1. Inserir Cliente\n");
        printf("2. Buscar Cliente\n");
        printf("3. Remover Cliente\n");
        printf("4. Atualizar Cliente\n");
        printf("5. Voltar\n");
        printf("Sua escolha: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao){
            case 1: {
                CLIENTE cliente = lerCliente();
                insereCliente(tabelaClientes, cliente);
                break;
            }
            case 2: {
                printf("Digite o CPF para buscar: ");
                scanf("%14s", cpf);
                getchar();
                CLIENTE *c = buscarCliente(tabelaClientes, cpf);
                if (c) {
                    printf("CPF: %s\nNome: %s\nTelefone: %s\nEndereco: %s\n", c->cpf, c->nome, c->telefone, c->endereco);
                } else {
                    printf("Cliente não encontrado!\n");
                }
                break;
            }
            case 3: {
                printf("Digite o CPF para remover: ");
                scanf("%14s", cpf);
                getchar();
                removerCliente(tabelaClientes, cpf);
                salvarClientes(tabelaClientes, "clientes.txt");
                break;
            }
            case 4:
                atualizaCliente(tabelaClientes);
                break;
            case 5:
                printf("\nVoltando ao MENU...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
}

void menuAgendamento(){
    int opcao = 0;
    while(opcao != 5){
        printf("\n-----------MENU AGENDAMENTO-----------\n");
        printf("Escolha a opção desejada:\n");
        printf("1. Agendar Serviço\n");
        printf("2. Visualizar Agendamentos\n");
        printf("3. Cancelar Agendamento\n");
        printf("4. Atualizar Agendamento\n");
        printf("5. Voltar\n");
        printf("Sua escolha: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao){
            case 1:
                // Implementar agendamento de serviço
                break;
            case 2:
                // Implementar listagem de agendamentos
                break;
            case 3:
                printf("\nVoltando ao MENU...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
}

void menuFila(){
    //Depois implementar menu
}

void menuHistorico(){
    //Implementar histŕoico dos atendimentos
}

void menuRelatorio(){
    //implementar o relatório de serviços
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
        }
    }
}