#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"



int hash(const char *cpf){
    int h = 0;

    for(int i = 0; cpf[i] != '\0'; i++){
        h = (h + cpf[i]) % N;
    }

    return h;
}

void iniciaHash(Hash tabela){
    for(int i = 0; i < N; i++){
        tabela[i] = NULL;
    }
}

CLIENTE lerCliente(){
    CLIENTE cliente;

    getchar();
    printf("CPF do cliente:");
    scanf("%14[^\n]", cliente.cpf);
    getchar();
    printf("Nome do cliente:");
    scanf("%80[\n]", cliente.nome);
    getchar();
    printf("Telefone do cliente:");
    scanf("%20[\n]", cliente.telefone);
    getchar();
    scanf("%100[\n]", cliente.endereco);
    getchar();
    printf("\n----------------------\n");

    return cliente;
}

void insereCliente(Hash tabela, CLIENTE cliente){
    FILE *arq = fopen("clientes.txt", "a");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de clientes\n");
        return;
    }

    int idx = hash(cliente.cpf);

    CLIENTE *atual = tabela[idx];
    while (atual) {
        if (strcmp(atual->cpf, cliente.cpf) == 0) {
            printf("Cliente já cadastrado!\n");
            return;
        }
        atual = atual->prox;
    }

    CLIENTE *novo = (CLIENTE *)malloc(sizeof(CLIENTE));
    if (!novo) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    *novo = cliente;
    novo->prox = tabela[idx];
    tabela[idx] = novo;

    
    fprintf(arq, "%s;%s;%s;%s\n", cliente.cpf, cliente.nome, cliente.telefone, cliente.endereco);
    fclose(arq);

    printf("Cliente inserido com sucesso!\n");
}

CLIENTE *buscarCliente(Hash tabela, const char *cpf) {
    int idx = hash(cpf);
    CLIENTE *atual = tabela[idx];
    while (atual) {
        if (strcmp(atual->cpf, cpf) == 0) {
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
    while (atual) {
        if (strcmp(atual->cpf, cpf) == 0) {
            if (anterior) {
                anterior->prox = atual->prox;
            } else {
                tabela[idx] = atual->prox;
            }
            free(atual);
            printf("Cliente removido com sucesso!\n");
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Cliente não encontrado!\n");
    return 0;
}

void salvarClientes(Hash tabela, const char *arquivo) {
    FILE *arq = fopen(arquivo, "w");
    if (!arq) {
        printf("Erro ao abrir o arquivo para salvar clientes.\n");
        return;
    }
    
    for (int i = 0; i < N; i++) {
        CLIENTE *atual = tabela[i];
        while (atual) {
            fprintf(arq, "%s;%s;%s;%s\n", atual->cpf, atual->nome, atual->telefone, atual->endereco);
            atual = atual->prox;
        }
    }
    fclose(arq);
}

void atualizaCliente(Hash tabela) {
    char cpf[15];
    printf("Digite o CPF do cliente para atualizar: ");
    scanf("%14s", cpf);
    getchar();

    CLIENTE *cliente = buscarCliente(tabela, cpf);
    if (!cliente) {
        printf("Cliente não encontrado!\n");
        return;
    }

    printf("Novo nome (deixe vazio para manter): ");
    char nome[81];
    fgets(nome, sizeof(nome), stdin);
    if (nome[0] != '\n') {
        nome[strcspn(nome, "\n")] = 0;
        strncpy(cliente->nome, nome, sizeof(cliente->nome));
    }

    printf("Novo telefone (deixe vazio para manter): ");
    char telefone[21];
    fgets(telefone, sizeof(telefone), stdin);
    if (telefone[0] != '\n') {
        telefone[strcspn(telefone, "\n")] = 0;
        strncpy(cliente->telefone, telefone, sizeof(cliente->telefone));
    }

    printf("Novo endereço (deixe vazio para manter): ");
    char endereco[101];
    fgets(endereco, sizeof(endereco), stdin);
    if (endereco[0] != '\n') {
        endereco[strcspn(endereco, "\n")] = 0;
        strncpy(cliente->endereco, endereco, sizeof(cliente->endereco));
    }

    salvarClientes(tabela, "clientes.txt");
    printf("Cliente atualizado com sucesso!\n");
}

void carregarClientes(Hash tabela, const char *arquivo) {
    iniciaHash(tabela);
    FILE *arq = fopen(arquivo, "r");
    if (!arq) return;
    CLIENTE cliente;
    while (fscanf(arq, "%14[^;];%80[^;];%20[^;];%100[^\n]\n", cliente.cpf, cliente.nome, cliente.telefone, cliente.endereco) == 4) {
        cliente.prox = NULL;
        insereCliente(tabela, cliente);
    }
    fclose(arq);
}


