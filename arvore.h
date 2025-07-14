#ifndef ARVORE_H
#define ARVORE_H

#define MAX_SERVICO 50
#define MAX_DESCRICAO 100

typedef struct {
    char nome[MAX_SERVICO];
    char descricao[MAX_DESCRICAO];
    float preco;
} Servico;

typedef struct no_avl {
    Servico servico;
    struct no_avl *esq;
    struct no_avl *dir;
    int altura;
} NoAVL;

typedef NoAVL* ArvoreAVL;

// Protótipos das funções
ArvoreAVL* cria_arvore();
void libera_arvore(ArvoreAVL *raiz);
int esta_vazia(ArvoreAVL *raiz);
int altura_no(NoAVL *no);
int fator_balanceamento(NoAVL *no);
void rotacao_LL(ArvoreAVL *raiz);
void rotacao_RR(ArvoreAVL *raiz);
void rotacao_LR(ArvoreAVL *raiz);
void rotacao_RL(ArvoreAVL *raiz);
int insere_servico(ArvoreAVL *raiz, Servico servico);
int remove_servico(ArvoreAVL *raiz, char *nome);
Servico* busca_servico(ArvoreAVL *raiz, char *nome);
void em_ordem(ArvoreAVL *raiz);

#endif