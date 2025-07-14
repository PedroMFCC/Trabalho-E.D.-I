#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int hash(const char *cpf) {
    int h = 0;
    for(int i = 0; cpf[i] != '\0'; i++) {
        h = (h + cpf[i]) % N;
    }
    return h;
}

void iniciaHash(Hash tabela) {
    for(int i = 0; i < N; i++) {
        tabela[i] = NULL;
    }
}

CLIENTE lerCliente() {
    CLIENTE cliente;
    printf("CPF do cliente: ");
    scanf("%14s", cliente.cpf);
    getchar();
    printf("Nome do cliente: ");
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0';
    printf("Telefone do cliente: ");
    fgets(cliente.telefone, sizeof(cliente.telefone), stdin);
    cliente.telefone[strcspn(cliente.telefone, "\n")] = '\0';
    printf("Endereço do cliente: ");
    fgets(cliente.endereco, sizeof(cliente.endereco), stdin);
    cliente.endereco[strcspn(cliente.endereco, "\n")] = '\0';
    return cliente;
}

void insereCliente(Hash tabela, CLIENTE cliente) {
    int idx = hash(cliente.cpf);
    CLIENTE *atual = tabela[idx];
    
    while(atual != NULL) {
        if(strcmp(atual->cpf, cliente.cpf) == 0) {
            printf("Cliente já cadastrado!\n");
            return;
        }
        atual = atual->prox;
    }
    
    CLIENTE *novo = (CLIENTE*)malloc(sizeof(CLIENTE));
    if(novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    *novo = cliente;
    novo->prox = tabela[idx];
    tabela[idx] = novo;
    
    // Salva no arquivo
    FILE *arq = fopen("clientes.txt", "a");
    if(arq == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    fprintf(arq, "%s;%s;%s;%s\n", cliente.cpf, cliente.nome, cliente.telefone, cliente.endereco);
    fclose(arq);
    printf("Cliente cadastrado com sucesso!\n");
}

CLIENTE *buscarCliente(Hash tabela, const char *cpf) {
    int idx = hash(cpf);
    CLIENTE *atual = tabela[idx];
    
    while(atual != NULL) {
        if(strcmp(atual->cpf, cpf) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

int removerCliente(Hash tabela, const char *cpf) {
    int idx = hash(cpf);
    CLIENTE *atual = tabela[idx];
    CLIENTE *anterior = NULL;
    
    while(atual != NULL) {
        if(strcmp(atual->cpf, cpf) == 0) {
            if(anterior == NULL) {
                tabela[idx] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            
            // Atualiza arquivo
            salvarClientes(tabela, "clientes.txt");
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return 0;
}

void salvarClientes(Hash tabela, const char *arquivo) {
    FILE *arq = fopen(arquivo, "w");
    if(arq == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    for(int i = 0; i < N; i++) {
        CLIENTE *atual = tabela[i];
        while(atual != NULL) {
            fprintf(arq, "%s;%s;%s;%s\n", atual->cpf, atual->nome, atual->telefone, atual->endereco);
            atual = atual->prox;
        }
    }
    fclose(arq);
}

void atualizaCliente(Hash tabela) {
    char cpf[15];
    printf("Digite o CPF do cliente: ");
    scanf("%14s", cpf);
    getchar();
    
    CLIENTE *cliente = buscarCliente(tabela, cpf);
    if(cliente == NULL) {
        printf("Cliente não encontrado!\n");
        return;
    }
    
    printf("Novo nome (atual: %s): ", cliente->nome);
    fgets(cliente->nome, sizeof(cliente->nome), stdin);
    cliente->nome[strcspn(cliente->nome, "\n")] = '\0';
    
    printf("Novo telefone (atual: %s): ", cliente->telefone);
    fgets(cliente->telefone, sizeof(cliente->telefone), stdin);
    cliente->telefone[strcspn(cliente->telefone, "\n")] = '\0';
    
    printf("Novo endereço (atual: %s): ", cliente->endereco);
    fgets(cliente->endereco, sizeof(cliente->endereco), stdin);
    cliente->endereco[strcspn(cliente->endereco, "\n")] = '\0';
    
    salvarClientes(tabela, "clientes.txt");
    printf("Cliente atualizado com sucesso!\n");
}

void carregarClientes(Hash tabela, const char *arquivo) {
    iniciaHash(tabela);
    FILE *arq = fopen(arquivo, "r");
    if(arq == NULL) {
        printf("Arquivo de clientes não encontrado. Um novo será criado.\n");
        return;
    }
    
    CLIENTE cliente;
    while(fscanf(arq, "%14[^;];%80[^;];%20[^;];%100[^\n]\n", 
          cliente.cpf, cliente.nome, cliente.telefone, cliente.endereco) == 4) {
        insereCliente(tabela, cliente);
    }
    fclose(arq);
}