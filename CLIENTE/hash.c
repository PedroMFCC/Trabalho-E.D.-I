#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

Cliente* tabelaClientes[N];

int hashCPF(const char* cpf) {
    int soma = 0;
    for (int i = 0; cpf[i] != '\0'; i++)
        soma = soma + cpf[i];
    return soma % N;
}

void iniciaHash() {
    for (int i = 0; i < N; i++) {
        tabelaClientes[i] = NULL;
    }
}

void inserirCliente() {
    Cliente novoCliente;
    
    printf("\nCADASTRAR NOVO CLIENTE: \n\n");
    printf("CPF: ");
    scanf(" %14s", novoCliente.cpf);
    printf("Nome: ");
    scanf(" %99[^\n]", novoCliente.nome);
    printf("Telefone: ");
    scanf(" %19s", novoCliente.telefone);
    printf("Endereço: ");
    scanf(" %99[^\n]", novoCliente.endereco);
    novoCliente.prox = NULL;

    int h = hashCPF(novoCliente.cpf);
    Cliente *atual = tabelaClientes[h];


    while(atual != NULL) {
        if(strcmp(atual->cpf, novoCliente.cpf) == 0) {
            printf("Erro: CPF já existente.\n");
            return;
        }
        atual = atual->prox;
    }


    Cliente* novo = malloc(sizeof(Cliente));
    *novo = novoCliente;
    novo->prox = tabelaClientes[h];
    tabelaClientes[h] = novo;

    printf("Cliente cadastrado com sucesso.\n");
}

void buscarCliente() {
    char cpf[15];
    printf("\nBUSCAR CLIENTE: \n\n");
    printf("CPF: ");
    scanf(" %14s", cpf);

    int h = hashCPF(cpf);
    Cliente *atual = tabelaClientes[h];

    while(atual != NULL) {
        if(strcmp(atual->cpf, cpf) == 0) {
            printf("\nCliente encontrado:\n");
            printf("CPF: %s\n", atual->cpf);
            printf("Nome: %s\n", atual->nome);
            printf("Telefone: %s\n", atual->telefone);
            printf("Endereço: %s\n", atual->endereco);
            return;
        }
        atual = atual->prox;
    }

    printf("Cliente não encontrado.\n");
}

void removerCliente() {
    char cpf[15];
    printf("\nREMOVER CLIENTE: \n\n");
    printf("CPF: ");
    scanf(" %14s", cpf);

    int h = hashCPF(cpf);
    Cliente *atual = tabelaClientes[h];
    Cliente *anterior = NULL;

    while(atual != NULL) {
        if(strcmp(atual->cpf, cpf) == 0) {
            if(anterior == NULL) {
                tabelaClientes[h] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Cliente removido com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Cliente não encontrado.\n");
}

void atualizarCliente() {
    char cpf[15];
    printf("\nATUALIZAR DADOS DE CLIENTE: \n\n");
    printf("CPF: ");
    scanf(" %14s", cpf);

    int h = hashCPF(cpf);
    Cliente *atual = tabelaClientes[h];

    while(atual != NULL) {
        if(strcmp(atual->cpf, cpf) == 0) {
            printf("Novo nome (atual: %s): ", atual->nome);
            scanf(" %99[^\n]", atual->nome);
            printf("Novo telefone (atual: %s): ", atual->telefone);
            scanf(" %19s", atual->telefone);
            printf("Novo endereço (atual: %s): ", atual->endereco);
            scanf(" %99[^\n]", atual->endereco);
            
            printf("Cliente atualizado com sucesso.\n");
            return;
        }
        atual = atual->prox;
    }

    printf("Cliente não encontrado.\n");
}

void salvarClientes(const char *filename) {
    FILE *file = fopen(filename, "w");
    if(file == NULL) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return;
    }
    
    for(int i = 0; i < N; i++) {
        Cliente *atual = tabelaClientes[i];
        while(atual != NULL) {
            fprintf(file, "%s;%s;%s;%s;\n", 
                   atual->cpf, atual->nome, atual->telefone, atual->endereco);
            atual = atual->prox;
        }
    }
    
    fclose(file);
}

void carregarClientes(const char *filename) {
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        printf("Arquivo de clientes não encontrado. Criando novo...\n");
        return;
    }
    
    Cliente cliente;
    
    while(fscanf(file, " %14[^;]", cliente.cpf) == 1) {
        fscanf(file, " %99[^;]", cliente.nome);
        fscanf(file, " %19[^;]", cliente.telefone);
        fscanf(file, " %99[^;]", cliente.endereco);
        cliente.prox = NULL;
        
        int h = hashCPF(cliente.cpf);
        Cliente* novo = malloc(sizeof(Cliente));
        *novo = cliente;
        novo->prox = tabelaClientes[h];
        tabelaClientes[h] = novo;
    }
    
    fclose(file);
}