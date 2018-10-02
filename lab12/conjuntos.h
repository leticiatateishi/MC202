//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Funcoes em conjuntos disjuntos.

#include <stdio.h>


/*  Cria um numero size de conjuntos disjuntos, todos de tamanho um e com
    representante igual ao unico elemento.
*/
void make_set (int *array, int size);


/*  Retorna o representante de um conjunto.
*/
int find (int *array, int number);


/*  Retorna -1 se pelo menos uma das raizes for um valor impossivel.
             0 se os dois numeros ja pertencem ao mesmo conjunto.
             1 se os dois conjuntos foram unidos.
*/
void union_sets (int *array, int first_root, int sec_root);



edge* sort_distance (asteroid *solar_system, int n, edge *sorted_edges, float time);


void quicksort (edge *sorted_edges, int low, int high, int size);


int partition (edge *sorted_edges, int low, int high, int size);


void switch_egdes (edge *sorted_edges, int first, int second);
