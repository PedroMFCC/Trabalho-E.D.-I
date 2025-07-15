#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#include "hash.h"

PilhaHistorico historicos[N];

void iniciaHistoricos() {
    for (int i = 0; i < N; i++) {
        historicos[i].topo = NULL;
    }
}

void registrarAtendimento() {
    Atendimento novo;
    
    printf("\nREGISTRAR ATENDIMENTO CONCLUÍDO:\n\n");
    printf("CPF do cliente: ");
    scanf(" %14s", novo.cpf);
    printf("Data do atendimento (dd/mm/aa): ");
    scanf(" %14s", novo.data);
    printf("Hora do atendimento (hh:mm): ");
    scanf(" %5s", novo.hora);
    printf("Tipo de serviço: ");
    scanf(" %49[^\n]", novo.tipo);
    getchar();
    printf("Observações: ");
    scanf(" %199[^\n]", novo.observacoes);

    Atendimento *novoAtendimento = (Atendimento*)malloc(sizeof(Atendimento));
    if (!novoAtendimento) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    *novoAtendimento = novo;
    
    int h = hashCPF(novo.cpf);
    novoAtendimento->prox = historicos[h].topo;
    historicos[h].topo = novoAtendimento;
    
    salvarHistoricos();
    printf("Atendimento registrado com sucesso!\n");
}

void visualizarHistorico() {
    char cpf[15];
    printf("\nVISUALIZAR HISTÓRICO DE ATENDIMENTOS:\n\n");
    printf("CPF do cliente: ");
    scanf(" %14s", cpf);
    
    int h = hashCPF(cpf);
    Atendimento *atual = historicos[h].topo;
    int contador = 1;
    
    printf("\nHISTÓRICO DE ATENDIMENTOS PARA CPF: %s\n", cpf);
    printf("----------------------------------------\n");
    
    if (atual == NULL) {
        printf("Nenhum atendimento registrado para este cliente.\n");
        return;
    }
    
    while (atual != NULL) {
        printf("%dº na pilha do histórico\n", contador++);
        printf("Data: %s | Hora: %s\n", atual->data, atual->hora);
        printf("Tipo de serviço: %s\n", atual->tipo);
        printf("Observações: %s\n", atual->observacoes);
        printf("----------------------------------------\n");
        atual = atual->prox;
    }
}

void salvarHistoricos() {
    FILE *arquivo = fopen("historicos.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir arquivo para escrita!\n");
        return;
    }
    
    for (int i = 0; i < N; i++) {
        Atendimento *atual = historicos[i].topo;
        while (atual != NULL) {
            fprintf(arquivo, "%s;%s;%s;%s;%s\n", 
                   atual->cpf, atual->data, atual->hora, 
                   atual->tipo, atual->observacoes);
            atual = atual->prox;
        }
    }
    
    fclose(arquivo);
}

void carregarHistoricos() {
    FILE *arquivo = fopen("historicos.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo de históricos não encontrado. Criando novo...\n");
        return;
    }
    
    char linha[1024];
    while (fgets(linha, sizeof(linha), arquivo)) {
        Atendimento novo;
        
        char *token = strtok(linha, ";");
        if (!token) continue;
        strcpy(novo.cpf, token);
        
        token = strtok(NULL, ";");
        if (!token) continue;
        strcpy(novo.data, token);
        
        token = strtok(NULL, ";");
        if (!token) continue;
        strcpy(novo.hora, token);
        
        token = strtok(NULL, ";");
        if (!token) continue;
        strcpy(novo.tipo, token);
        
        token = strtok(NULL, "\n");
        if (!token) continue;
        strcpy(novo.observacoes, token);
        
        int h = hashCPF(novo.cpf);
        Atendimento *novoAtendimento = (Atendimento*)malloc(sizeof(Atendimento));
        if (!novoAtendimento) continue;
        
        *novoAtendimento = novo;
        novoAtendimento->prox = historicos[h].topo;
        historicos[h].topo = novoAtendimento;
    }
    
    fclose(arquivo);
}