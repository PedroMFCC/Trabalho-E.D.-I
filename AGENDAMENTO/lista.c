#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

Agendamento* listaAgendamentos = NULL;


void inserirAgendamento(Agendamento novo) {
    Agendamento *novoAgendamento = (Agendamento*)malloc(sizeof(Agendamento));
    if (!novoAgendamento) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    *novoAgendamento = novo;
    novoAgendamento->prox = listaAgendamentos;
    listaAgendamentos = novoAgendamento;
}

void criarAgendamento() {
    Agendamento novo;
    
    printf("\nCRIAR NOVO AGENDAMENTO: \n\n");
    printf("CPF: ");
    scanf(" %14s", novo.cpf);
    printf("Data (dd/mm/aa): ");
    scanf(" %14s", novo.data);
    printf("Horário (hh:mm): ");
    scanf(" %5s", novo.hora);
    printf("Tipo de serviço: ");
    scanf(" %49[^\n]", novo.tipo);
    strcpy(novo.status, "Agendado");
    
    inserirAgendamento(novo);
    printf("Agendamento feito com sucesso!\n");
    
    salvarAgendamentos();
}

void visualizarAgendamentos() {
    char cpf[15];
    printf("\nLISTAR AGENDAMENTOS\n");
    printf("CPF: ");
    scanf(" %14s", cpf);
    
    Agendamento* atual = listaAgendamentos;
    int encontrou = 0;
    
    printf("\nAGENDAMENTOS DO CPF: %s \n", cpf);
    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf) == 0) {
            printf("Data: %s | Hora: %s\n", atual->data, atual->hora);
            printf("Tipo de Serviço: %s\n", atual->tipo);
            printf("Status: %s\n", atual->status);
            printf("-----------------------------\n");
            encontrou = 1;
        }
        atual = atual->prox;
    }
    
    if (!encontrou) {
        printf("Nenhum agendamento encontrado para este CPF.\n");
    }
}

void cancelarAgendamento() {
    char cpf[15], data[15], hora[6];
    
    printf("\nCANCELAR AGENDAMENTO\n");
    printf("CPF: ");
    scanf(" %14s", cpf);
    printf("Data: ");
    scanf(" %14s", data);
    printf("Hora: ");
    scanf(" %5s", hora);
    
    Agendamento* atual = listaAgendamentos;
    int sucesso = 0;
    
    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf) == 0 &&
            strcmp(atual->data, data) == 0 &&
            strcmp(atual->hora, hora) == 0) {
            strcpy(atual->status, "Cancelado");
            sucesso = 1;
            break;
        }
        atual = atual->prox;
    }
    
    if (sucesso) {
        printf("Agendamento cancelado com sucesso!\n");
        salvarAgendamentos();
    } else {
        printf("Não foi possível cancelar o agendamento.\n");
    }
}

void atualizarStatus() {
    char cpf[15], data[15], hora[6], status[MAX_STATUS];
    
    printf("\nATUALIZAR STATUS DE AGENDAMENTO\n");
    printf("CPF: ");
    scanf(" %14s", cpf);
    printf("Data: ");
    scanf(" %14s", data);
    printf("Hora: ");
    scanf(" %5s", hora);
    printf("Novo status (Agendado | Concluído | Cancelado): ");
    scanf(" %24s", status);
    
    Agendamento* atual = listaAgendamentos;
    int sucesso = 0;
    
    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf) == 0 &&
            strcmp(atual->data, data) == 0 &&
            strcmp(atual->hora, hora) == 0) {
            strncpy(atual->status, status, MAX_STATUS - 1);
            atual->status[MAX_STATUS - 1] = '\0';
            sucesso = 1;
            break;
        }
        atual = atual->prox;
    }
    
    if (sucesso) {
        printf("Status do agendamento atualizado com sucesso!\n");
        salvarAgendamentos();
    } else {
        printf("Não foi encontrado este agendamento.\n");
    }
}

void salvarAgendamentos() {
    FILE *arquivo = fopen("agendamento.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir arquivo para escrita!\n");
        return;
    }
    
    Agendamento* atual = listaAgendamentos;
    while (atual != NULL) {
        fprintf(arquivo, "%s;%s;%s;%s;%s\n", 
                atual->cpf, atual->data, atual->hora, 
                atual->tipo, atual->status);
        atual = atual->prox;
    }
    
    fclose(arquivo);
}

void carregarAgendamentos() {
    FILE *arquivo = fopen("agendamento.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo de agendamentos não encontrado.\n");
        return;
    }
    
    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        Agendamento novo;
        
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
        
        token = strtok(NULL, ";");
        if (!token) continue;

        token[strcspn(token, "\n")] = 0;
        strcpy(novo.status, token);
        
        inserirAgendamento(novo);
    }
    
    fclose(arquivo);
}