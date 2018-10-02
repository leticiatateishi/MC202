//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Funcoes em conjuntos disjuntos.

#include <stdio.h>


/*  Cria um numero size de conjuntos disjuntos, todos de tamanho um e com
    representante igual ao unico elemento.
*/
void make_set (int *array, int size);


/*  Retorna o representante de um conjunto.
*/
int find (int *array, int size, int number);


/*  Retorna -1 se pelo menos uma das raizes for um valor impossivel.
             0 se os dois numeros ja pertencem ao mesmo conjunto.
             1 se os dois conjuntos foram unidos.
*/
int union_sets (int *array, int size, int first_root, int sec_root);
