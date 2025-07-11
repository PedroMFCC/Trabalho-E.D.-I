#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "fila.h"
#include "hash.h"
#include "lista.h"
#include "pilha.h"


void menuClientes(){

    int opcao = 0;
    while(opcao !=6 ){
        printf("\n-----------MENU CLIENTES-----------\n");
        printf("escolha a opcao desejada:\n1.Inserir Cliente\n2.Buscar Cliente\n3.Remover Cliente\n4.Excluir Cliente\n5.Atualizar Cliente\n6.volar\n");
        printf("sua escolha:");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                insereCliente();
            break;

            case 2:
                buscaCliente();
            break;

            case 3:
                removeCliente();
            break;

            case 4:
                excluiCliente();
            break;

            case 5:
                atualizaCliente();
            break;

            case 6:
                printf("\nVoltando ao ''MENU''\n");
            break;
        }
    }
}

void menuAgendamento(){

}

void menuFila(){

}

void menuHistorico(){

}

void menuRelatorio(){

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