#ifndef HISTORICO_H
#define HISTORICO_H

#define MAX_OBS 200

typedef struct Atendimento {
    char cpf[15];
    char data[15];    // dd/mm/aa
    char hora[6];     // hh:mm
    char tipo[50];
    char observacoes[MAX_OBS];
    struct Atendimento *prox;
} Atendimento;

typedef struct {
    Atendimento *topo;
} PilhaHistorico;

void registrarAtendimento();
void visualizarHistorico();
void salvarHistoricos();
void carregarHistoricos();

#endif