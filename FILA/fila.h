#ifndef FILA_H
#define FILA_H

typedef struct NoFila {
    char cpf[15];
    char tipo[10];
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
} FilaAtendimento;

void entrarNaFila();
void proxAtendimento();
void visualizarFila();
void salvarFila();
void carregarFila();

#endif