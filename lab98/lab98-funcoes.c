//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab 98 - Estruturas: pilha e fila.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "lab98.h"


void insert (int *queue, int *stack, int number) {

    /*  Queue[0] indica a posicao onde deve ser inserido o novo numero.
        O numero é inserido e queue[0] é incrementado para que possa ocorrer
        uma nova insercao.
    */
    if (queue != NULL) {
        queue[queue[0]] = number;
        queue[0] ++;
    }


    /*  Stack[0] indica a posicao onde deve ser inserido o novo numero.
        O numero é inserido e a posicao inicial é incrementada.
    */
    if (stack != NULL)  {
        stack[stack[0]] = number;
        stack[0] ++;
    }

}



int remove_queue (int *queue, int number) {

    if (queue != NULL)  {
        int i = 1;

        /*  INT_MIN indica uma posicao removida.
            Percorre todas as posicoes iniciais que ja foram removidas.
        */
        while (queue[i] == INT_MIN)
            i++;

        /*  Verifica se o primeiro numero que de fato pertence a fila (diferente
            de INT_MIN) corresponde ao valor esperado.
            Retorna 1 caso corresponda.
        */
        if (queue[i] == number) {
            queue[i] = INT_MIN;
            return 1;
        }
    }

    /*  Retorna 0 caso nao seja uma fila.
    */
    return 0;
}



int remove_stack (int *stack, int number) {

    if (stack != NULL)  {

        /*  Verifica se a ultima posicao da pilha corresponde ao numero
            esperado. Caso sim, decrementa a posicao zero (que indica a posicao
            da proxima insercao) e retorna 1.
        */
        if (stack[stack[0]-1] == number) {
            stack[stack[0]-1] = -1;
            stack[0] --;
            return 1;
        }
    }

    /*  Retorna 0 caso nao seja uma pilha.
    */
    return 0;
}
