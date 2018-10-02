//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab 13 - Crise na Krakovia


#include <stdio.h>

typedef struct corredor {
    int custo;
    int ida;
    int volta;
} corredor;


void menor_caminho (corredor *salas, int vertice, corredor *antecessor);


void maior_vizinho (corredor *vizinhos[], int tamanho);


void limpar_salas (corredor *salas);


int calcular_indice (int a, int b);


int soma_pa (int n);
