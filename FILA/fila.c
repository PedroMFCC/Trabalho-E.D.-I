#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

FilaAtendimento fila = {NULL, NULL};

void limparFila() {
    while (fila.inicio != NULL) {
        NoFila* temp = fila.inicio;
        fila.inicio = fila.inicio->prox;
        free(temp);
    }
    fila.fim = NULL;
}

void carregarFila() {
    FILE* arquivo = fopen("fila.txt", "r");
    if (!arquivo) return;  
    
    char linha[50];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\n")] = 0;
        
        char* token = strtok(linha, ";");
        if (!token) continue;
        
        NoFila* novo = malloc(sizeof(NoFila));
        if (!novo) {
            fclose(arquivo);
            return;
        }
        
        strncpy(novo->cpf, token, 14);
        novo->cpf[14] = '\0';
        
        token = strtok(NULL, ";");
        if (!token) {
            free(novo);
            continue;
        }
        
        strncpy(novo->tipo, token, 9);
        novo->tipo[9] = '\0';
        novo->prox = NULL;
        
        if (fila.fim == NULL) {
            fila.inicio = novo;
            fila.fim = novo;
        } else {
            fila.fim->prox = novo;
            fila.fim = novo;
        }
    }
    fclose(arquivo);
}

void salvarFila() {
    FILE* arquivo = fopen("fila.txt", "w");
    if (!arquivo) {
        printf("Erro ao salvar fila no arquivo!\n");
        return;
    }
    
    NoFila* atual = fila.inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%s;%s\n", atual->cpf, atual->tipo);
        atual = atual->prox;
    }
    
    fclose(arquivo);
}

void entrarNaFila() {
    char cpf[15];
    char tipo[10];

    printf("CPF do cliente: ");
    scanf(" %14s", cpf);
    getchar();

    printf("Tipo de atendimento (Agendado ou Avulso): ");
    scanf(" %9s", tipo);
    getchar();

    NoFila* novo = malloc(sizeof(NoFila));
    if (!novo) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    strcpy(novo->cpf, cpf);
    strncpy(novo->tipo, tipo, 9);
    novo->tipo[9] = '\0';
    novo->prox = NULL;

    if (fila.fim == NULL) {
        fila.inicio = novo;
        fila.fim = novo;
    } else {
        fila.fim->prox = novo;
        fila.fim = novo;
    }

    salvarFila();
    printf("Cliente inserido na fila com sucesso.\n");
}

void proxAtendimento() {
    if (fila.inicio == NULL) {
        printf("A fila está vazia.\n");
        return;
    }

    NoFila* atendido = fila.inicio;
    printf("Chamando próximo da fila:\n");
    printf("CPF: %s | Tipo: %s\n", atendido->cpf, atendido->tipo);
    
    fila.inicio = atendido->prox;
    if (fila.inicio == NULL) {
        fila.fim = NULL;
    }
    
    free(atendido);
    salvarFila();
}

void visualizarFila() {
    printf("\nFILA DE ATENDIMENTO:\n");
    
    if (fila.inicio == NULL) {
        printf("Fila vazia.\n");
        return;
    }

    NoFila* atual = fila.inicio;
    int posicao = 1;
    while (atual != NULL) {
        printf("%d. CPF: %s | Tipo: %s\n", posicao++, atual->cpf, atual->tipo);
        atual = atual->prox;
    }
}