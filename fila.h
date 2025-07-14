#ifndef FILA_H
#define FILA_H

typedef struct NoFila {
    char cpf[15];
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
} Fila;

void inicializaFila(Fila *fila);
void enfileira(Fila *fila, const char *cpf);
int desenfileira(Fila *fila, char *cpf);
void imprimeFila(Fila *fila);

#endif