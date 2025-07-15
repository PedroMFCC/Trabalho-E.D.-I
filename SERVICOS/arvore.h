#ifndef SERVICO_H
#define SERVICO_H

typedef struct Servico {
    char tipo[50];
    char descricao[100];
    float preco;
} Servico;

typedef struct NoServico {
    Servico servico;
    struct NoServico *esq;
    struct NoServico *dir;
    int altura;
} NoServico;

extern NoServico* arvoreServicos;

void adicionarServico();
void buscarServico();
void listarServicosOrdem();
void salvarServicos();
void carregarServicos();

#endif