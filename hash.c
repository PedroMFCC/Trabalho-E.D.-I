#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

void insereCliente(){
    FILE *arq = fopen("clientes.txt", "a");
    if(arq == NULL){
        printf("Erro ao fazera leitura do arquivo de clientes\n");
        exit(1);
    }

    


}
