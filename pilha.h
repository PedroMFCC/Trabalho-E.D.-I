#ifndef PILHA_H
#define PILHA_H

#define MAX_DESCRICAO 100

typedef struct NoPilha {
    char cpf[15];
    char descricao[MAX_DESCRICAO];
    struct NoPilha *prox;
} NoPilha;

typedef struct {
    NoPilha *topo;
} Pilha;

void inicializaPilha(Pilha *pilha);
void empilha(Pilha *pilha, const char *cpf, const char *descricao);
void imprimeHistorico(Pilha *pilha, const char *cpf);
void salvarHistorico(Pilha *pilha, const char *arquivo);
void carregarHistorico(Pilha *pilha, const char *arquivo);

#endif