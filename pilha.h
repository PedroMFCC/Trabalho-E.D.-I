#ifndef PILHA_H
#define PILHA_H

typedef struct NoPilha {
    char cpf[15];
    char descricao[101];
    struct NoPilha *prox;
} NoPilha;

typedef struct {
    NoPilha *topo;
} Pilha;

void inicializaPilha(Pilha *pilha);
void empilha(Pilha *pilha, const char *cpf, const char *descricao);
void imprimeHistorico(Pilha *pilha, const char *cpf);

#endif