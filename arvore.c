#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

ArvoreAVL* cria_arvore() {
    ArvoreAVL *raiz = (ArvoreAVL*)malloc(sizeof(ArvoreAVL));
    if(raiz != NULL) {
        *raiz = NULL;
    }
    return raiz;
}

void libera_no(NoAVL *no) {
    if(no == NULL) return;
    libera_no(no->esq);
    libera_no(no->dir);
    free(no);
}

void libera_arvore(ArvoreAVL *raiz) {
    if(raiz == NULL) return;
    libera_no(*raiz);
    free(raiz);
}

int esta_vazia(ArvoreAVL *raiz) {
    if(raiz == NULL) return 1;
    return (*raiz == NULL);
}

int altura_no(NoAVL *no) {
    if(no == NULL) return -1;
    return no->altura;
}

int fator_balanceamento(NoAVL *no) {
    return altura_no(no->esq) - altura_no(no->dir);
}

int maior(int x, int y) {
    return (x > y) ? x : y;
}

void rotacao_LL(ArvoreAVL *raiz) {
    NoAVL *no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;
    (*raiz)->altura = maior(altura_no((*raiz)->esq), altura_no((*raiz)->dir)) + 1;
    no->altura = maior(altura_no(no->esq), (*raiz)->altura) + 1;
    *raiz = no;
}

void rotacao_RR(ArvoreAVL *raiz) {
    NoAVL *no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = *raiz;
    (*raiz)->altura = maior(altura_no((*raiz)->esq), altura_no((*raiz)->dir)) + 1;
    no->altura = maior(altura_no(no->dir), (*raiz)->altura) + 1;
    *raiz = no;
}

void rotacao_LR(ArvoreAVL *raiz) {
    rotacao_RR(&(*raiz)->esq);
    rotacao_LL(raiz);
}

void rotacao_RL(ArvoreAVL *raiz) {
    rotacao_LL(&(*raiz)->dir);
    rotacao_RR(raiz);
}

int insere_servico(ArvoreAVL *raiz, Servico servico) {
    int res;
    if(*raiz == NULL) {
        NoAVL *novo = (NoAVL*)malloc(sizeof(NoAVL));
        if(novo == NULL) return 0;
        novo->servico = servico;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        
        // Atualiza arquivo
        FILE *arq = fopen("servicos.txt", "a");
        if(arq != NULL) {
            fprintf(arq, "%s;%s;%.2f\n", servico.nome, servico.descricao, servico.preco);
            fclose(arq);
        }
        return 1;
    }
    
    NoAVL *atual = *raiz;
    if(strcmp(servico.nome, atual->servico.nome) < 0) {
        if((res = insere_servico(&(atual->esq), servico)) == 1) {
            if(fator_balanceamento(atual) >= 2) {
                if(strcmp(servico.nome, (*raiz)->esq->servico.nome) < 0) {
                    rotacao_LL(raiz);
                } else {
                    rotacao_LR(raiz);
                }
            }
        }
    } else if(strcmp(servico.nome, atual->servico.nome) > 0) {
        if((res = insere_servico(&(atual->dir), servico)) == 1) {
            if(fator_balanceamento(atual) <= -2) {
                if(strcmp(servico.nome, (*raiz)->dir->servico.nome) > 0) {
                    rotacao_RR(raiz);
                } else {
                    rotacao_RL(raiz);
                }
            }
        }
    } else {
        printf("Serviço já existe!\n");
        return 0;
    }
    
    atual->altura = maior(altura_no(atual->esq), altura_no(atual->dir)) + 1;
    return res;
}

