//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab 98 - Estruturas: pilha e fila.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "lab98.h"

// stack == pilha
// queue == fila

int main () {

    int n_operations;

    while (1) {

        scanf ("%d", &n_operations);

        /*  O zero representa o fim do arquivo de entrada.
        */
        if (n_operations == 0)
            return 0;


        /*  Os vetores de inteiros que representam a pilha (stack) e a fila
            (queue) sao alocados dinamicamente. É possivel utilizar o malloc
            pois nao ha remocao de uma estrutura vazia.
        */
        int *stack = malloc ((n_operations+1) * sizeof(int));
        int *queue = malloc ((n_operations+1) * sizeof(int));

        stack[0] = 1;
        queue[0] = 1;


        int operation, number;
        for (int i = 1; i <= n_operations; i ++) {

            /*  Le a operacao a ser realizada: 1 para insercao e 2 para remocao
                e em seguida o numero a ser inserido ou removido.
            */
            scanf ("%d %d\n", &operation, &number);


            /*  Insere o numero na pilha e na fila simultaneamente.
            */
            if (operation == 1)
                insert (queue, stack, number);


            /*  Se o numero a ser removido da pilha viola a propriedade de first
                in, last out, o vetor da pilha passa a ser nulo.
                Se o mesmo numero, ao ser removido da fila, violar a propriedade
                de first in, first out, o vetor da fila passa a ser nulo.
            */
            else {
                if (!remove_queue (queue, number))
                    queue = NULL;
                if (!remove_stack (stack, number))
                    stack = NULL;
            }
        }


        /*  Apos todas as operacoes, se ambos os vetores forem nulos, significa
            que as propriedades da fila E da pilha foram violadas pela sequencia
            de operacoes realizadas. Portanto, tais operacoes sao impossiveis.
        */
        if (!stack && !queue)
            printf ("impossivel\n");


        /*  Se apenas a propriedade da pilha foi violada e seu vetor for nulo,
            a sequencia dada corresponde a uma fila.
        */
        else if (!stack) {
            printf ("fila\n");
            free (queue);
        }

        /*  Se apenas a propriedade da fila foi violada e seu vetor for nulo, a
            sequencia corresponde a uma pilha.
        */
        else if (!queue) {
            printf ("pilha\n");
            free (stack);
        }

        /*  Se nenhum dos dois vetores for nulo, significa que a sequencia pode
            corresponder a uma fila ou a uma pilha.
        */
        else {
            printf ("duvida\n");
            free (stack);
            free (queue);
        }

    }

    return 0;
}
