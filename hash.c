#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"



int hash(const char *cpf){
    int h = 0;

    for(int i = 0; cpf[i] != '\0'; i++){
        h = (h + cpf[i]) % TAM;
    }

    return h;
}

void iniciaHash(Hash tabela){
    for(int i = 0; i < TAM; i++){
        tabela[i] = NULL;
    }
}

void insereCliente(){
    FILE *arq = fopen("clientes.txt", "a");
    if(arq == NULL){
        printf("Erro ao fazera leitura do arquivo de clientes\n");
        exit(1);
    }

    CLIENTE cliente;

    getchar();
    printf("CPF do cliente:");
    scanf("%14[^\n]", cliente.cpf);
    getchar();
    printf("Nome do cliente:");
    scanf("%80[\n]", cliente.nome);
    getchar();
    printf("Telefone do cliente:");
    scanf("%20[\n]", cliente.telefone);
    getchar();
    scanf("%100[\n]", cliente.endereco);
    getchar();
    printf("\n----------------------\n");


}