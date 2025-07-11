#ifndef HASH_H
#define HASH_H

#define TAM 127 

typedef struct {
    char cpf[15];      
    char nome[81];
    char telefone[21];
    char endereco[101];
} CLIENTE;

typedef struct Node {
    CLIENTE cliente;
    struct Node *prox;
} Node;

typedef Node *Hash[TAM];



void iniciaHash(Hash tabela);
void insereCliente();
CLIENTE *buscarCliente(Hash tabela, const char *cpf)

#endif