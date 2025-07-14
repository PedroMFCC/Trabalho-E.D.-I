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
        printf("CPF: %s | Serviço: %s | Data: %s | Hora: %s\n", atual->cpfCliente, atual->servico, atual->data, atual->hora);
        atual = atual->prox;
    }
}