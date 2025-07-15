#ifndef LISTA_H
#define LISTA_H

#define MAX_STATUS 20

typedef struct Agendamento {
    char cpf[15];
    char data[15];//dd/mm/aa
    char hora[6]; //hh:mm
    char tipo[50];
    char status[25];
    struct Agendamento *prox;
} Agendamento;

extern Agendamento *listaAgendamentos;


void criarAgendamento();
void visualizarAgendamentos();
void cancelarAgendamento();
void atualizarStatus();
void salvarAgendamentos();
void carregarAgendamentos();


#endif