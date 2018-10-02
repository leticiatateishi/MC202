//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab 12 - Conexoes entre asteroides.

#include <stdio.h>
#include <stdlib.h>



/*  Armazena todas as informacoes de um asteroide: sua posicao e sua velocidade
    no espaco.
*/
typedef struct asteroid {
    int x_position;
    int y_position;
    int z_position;
    int x_velocity;
    int y_velocity;
    int z_velocity;
} asteroid;


/*  Representa uma aresta nao ordenada.
    Start e end indicam os vertices unidos pelo vertice, embora seja uma aresta
    nao ordenada e a escolha dos vertices start e end seja arbitraria.
*/
typedef struct edge {
    int start;
    int end;
    float distance;
} edge;



/*  Cria a arvore de custo minimo e retorna o tamanho de arestas presentes
    em tree.
*/
int minimum_tree (int n_asteroids, asteroid *solar_system, edge *tree,
float time);


/*  Retorna a quantidade de vezes que a
*/
int tree_changes (asteroid *solar_system, int n_asteroids);


/*  Retorna a distancia entre dois asteroides em um determinado instante de
    tempo.
*/
float calculate_distance (asteroid *one, asteroid *two, float t);


/*  Retorna 1 se as arvores forem diferentes.
            0 se as arvores forem iguais.
*/
int compare_trees (edge *first, edge *second, int size, int tree_size,
int n_asteroids);


/*  Retorna a quantidade de vizinhos de uma posicao key em uma determinada
    arvore array_edges
*/
int count_neighbours (edge *array_edges, int key, int size);


/*  Inicializa em array a posicao em solar_system de todos os vizinhos de uma]
    determinada chave number.
*/
void find_neighbours (edge *array_edges, int *array, int number, int size);


/*  Retorna 0 se os vetores forem iguais.
            1 se os vetores forem diferentes.
*/
int compare_arrays (int *first, int *second, int size);


/*  Retorna -1 se a distancia entre os asteroides um e dois nunca for igual a
    distancia entre os asteroides tres e quatro.
    Retorna o tempo no qual a equivalencia entre distancias é valida, caso
    contrario.
*/
float calculate_time (asteroid *one, asteroid *two, asteroid *three,
asteroid *four);
