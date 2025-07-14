#ifndef LISTA_H
#define LISTA_H

typedef struct AGENDAMENTO {
    char cpfCliente[15];
    char servico[51];
    char data[11];      // formato: DD/MM/AAAA
    char hora[6];       // formato: HH:MM
    struct AGENDAMENTO *prox;
} AGENDAMENTO;

typedef struct {
    AGENDAMENTO *inicio;
} ListaAgendamento;

void inicializaLista(ListaAgendamento *lista);
void insereAgendamento(ListaAgendamento *lista, AGENDAMENTO ag);
AGENDAMENTO *buscaAgendamento(ListaAgendamento *lista, const char *cpf);
int removeAgendamento(ListaAgendamento *lista, const char *cpf);
void imprimeAgendamentos(ListaAgendamento *lista);
void salvarAgendamentos(ListaAgendamento *lista, const char *arquivo);
void carregarAgendamentos(ListaAgendamento *lista, const char *arquivo);

#endif