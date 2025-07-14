#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

void inicializaLista(ListaAgendamento *lista) {
    lista->inicio = NULL;
}

void insereAgendamento(ListaAgendamento *lista, AGENDAMENTO ag) {
    AGENDAMENTO *novo = (AGENDAMENTO *)malloc(sizeof(AGENDAMENTO));
    if (!novo) {
        printf("Erro ao alocar memória para agendamento!\n");
        return;
    }
    
    *novo = ag;
    novo->prox = lista->inicio;
    lista->inicio = novo;
    
    // Salva no arquivo
    salvarAgendamentos(lista, "agendamentos.txt");
    printf("Agendamento inserido com sucesso!\n");
}

AGENDAMENTO *buscaAgendamento(ListaAgendamento *lista, const char *cpf) {
    AGENDAMENTO *atual = lista->inicio;
    while (atual) {
        if (strcmp(atual->cpfCliente, cpf) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

int removeAgendamento(ListaAgendamento *lista, const char *cpf) {
    AGENDAMENTO *atual = lista->inicio;
    AGENDAMENTO *anterior = NULL;
    
    while (atual) {
        if (strcmp(atual->cpfCliente, cpf) == 0) {
            if (anterior) {
                anterior->prox = atual->prox;
            } else {
                lista->inicio = atual->prox;
            }
            free(atual);
            
            // Atualiza arquivo
            salvarAgendamentos(lista, "agendamentos.txt");
            printf("Agendamento removido com sucesso!\n");
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    
    printf("Agendamento não encontrado!\n");
    return 0;
}

void imprimeAgendamentos(ListaAgendamento *lista) {
    AGENDAMENTO *atual = lista->inicio;
    if (!atual) {
        printf("Nenhum agendamento encontrado.\n");
        return;
    }
    
    while (atual) {
        printf("CPF: %s | Serviço: %s | Data: %s | Hora: %s\n", 
               atual->cpfCliente, atual->servico, atual->data, atual->hora);
        atual = atual->prox;
    }
}

void salvarAgendamentos(ListaAgendamento *lista, const char *arquivo) {
    FILE *arq = fopen(arquivo, "w");
    if (!arq) {
        printf("Erro ao abrir arquivo para salvar agendamentos!\n");
        return;
    }
    
    AGENDAMENTO *atual = lista->inicio;
    while (atual) {
        fprintf(arq, "%s;%s;%s;%s\n", 
                atual->cpfCliente, atual->servico, atual->data, atual->hora);
        atual = atual->prox;
    }
    
    fclose(arq);
}

void carregarAgendamentos(ListaAgendamento *lista, const char *arquivo) {
    inicializaLista(lista);
    FILE *arq = fopen(arquivo, "r");
    if (!arq) {
        printf("Arquivo de agendamentos não encontrado. Um novo será criado.\n");
        return;
    }
    
    AGENDAMENTO ag;
    while (fscanf(arq, "%14[^;];%50[^;];%10[^;];%5[^\n]\n", 
                  ag.cpfCliente, ag.servico, ag.data, ag.hora) == 4) {
        ag.prox = NULL;
        insereAgendamento(lista, ag);
    }
    
    fclose(arq);
}