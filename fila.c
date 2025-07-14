#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

void inicializaFila(Fila *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

void enfileira(Fila *fila, const char *cpf) {
    NoFila *novo = (NoFila *)malloc(sizeof(NoFila));
    if (!novo) {
        printf("Erro ao alocar memória para fila!\n");
        return;
    }
    strncpy(novo->cpf, cpf, sizeof(novo->cpf));
    novo->cpf[sizeof(novo->cpf)-1] = '\0';
    novo->prox = NULL;
    if (fila->fim) {
        fila->fim->prox = novo;
    } else {
        fila->inicio = novo;
    }
    fila->fim = novo;
    printf("Cliente %s adicionado à fila!\n", cpf);
}

int desenfileira(Fila *fila, char *cpf) {
    if (!fila->inicio) {
        printf("Fila vazia!\n");
        return 0;
    }
    NoFila *remover = fila->inicio;
    strncpy(cpf, remover->cpf, 15);
    cpf[14] = '\0';
    fila->inicio = remover->prox;
    if (!fila->inicio) fila->fim = NULL;
    free(remover);
    return 1;
}

void imprimeFila(Fila *fila) {
    NoFila *atual = fila->inicio;
    if (!atual) {
        printf("Fila vazia!\n");
        return;
    }
    printf("Fila de atendimento:\n");
    while (atual) {
        printf("CPF: %s\n", atual->cpf);
        atual = atual->prox;
    }
}