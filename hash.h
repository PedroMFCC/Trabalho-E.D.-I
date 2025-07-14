#ifndef HASH_H
#define HASH_H

#define N 127

typedef struct CLIENTE {
    char cpf[15];      
    char nome[81];
    char telefone[21];
    char endereco[101];
    struct CLIENTE *prox;
} CLIENTE;

typedef CLIENTE *Hash[N];

int hash(const char *cpf);
void iniciaHash(Hash tabela);
void insereCliente(Hash tabela, CLIENTE cliente);
CLIENTE lerCliente();
CLIENTE *buscarCliente(Hash tabela, const char *cpf);
int removerCliente(Hash tabela, const char *cpf);
void salvarClientes(Hash tabela, const char *arquivo);
void atualizaCliente(Hash tabela);
void carregarClientes(Hash tabela, const char *arquivo);

#endif