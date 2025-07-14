#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

void inicializaPilha(Pilha *pilha) {
    pilha->topo = NULL;
}

void empilha(Pilha *pilha, const char *cpf, const char *descricao) {
    NoPilha *novo = (NoPilha *)malloc(sizeof(NoPilha));
    if (!novo) {
        printf("Erro ao alocar memória para histórico!\n");
        return;
    }
    
    strncpy(novo->cpf, cpf, sizeof(novo->cpf));
    novo->cpf[sizeof(novo->cpf)-1] = '\0';
    strncpy(novo->descricao, descricao, sizeof(novo->descricao));
    novo->descricao[sizeof(novo->descricao)-1] = '\0';
    novo->prox = pilha->topo;
    pilha->topo = novo;
    
    // Salva no arquivo
    salvarHistorico(pilha, "historico.txt");
    printf("Atendimento registrado!\n");
}

void imprimeHistorico(Pilha *pilha, const char *cpf) {
    NoPilha *atual = pilha->topo;
    int encontrou = 0;
    
    while (atual) {
        if (strcmp(atual->cpf, cpf) == 0) {
            printf("CPF: %s | Descrição: %s\n", atual->cpf, atual->descricao);
            encontrou = 1;
        }
        atual = atual->prox;
    }
    
    if (!encontrou) {
        printf("Nenhum atendimento encontrado para o CPF informado.\n");
    }
}

void salvarHistorico(Pilha *pilha, const char *arquivo) {
    FILE *arq = fopen(arquivo, "w");
    if (!arq) {
        printf("Erro ao abrir arquivo para salvar histórico!\n");
        return;
    }
    
    NoPilha *atual = pilha->topo;
    while (atual) {
        fprintf(arq, "%s;%s\n", atual->cpf, atual->descricao);
        atual = atual->prox;
    }
    
    fclose(arq);
}

void carregarHistorico(Pilha *pilha, const char *arquivo) {
    inicializaPilha(pilha);
    FILE *arq = fopen(arquivo, "r");
    if (!arq) {
        printf("Arquivo de histórico não encontrado. Um novo será criado.\n");
        return;
    }
    
    char cpf[15];
    char descricao[MAX_DESCRICAO];
    
    // Lê do fim para o início para manter a ordem correta na pilha
    // Primeiro conta quantos registros existem
    int count = 0;
    while (fscanf(arq, "%14[^;];%99[^\n]\n", cpf, descricao) == 2) {
        count++;
    }
    
    // Reposiciona no início
    rewind(arq);
    
    // Cria um array temporário para armazenar na ordem inversa
    NoPilha **temp = (NoPilha **)malloc(count * sizeof(NoPilha *));
    if (!temp) {
        fclose(arq);
        printf("Erro ao alocar memória para carregar histórico!\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        if (fscanf(arq, "%14[^;];%99[^\n]\n", cpf, descricao) != 2) {
            break;
        }
        
        NoPilha *novo = (NoPilha *)malloc(sizeof(NoPilha));
        if (!novo) {
            // Libera memória alocada até agora
            for (int j = 0; j < i; j++) {
                free(temp[j]);
            }
            free(temp);
            fclose(arq);
            printf("Erro ao alocar memória para carregar histórico!\n");
            return;
        }
        
        strcpy(novo->cpf, cpf);
        strcpy(novo->descricao, descricao);
        novo->prox = NULL;
        temp[i] = novo;
    }
    
    // Empilha na ordem inversa
    for (int i = count - 1; i >= 0; i--) {
        temp[i]->prox = pilha->topo;
        pilha->topo = temp[i];
    }
    
    free(temp);
    fclose(arq);
}