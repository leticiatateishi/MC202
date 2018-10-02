//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Funcoes auxiliares para o algoritmo Minimum Spanning Tree de Kruskal.

#include <stdio.h>


typedef struct asteroid {
    int x_position;
    int y_position;
    int z_position;
    int x_velocity;
    int y_velocity;
    int z_velocity;
} asteroid;


typedef struct edge {
    int start;
    int end;
    float distance;
} edge;


/*  Cria um numero size de conjuntos disjuntos, todos de tamanho um e com
    representante igual ao unico elemento.
*/
void make_set (int *array, int size);


/*  Retorna o representante de um conjunto.
*/
int find (int *array, int number);


/*  Faz a uniao de dois conjuntos, de modo tal que o representante do primeiro
    seja igual ao representante do segundo.
*/
void union_sets (int *array, int first_root, int sec_root);


/*  Iniciliza um vetor com todas as arestas entre asteroides (os dois vertices
    e a distancia entre eles). Em seguida, utiliza o algoritmo de quicksort
    para ordenar em ordem crescente de distancia.
*/
edge* sort_distance (asteroid *solar_system, edge *sorted_edges, int n,
float time);



void quicksort (edge *sorted_edges, int low, int high, int size);


int partition (edge *sorted_edges, int low, int high, int size);


/*  Faz a troca de duas arestas para auxiliar a funcao partition do quicksort.
*/
void switch_egdes (edge *sorted_edges, int first, int second);
