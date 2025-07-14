#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

void inicializaPilha(Pilha *pilha) {
    pilha->topo = NULL;
}

void empilha(Pilha *pilha, const char *cpf, const char *descricao) {
    NoPilha *novo = (NoPilha *)malloc(sizeof(NoPilha));
    if (!novo) {
        printf("Erro ao alocar memória para histórico!\n");
        return;
    }
    strncpy(novo->cpf, cpf, sizeof(novo->cpf));
    novo->cpf[sizeof(novo->cpf)-1] = '\0';
    strncpy(novo->descricao, descricao, sizeof(novo->descricao));
    novo->descricao[sizeof(novo->descricao)-1] = '\0';
    novo->prox = pilha->topo;
    pilha->topo = novo;
    printf("Atendimento registrado!\n");
}

void imprimeHistorico(Pilha *pilha, const char *cpf) {
    NoPilha *atual = pilha->topo;
    int encontrou = 0;
    while (atual) {
        if (strcmp(atual->cpf, cpf) == 0) {
            printf("CPF: %s | Descrição: %s\n", atual->cpf, atual->descricao);
            encontrou = 1;
        }
        atual = atual->prox;
    }
    if (!encontrou) {
        printf("Nenhum atendimento encontrado para o CPF informado.\n");
    }
}