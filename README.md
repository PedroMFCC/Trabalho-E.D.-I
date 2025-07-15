Compilação no terminal:
CLIENTE
gcc -c CLIENTE/hash.c -o CLIENTE/hash.o

FILA
gcc -c FILA/fila.c -o FILA/fila.o

AGENDAMENTO
gcc -c AGENDAMENTO/lista.c -o AGENDAMENTO/lista.o

SERVICOS
gcc -c SERVICOS/arvore.c -o SERVICOS/arvore.o

HISTORICO
gcc -c HISTORICO/pilha.c ICLIENTE -o HISTORICO/pilha.o

GERAL
gcc main.c CLIENTE/hash.o FILA/fila.o AGENDAMENTO/lista.o SERVICOS/arvore.o HISTORICO/pilha.o -o programa.exe

EXECUÇÃO
./programa.exe
