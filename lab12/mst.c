//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Funcoes auxiliares para o algoritmo Minimum Spanning Tree de Kruskal.

#include <stdio.h>
#include "mst.h"


void make_set (int *array, int size) {

    /*  Inicializa todas as posicoes do vetor com o valor da propria posicao,
        indicando o representante dos conjuntos disjuntos.
    */
    for (int i = 0; i < size; i++)
        array[i] = i;
}



int find (int *array, int number) {

    /*  Se o numero for representante de si mesmo.
    */
    if (array[number] == number)
        return number;

    /*  Verifica os itens do conjunto ate que a segunda condicao seja
        satisfeita, ou seja, o representante seja encontrado.
    */
    return (find (array, array[number]));
}



void union_sets (int *array, int first_root, int sec_root) {

    /*  Encontra os dois representantes.
    */
    int first_parent = find (array, first_root);
    int sec_parent = find (array, sec_root);

    /*  Se os dois valores possuirem o mesmo representante, ou seja, se
    ja estiverem no mesmo conjunto.
    */
    if (first_parent == sec_parent)
        return;

    /*  Ocorre a uniao dos dois conjuntos.
    */
    array[first_parent] = sec_parent;
}




edge* sort_distance (asteroid *solar_system, edge *sorted_edges, int n,
float time) {

    int k = 0;

    /*  Percorre todas as arestas, de dois a dois asteroides.
    */
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {

            /*  Iniciliza os vertices da aresta e a distancia.
            */
            (sorted_edges[k]).start = i;
            (sorted_edges[k]).end = j;
            (sorted_edges[k]).distance = calculate_distance (&solar_system[i],
                &solar_system[j], time);
            k ++;
        }
    }

    quicksort (sorted_edges, 0, n-1, ((n-1)*n)/2);

    /*  Retorna o vetor de arestas organizado em ordem crescente.
    */
    return sorted_edges;
}






void quicksort (edge *sorted_edges, int low, int high, int size) {

    if (low < high) {
        int pivot = partition (sorted_edges, low, high, size);
        quicksort (sorted_edges, low, pivot-1, size);
        quicksort (sorted_edges, pivot+1, high, size);
    }
}




int partition (edge *sorted_edges, int low, int high, int size) {

    int left = low, right = high;
    float pivot_item = (sorted_edges[low]).distance;

    while (left < right) {

        while (left < size && (sorted_edges[left]).distance <= pivot_item)
            left ++;

        while (right >= 0 && (sorted_edges[right]).distance > pivot_item)
            right --;

        if (left < right)
            switch_egdes (sorted_edges, left, right);
    }

    if (low < size && right < size)
        switch_egdes (sorted_edges, low, right);
    return right;
}



void switch_egdes (edge *sorted_edges, int first, int second) {

    float temp = (sorted_edges[first]).distance;
    (sorted_edges[first]).distance = (sorted_edges[second]).distance;
    (sorted_edges[second]).distance = temp;

    temp = (sorted_edges[first]).start;
    (sorted_edges[first]).start = (sorted_edges[second]).start;
    (sorted_edges[second]).start = temp;

    temp = (sorted_edges[first]).end;
    (sorted_edges[first]).end = (sorted_edges[second]).end;
    (sorted_edges[second]).end = temp;
}
