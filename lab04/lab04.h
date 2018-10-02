// Leticia Mayumi Araujo Tateishi - RA 201454

#include <stdio.h>

typedef struct dados_vetor {
    int inicio;
    int tamanho;
    int capacidade;
} dados_vetor;


void criar_vetor(int tamanho, int *vet_circular, dados_vetor * dados);
void retirar_cartas(int *vetor, dados_vetor * dados);
void nova_posicao(dados_vetor * dados, int *vetor);
int *realocar(int *vet_original, dados_vetor * dados);
