#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

void cadastrarCliente() {
    Cliente novoCliente;

    printf("\nCADASTRAR NOVO CLIENTE: \n\n");
    printf("CPF: ");
    scanf(" %14s", novoCliente.cpf);
    printf("Nome: ");
    scanf(" %[^\n]", novoCliente.nome);
    printf("Telefone: ");
    scanf(" %19s", novoCliente.telefone);
    printf("Endereço: ");
    scanf(" %[^\n]", novoCliente.endereco);

    if (inserir(novoCliente))
        printf("Cliente cadastrado com sucesso.\n");
    else
        printf("Erro: CPF já existente.\n");
}

void buscarCliente() {
    char cpf [15];

    printf("\nBUSCAR CLIENTE: \n\n");

    printf("CPF: ");
    scanf(" %14s", cpf);
    Cliente *cliente = buscar(cpf);

    if (cliente)
        printf("Nome: %s | Tel: %s | Endereço: %s\n", cliente->nome, cliente->telefone, cliente->endereco);
    else
        printf("Cliente não encontrado.\n");
}

void atualizarCliente() {
    char cpf[15];
    Cliente novo;

    printf("\nATUALIZAR DADOS DE CLIENTE: \n\n");

    printf("CPF: ");
    scanf(" %14s", cpf);

    Cliente* cliente = buscar(cpf);

    if (cliente) {
        printf("Novo nome: ");
        scanf(" %[^\n]", novo.nome);
        printf("Novo telefone: ");
        scanf(" %19s", novo.telefone);
        printf("Novo endereço: ");
        scanf(" %[^\n]", novo.endereco);

        atualizar(cliente, novo);

        printf("Cliente atualizado com sucesso.\n");
    } else {
        printf("Cliente não encontrado.\n");
    }
}

void removerCliente() {
    char cpf[15];

    printf("\nREMOVER CLIENTE: \n\n");

    printf("CPF: ");
    scanf(" %14s", cpf);

    if (remover(cpf))
        printf("Cliente removido com sucesso.\n");
    else
        printf("Cliente não encontrado.\n");
}