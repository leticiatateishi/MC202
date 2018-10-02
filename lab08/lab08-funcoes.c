// Leticia Mayumi Araujo Tateishi - RA 201454
// Lab 08 - heap aumentado com vetor.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dupla {
    int chave;
    int custo;
} dupla;



/*  Insere uma dupla {chave, custo} no heap e retorna a posicao do fim do heap.
*/
int inserir (
    dupla *heap, int *posicoes, int fim, int chave_nova, int custo_novo,
    int tamanho
) {

    /*  Se a chave a ser inserida ja pertence ao heap, a insercao nao ocorre
        e a variavel fim nao é incrementada.
    */
    if (posicoes[chave_nova] != -1)
        return -1;


    /*  O incremento de fim indica que a insercao foi feita. */
    fim ++;

    /*  A dupla {chave, custo} da ultima posicao do heap é copiada ao inicio
        e sua localizacao é atualizada no vetor posicoes.
    */
    (*(heap + fim)).chave = chave_nova;
    (*(heap + fim)).custo = custo_novo;
    posicoes[chave_nova] = fim;

    return fim;
}



/*  Remove a dupla com custo minimo, ou seja, a primeira dupla do vetor
    circular que representa o heap.
    Retorna 0 se a remocao foi feita.
    Retorna -1 caso contrario.
*/
int remover_minimo (dupla *heap, int *posicoes, int fim) {

    int i = posicoes[(*heap).chave];

    /*  Quando nao ha chave tal que posicoes[chave] == 0, o heap esta vazio. */
    if (i == -1) {
        printf ("vazio\n");
        return 1;
    }


    /*  Imprime a primeira dupla do heap e atualiza sua posicao para -1. */
    printf ("minimo {%d,%d}\n", (*heap).chave, (*heap).custo);
    posicoes[(*heap).chave] = -1;


    /*  Se o heap possuir mais de um elemento, a primeira posicao recebe a
        ultima (equivalente a uma folha de uma arvore binaria) e a ultima
        recebe a dupla nula {0, 0}.
    */
    if (fim > 0) {
        (*heap).chave = (*(heap + fim)).chave;
        (*heap).custo = (*(heap + fim)).custo;
        (*(heap + fim)).chave = (*(heap + fim)).custo = 0;
        posicoes[(*heap).chave] = 0;
    }

    return 0;
}



/*  Reorganiza o vetor do inicio ate que a caracteristica de heap de minimo
    for satisfeita.
*/
void arrumar (dupla *heap, int *posicoes, int i, int fim) {

    int esquerda = 2*i + 1;
    int direita = esquerda + 1;


    int aux_custo = (*(heap + i)).custo;
    int aux_chave = (*(heap + i)).chave;


    /*  Se a posicao atual possuir, no minimo, filho da esquerda.  */
    if (esquerda <= fim) {

        /*  Se a posicao atual possuir filho da direita e filho da esquerda. */
        if (direita <= fim) {


            /*  Se o custo do filho da esquerda for inferior ao da direita e
                ao do pai, as uplas do filho da esquerda e de seu pai sao
                trocadas e suas posicoes sao atualizadas.
            */
            if (
                (*(heap + esquerda)).custo < (*(heap + direita)).custo &&
                (*(heap + i)).custo > (*(heap + esquerda)).custo
            ) {

                (*(heap + i)).custo = (*(heap + esquerda)).custo;
                (*(heap + i)).chave = (*(heap + esquerda)).chave;
                (*(heap + esquerda)).custo = aux_custo;
                (*(heap + esquerda)).chave = aux_chave;

                posicoes[(*(heap + esquerda)).chave] = esquerda;
                posicoes[(*(heap + i)).chave] = i;

                return arrumar (heap, posicoes, esquerda, fim);
            }


            /*  Se o custo do filho da direita for inferior ao custo do filho
                da esquerda e ao custo do pai, as duplas de filho da direita e
                de seu pai sao trocadas e suas posicoes sao atualizadas.
            */
            else if ( (*(heap + i)).custo > (*(heap + direita)).custo ){

                (*(heap + i)).custo = (*(heap + direita)).custo;
                (*(heap + i)).chave = (*(heap + direita)).chave;
                (*(heap + direita)).custo = aux_custo;
                (*(heap + direita)).chave = aux_chave;

                posicoes[(*(heap + direita)).chave] = direita;
                posicoes[(*(heap + i)).chave] = i;

                return arrumar (heap, posicoes, direita, fim);
            }
        }


        /*  Se a posicao possuir apenas filho da esquerda e o custo do unico
            filho for menor que o custo do pai, a troca é feita.
        */
        else if ( (*(heap + i)).custo > (*(heap + esquerda)).custo ){
            (*(heap + i)).custo = (*(heap + esquerda)).custo;
            (*(heap + i)).chave = (*(heap + esquerda)).chave;
            (*(heap + esquerda)).custo = aux_custo;
            (*(heap + esquerda)).chave = aux_chave;

            posicoes[(*(heap + esquerda)).chave] = esquerda;
            posicoes[(*(heap + i)).chave] = i;

            return arrumar (heap, posicoes, esquerda, fim);
        }
    }
}




/*  Altera o custo de uma chave especifica.
    Retorna 1 caso a alteracao seja realizada com sucesso.
    Retorna 0 caso contrario, ou seja, caso a chave pedida nao esteja no heap.
*/
int diminuir_custo (
    dupla *heap, int *posicoes, int custo_novo, int chave_alterar
) {

    int i = posicoes[chave_alterar];

    if (i != -1){
        (*(heap + i)).custo = custo_novo;
        return 1;
    }

    return 0;
}



/*  Percorre o heap do fim ao inicio e procura duplas cujo custo viole a
    organizacao do heap.
    Altera a posicao das duplas quando seu custo for menor do que o custo de
    seu antecessor.
*/
void rearranjar_heap (dupla* heap, int *posicoes, int posicao) {

    /*  A posicao zero é raiz da arvore e nao possui pai.  */
    if (posicao <= 0)
        return;


    int pai = (posicao - 1) / 2;


    /*  Se o custo da chave atual for menor do que o custo de seu pai, as
        duplas sao trocadas e suas posicoes sao atualizadas.
        A funcao é chamada recursivamente para a nova posicao, para que seu novo
        custo seja novamente comparada com o avo.
    */
    if ((*(heap + posicao)).custo < (*(heap + pai)).custo) {

        int aux_custo = (*(heap + pai)).custo;
        int aux_chave = (*(heap + pai)).chave;
        (*(heap + pai)).custo = (*(heap + posicao)).custo;
        (*(heap + pai)).chave = (*(heap + posicao)).chave;
        (*(heap + posicao)).custo = aux_custo;
        (*(heap + posicao)).chave = aux_chave;

        posicoes[aux_chave] = posicao;
        posicoes[(*(heap + pai)).chave] = pai;

        return rearranjar_heap (heap, posicoes, pai);
    }

}
