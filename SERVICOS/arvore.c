#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

NoServico* arvoreServicos = NULL;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura(NoServico *no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

NoServico* novoNo(Servico servico) {
    NoServico* no = (NoServico*)malloc(sizeof(NoServico));
    no->servico = servico;
    no->esq = NULL;
    no->dir = NULL;
    no->altura = 1;
    return no;
}

NoServico* rotacaoDireita(NoServico *y) {
    NoServico *x = y->esq;
    NoServico *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

NoServico* rotacaoEsquerda(NoServico *x) {
    NoServico *y = x->dir;
    NoServico *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

int fatorBalanceamento(NoServico *no) {
    if (no == NULL)
        return 0;
    return altura(no->esq) - altura(no->dir);
}

NoServico* inserirServico(NoServico* no, Servico servico) {
    if (no == NULL)
        return novoNo(servico);

    if (strcmp(servico.tipo, no->servico.tipo) < 0)
        no->esq = inserirServico(no->esq, servico);
    else if (strcmp(servico.tipo, no->servico.tipo) > 0)
        no->dir = inserirServico(no->dir, servico);
    else
        return no;

    no->altura = 1 + max(altura(no->esq), altura(no->dir));

    int balance = fatorBalanceamento(no);

    if (balance > 1 && strcmp(servico.tipo, no->esq->servico.tipo) < 0)
        return rotacaoDireita(no);

    if (balance < -1 && strcmp(servico.tipo, no->dir->servico.tipo) > 0)
        return rotacaoEsquerda(no);

    if (balance > 1 && strcmp(servico.tipo, no->esq->servico.tipo) > 0) {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }

    if (balance < -1 && strcmp(servico.tipo, no->dir->servico.tipo) < 0) {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }

    return no;
}

NoServico* buscarNoServico(NoServico* raiz, const char* tipo) {
    if (raiz == NULL)
        return NULL;

    int cmp = strcmp(tipo, raiz->servico.tipo);
    if (cmp == 0)
        return raiz;
    else if (cmp < 0)
        return buscarNoServico(raiz->esq, tipo);
    else
        return buscarNoServico(raiz->dir, tipo);
}

void emOrdem(NoServico* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("Tipo: %s\n", raiz->servico.tipo);
        printf("Descrição: %s\n", raiz->servico.descricao);
        printf("Preço: R$%.2f\n", raiz->servico.preco);
        printf("-----------------------------\n");
        emOrdem(raiz->dir);
    }
}

void adicionarServico() {
    Servico novo;
    
    printf("\nADICIONAR NOVO SERVIÇO:\n\n");
    printf("Tipo de serviço: ");
    scanf(" %49[^\n]", novo.tipo);
    printf("Descrição: ");
    scanf(" %99[^\n]", novo.descricao);
    printf("Preço médio: ");
    scanf("%f", &novo.preco);
    
    arvoreServicos = inserirServico(arvoreServicos, novo);
    printf("Serviço adicionado com sucesso!\n");
    
    salvarServicos();
}

void buscarServico() {
    char tipo[50];
    printf("\nBUSCAR SERVIÇO:\n\n");
    printf("Tipo de serviço: ");
    scanf(" %49[^\n]", tipo);
    
    NoServico* encontrado = buscarNoServico(arvoreServicos, tipo);
    if (encontrado != NULL) {
        printf("\nServiço encontrado:\n");
        printf("Tipo: %s\n", encontrado->servico.tipo);
        printf("Descrição: %s\n", encontrado->servico.descricao);
        printf("Preço: R$%.2f\n", encontrado->servico.preco);
    } else {
        printf("Serviço não encontrado.\n");
    }
}

void listarServicosOrdem() {
    printf("\nLISTA DE SERVIÇOS (ORDEM ALFABÉTICA):\n\n");
    if (arvoreServicos == NULL) {
        printf("Nenhum serviço cadastrado.\n");
        return;
    }
    emOrdem(arvoreServicos);
}

void salvarServicosEmOrdem(FILE* arquivo, NoServico* no) {
    if (no != NULL) {
        salvarServicosEmOrdem(arquivo, no->esq);
        fprintf(arquivo, "%s;%s;%.2f;", no->servico.tipo, no->servico.descricao, no->servico.preco);
        salvarServicosEmOrdem(arquivo, no->dir);
    }
}

void salvarServicos() {
    FILE* arquivo = fopen("servicos.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir arquivo para escrita!\n");
        return;
    }
    
    salvarServicosEmOrdem(arquivo, arvoreServicos);
    fclose(arquivo);
}

void carregarServicos() {
    FILE* arquivo = fopen("servicos.txt", "r");
    if (!arquivo) {
        printf("Arquivo de serviços não encontrado. Criando novo...\n");
        return;
    }
    
    Servico servico;
    char linha[150];
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, ";")] = 0;
        strcpy(servico.tipo, linha);
        
        if (fgets(linha, sizeof(linha), arquivo) == NULL) break;
        linha[strcspn(linha, ";")] = 0;
        strcpy(servico.descricao, linha);
        
        if (fgets(linha, sizeof(linha), arquivo) == NULL) break;
        servico.preco = atof(linha);
        
        arvoreServicos = inserirServico(arvoreServicos, servico);
    }
    
    fclose(arquivo);
}
