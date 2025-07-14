#ifndef HASH_H
#define HASH_H

#define N 127

typedef struct{
    char cpf[15];
    char nome[100];
    char telefone[20];
    char endereco[100];
    struct Cliente* prox;
} Cliente;

extern Cliente* tabelaClientes[N];

int hashCPF(const char* cpf);
void iniciaHash();
void inserirCliente();
void buscarCliente();
void removerCliente();
void atualizarCliente();
void salvarClientes(const char *filename);
void carregarClientes(const char *filename);

#endif