NoAVL* procura_menor(NoAVL *atual) {
    NoAVL *no1 = atual;
    NoAVL *no2 = atual->esq;
    while(no2 != NULL) {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_servico(ArvoreAVL *raiz, char *nome) {
    if(*raiz == NULL) {
        printf("Serviço não existe!\n");
        return 0;
    }
    
    int res;
    if(strcmp(nome, (*raiz)->servico.nome) < 0) {
        if((res = remove_servico(&(*raiz)->esq, nome)) == 1) {
            if(fator_balanceamento(*raiz) <= -2) {
                if(altura_no((*raiz)->dir->esq) <= altura_no((*raiz)->dir->dir)) {
                    rotacao_RR(raiz);
                } else {
                    rotacao_RL(raiz);
                }
            }
        }
    } else if(strcmp(nome, (*raiz)->servico.nome) > 0) {
        if((res = remove_servico(&(*raiz)->dir, nome)) == 1) {
            if(fator_balanceamento(*raiz) >= 2) {
                if(altura_no((*raiz)->esq->dir) <= altura_no((*raiz)->esq->esq)) {
                    rotacao_LL(raiz);
                } else {
                    rotacao_LR(raiz);
                }
            }
        }
    } else {
        if((*raiz)->esq == NULL || (*raiz)->dir == NULL) {
            NoAVL *oldNode = (*raiz);
            if((*raiz)->esq != NULL) {
                *raiz = (*raiz)->esq;
            } else {
                *raiz = (*raiz)->dir;
            }
            free(oldNode);
        } else {
            NoAVL *temp = procura_menor((*raiz)->dir);
            (*raiz)->servico = temp->servico;
            remove_servico(&(*raiz)->dir, (*raiz)->servico.nome);
            if(fator_balanceamento(*raiz) >= 2) {
                if(altura_no((*raiz)->esq->dir) <= altura_no((*raiz)->esq->esq)) {
                    rotacao_LL(raiz);
                } else {
                    rotacao_LR(raiz);
                }
            }
        }
        
        // Atualiza arquivo
        FILE *arq = fopen("servicos.txt", "w");
        if(arq != NULL) {
            salvar_servicos(raiz, arq);
            fclose(arq);
        }
        return 1;
    }
    
    (*raiz)->altura = maior(altura_no((*raiz)->esq), altura_no((*raiz)->dir)) + 1;
    return res;
}

Servico* busca_servico(ArvoreAVL *raiz, char *nome) {
    if(raiz == NULL || *raiz == NULL) return NULL;
    
    NoAVL *atual = *raiz;
    while(atual != NULL) {
        int cmp = strcmp(nome, atual->servico.nome);
        if(cmp == 0) {
            return &(atual->servico);
        } else if(cmp < 0) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    return NULL;
}

void em_ordem(ArvoreAVL *raiz) {
    if(raiz == NULL) return;
    if(*raiz != NULL) {
        em_ordem(&((*raiz)->esq));
        printf("Servico: %s\nDescricao: %s\nPreco: R$%.2f\n\n", 
               (*raiz)->servico.nome, 
               (*raiz)->servico.descricao, 
               (*raiz)->servico.preco);
        em_ordem(&((*raiz)->dir));
    }
}

void salvar_servicos(ArvoreAVL *raiz, FILE *arq) {
    if(raiz == NULL || *raiz == NULL) return;
    
    NoAVL *atual = *raiz;
    if(atual->esq != NULL) {
        salvar_servicos(&(atual->esq), arq);
    }
    
    fprintf(arq, "%s;%s;%.2f\n", 
            atual->servico.nome, 
            atual->servico.descricao, 
            atual->servico.preco);
    
    if(atual->dir != NULL) {
        salvar_servicos(&(atual->dir), arq);
    }
}

void carregar_servicos(ArvoreAVL *raiz, const char *arquivo) {
    FILE *arq = fopen(arquivo, "r");
    if(arq == NULL) {
        printf("Arquivo de serviços não encontrado. Um novo será criado.\n");
        return;
    }
    
    Servico servico;
    while(fscanf(arq, "%49[^;];%99[^;];%f\n", 
          servico.nome, servico.descricao, &servico.preco) == 3) {
        insere_servico(raiz, servico);
    }
    fclose(arq);
}