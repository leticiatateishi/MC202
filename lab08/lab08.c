// Leticia Mayumi Araujo Tateishi - RA 201454
// Lab 08 - heap aumentado com vetor.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct dupla {
    int chave;
    int custo;
} dupla;


int inserir (dupla *heap, int *posicoes, int fim, int chave_nova, int custo_novo, int tamanho);
int remover_minimo (dupla *heap, int *posicoes, int tamanho);
int diminuir_custo (dupla* heap, int *posicoes, int custo_novo, int chave_alterar);
void rearranjar_heap (dupla* heap, int *posicoes, int posicao);
void imprimir (dupla*heap, int tamanho, int fim, int *posicoes);
void arrumar (dupla *heap, int *posicoes, int i, int fim);



int main () {

    int n_duplas;
    scanf ("%d", &n_duplas);

    dupla *heap = calloc (n_duplas, sizeof(dupla));

    /* Posicoes é um vetor de inteiros tal que posicoes[i] seja a posicao da
        chave i em heap, ou seja, (heap[posicoes[i]])->chave == i.
        O vetor é inicializado com -1 para indicar vazio.
    */
    int *posicoes = malloc (n_duplas * sizeof(int));

    int x = n_duplas-1;
    while (x >= 0) {
        posicoes[x] = -1;
        x --;
    }

    char comando;
    int fim = -1;


    while (1) {

        scanf ("\n%c", &comando);


        /*  Inserir uma dupla no heap. */
        if (comando == 'i') {
            int chave_inserir, custo_inserir;
            scanf ("%d %d", &chave_inserir, &custo_inserir);

            int insercao = inserir (heap, posicoes, fim, chave_inserir, custo_inserir, n_duplas);

            /*  Se a insercao puder ser realizada, o fim é incrementado e o
                heap é rearranjado. */
            if (insercao != -1) {
                fim = insercao;
                rearranjar_heap (heap, posicoes, fim);
            }
        }


        /*  Remover a dupla de menor custo do heap. */
        else if (comando == 'm') {
            if (!remover_minimo (heap, posicoes, fim)) {
                if (fim >= 0)
                    fim --;
                arrumar (heap, posicoes, 0, fim);
            }
        }



        /*  Diminuir o custo de uma determinada chave. */
        else if (comando == 'd') {
            int chave_alterar, novo_custo;
            scanf ("%d %d", &chave_alterar, &novo_custo);

            /*  Rearranja o heap caso a alteracao de custo tenha sido realizada
            */
            if (diminuir_custo (heap, posicoes, novo_custo, chave_alterar))
                rearranjar_heap (heap, posicoes, posicoes[chave_alterar]);
        }


        else
            break;

    }

    free (heap);
    free (posicoes);
    return 0;
}
