//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Funcoes em conjuntos disjuntos.

#include <stdio.h>
#include "conjuntos.h"


void make_set (int *array, int size) {

    /*  Inicializa todas as posicoes do vetor com o valor da propria posicao,
        indicando o representante dos conjuntos disjuntos.
    */
    for (int i = 0; i < size; i++)
        array[i] = i;
}



int find (int *array, int size, int number) {

    /*  Se o valor procurado for impossivel.
    */
    if (number < 0 || number >= size)
        return -1;

    /*  Se o numero for representante de si mesmo.
    */
    if (array[number] == number)
        return number;

    /*  Verifica os itens do conjunto ate que a segunda condicao seja
        satisfeita, ou seja, o representante seja encontrado.
    */
    return (find (array, size, array[number]));
}



int union_sets (int *array, int size, int first_root, int sec_root) {

    /*  Se pelo menos algum dos valores for impossivel.
    */
    if (first_root<0 || first_root>=size || sec_root<0 || sec_root>=size)
        return -1;

    int first_parent = find (array, size, first_root);
    int sec_parent = find (array, size, sec_root);

    /*  Se os dois valores possuirem o mesmo representante, ou seja, se
    ja estiverem no mesmo conjunto.
    */
    if (first_parent == sec_parent)
        return 0;

    /*  Ocorre a uniao dos dois conjuntos.
    */
    array[first_parent] = sec_parent;
    return 1;
}
