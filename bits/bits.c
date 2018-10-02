//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab 99 - Conjunto em vetor de bits.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "bits.h"


char* create_array (int n_bytes) {

    /*  Aloca memoria para o vetor de bits.
        O vetor ja é alocado calloc para que todos os bits iniciem falsos.
    */
    char *array = calloc (n_bytes, sizeof(char));

    return array;
}




void bit_true (char *array, int key) {

    /*  Calcula em qual byte a chave esta.
    */
    int pos_byte = key / CHAR_BIT;

    /*  Utiliza uma mascara com o operador OU para tornar o bit verdadeiro.
        A mascara é shift-left de 1 com o resto da divisao inteira da chave
        pela quantidade de bits em um char, ou seja, a posicao do bit dentro
        do byte.
    */
    array[pos_byte] = (array[pos_byte] | (1 << (key%CHAR_BIT)));
}




void bit_false (char *array, int key) {

    /*  Calcula em qual byte a chave esta.
    */
    int pos_byte = key / CHAR_BIT;

    /*  Utiliza uma mascara com o operador E para tornar o bit falso.
        A mascara é shift-left de 1 invertida com a posicao do bit dentro do
        byte.
    */
    array[pos_byte] = (array[pos_byte]) & (~(1 << (key%CHAR_BIT)));
}



int check_bit (char *array, int key) {

    /*  Calcula em qual byte a chave esta.
    */
    int pos_byte = key / CHAR_BIT;

    /*  Utiliza uma mascara com o operador E para verificar o valor do bit.
        A mascara é shift-left de 1 pela posicao do bit dentro do byte.
    */
    return ((array[pos_byte] & (1<<(key%CHAR_BIT))) > 0);
}




int count_elements (char *array, int size) {

    int count = 0;

    /*  Percorre todos os bits que representam o vetor, ou seja, a quantidade
        maxima de elementos do conjunto (size). array pode possuir mais
        espaco do que size, pois utilizamos divisao inteira para alocacao
        dinamica do vetor, mas esses bits "extras" sao desconsiderados.
        Conta a quantidade de bits positivos ha no conjunto.
    */
    for (int i = 0; i < size; i++) {
        if (check_bit (array, i))
            count ++;
    }

    return count;
}
