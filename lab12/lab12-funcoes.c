//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab 12 - Conexoes entre asteroides.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lab12.h"
#include "mst.h"



int minimum_tree (int n_asteroids, asteroid *solar_system, edge *tree,
float time) {


    /*  Vetor de inteiros que indica o representante de cada vertice.
        Inicialmente, ha n_asteroids sets e cada vertice é representante de
        si mesmo.
    */
    int *sets = malloc (n_asteroids * sizeof(int));
    make_set (sets, n_asteroids);


    /*  Vetor de edges que armazena a quantidade exata de arestas, considerando
        que todo vertice esta ligado a todos os outros n_asteroids-1 vertices.
        Armazena os vertices das duas extremidades e a distancia entre eles.
    */
    int n = ((n_asteroids-1)*n_asteroids) / 2;
    edge *sorted_edges = malloc (n*sizeof(edge));

    /*  O vetor de arestas é ordenado de acordo com as distancias.
    */
    sorted_edges = sort_distance(solar_system, n_asteroids, sorted_edges, time);


    /*  Contador da quantidade de arestas na arvore tree.
    */
    int position_tree = 0;

    /*  Para todas as arestas em sorted_edges, verifica se a aresta entre os
         asteroides start e end formam um ciclo, ou seja, se possuem o mesmo
         representante. Caso nao, eles sao adicionados a arvore e seus
         conjuntos sao unidos..
    */
    for (int i = 0; i < n; i++) {
        if (find (sets, sorted_edges[i].start)
        != find (sets, sorted_edges[i].end)) {

            tree[position_tree].start = sorted_edges[i].start;
            tree[position_tree].end = sorted_edges[i].end;
            tree[position_tree].distance = sorted_edges[i].distance;

            position_tree ++;

            union_sets (sets, sorted_edges[i].start, sorted_edges[i].end);
        }
    }

    free (sorted_edges);
    free (sets);
    return position_tree;

}




int tree_changes (asteroid *solar_system, int n_asteroids) {

    int count = 0;

    int n = ((n_asteroids-1)*n_asteroids) / 2;

    edge *before = malloc (n*sizeof(edge));
    edge *after = malloc (n*sizeof(edge));



    /*  Para quando ha apenas tres asteroides, 6 comparacoes bastam, pois
        considerando um asteroide como "central", devemos comparar a distancia
        deste central aos outros dois, verificando se as duas distancias serao
        iguais em algum momento.
    */
    if (n_asteroids == 3) {

        for (int i = 0; i < n_asteroids; i++) {

            int j = (i+1)%n_asteroids;
            int k = (j+1)%n_asteroids;


            /*  O asteroide i é o central, e a distancia i-j é comparada com
                a distancia i-k.
            */
            float time = calculate_time (&solar_system[i],
                &solar_system[j], &solar_system[i],
                &solar_system[k]);

            /*  Se tais distancias forem iguais em algum momento.
            */
            if (time != -1) {

                int before_size = minimum_tree (n_asteroids, solar_system,
                before, (time - pow (10, -6)));

                int after_size = minimum_tree (n_asteroids, solar_system,
                after, (time + pow (10, -6)));

                if (compare_trees (before, after, before_size, after_size,
                n_asteroids) == 1)
                    count ++;

            }
        }

        free (before);
        free (after);
        return count;
    }


    /*  Para quatro ou mais asteroides, devemos ferificar que todas as
        distancias sejam comparadas.
    */
    int i, j, k, l;

    for (i = 0; i < n_asteroids-3; i++) {
        for (j = i+1; j < n_asteroids-2; j++) {
            for (k = j+1; k < n_asteroids-1; k++) {
                for (l = k+1; l < n_asteroids; l++) {

                    float time = calculate_time (&solar_system[i],
                        &solar_system[j], &solar_system[k],
                        &solar_system[l]);

                    if (time != -1) {

                        int before_size = minimum_tree (n_asteroids,
                            solar_system, before, (time - pow (10, -6)));
                        int after_size = minimum_tree (n_asteroids,
                            solar_system, after, (time + pow (10, -6)));

                        if (!compare_trees (before, after, before_size,
                        after_size, n_asteroids))
                            count ++;

                    }


                    time = calculate_time (&solar_system[i],
                        &solar_system[k], &solar_system[j],
                        &solar_system[l]);

                    if (time != -1) {

                        int before_size = minimum_tree (n_asteroids,
                            solar_system, before, (time - pow (10, -6)));
                        int after_size = minimum_tree (n_asteroids,
                            solar_system, after, (time + pow (10, -6)));

                        if (!compare_trees (before, after, before_size,
                        after_size, n_asteroids))
                            count ++;

                    }



                    time = calculate_time (&solar_system[i],
                        &solar_system[l], &solar_system[k],
                        &solar_system[j]);

                    if (time != -1) {

                        int before_size = minimum_tree (n_asteroids,
                            solar_system, before, (time - pow (10, -6)));
                        int after_size = minimum_tree (n_asteroids,
                            solar_system, after, (time + pow (10, -6)));

                        if (!compare_trees (before, after, before_size,
                        after_size, n_asteroids))
                            count ++;


                    }
                }

            }
        }
    }

    free (before);
    free (after);
    return count;
}



float calculate_distance (asteroid *one, asteroid *two, float t) {

    float distance;

    /*  Sendo S1x a posicao no eixo x do asteroide um em tal instante de tempo:
        distancia^2 = (S1x - S2x)^2 + (S1y - S2y)^2 + (S1z - S2z)^2
    */
    distance =  pow (one->x_position + ((one->x_velocity)*t) - two->x_position
                - ((two->x_velocity)*t), 2) +
                pow (one->y_position + ((one->y_velocity)*t) - two->y_position
                - ((two->y_velocity)*t), 2) +
                pow (one->z_position + ((one->z_velocity)*t) - two->z_position
                - ((two->z_velocity)*t), 2);

    return sqrt(distance);
}




int compare_trees (edge *first, edge *second, int first_size, int sec_size,
int n_asteroids) {


    /*  Se os tamanhos das arvores forem diferentes, elas obrigatoriamente
        tambem serao diferentes.
    */
    if (first_size != sec_size)
        return 1;


    /*  Para cada asteroide i, first_neighbours armazena a quantidade de
        vizinhos de i na primeira arvore e second_neighbours para a segunda
        arvore. Em seguida, first_array armazena a chave (posicao no sistema
        solar) de cada vizinho de i na primeira arvore. O mesmo em second_array
        para a segunda arvore.
        Entao, first_array e second_array sao comparados. Se forem iguais, as
        duas arvores tambem sao iguais.
    */
    for (int i = 0; i < n_asteroids; i++) {

        int first_neighbours = count_neighbours (first, i, first_size);
        int second_neighbours = count_neighbours (second, i, first_size);


        if (first_neighbours != second_neighbours)
            return 1;


        int *first_array = malloc (first_neighbours * sizeof(int));
        int *second_array = malloc (first_neighbours * sizeof(int));


        find_neighbours (first, first_array, i, first_size);
        find_neighbours (second, second_array, i, first_size);

        if (compare_arrays (first_array, second_array, first_neighbours))
            return 1;


        free (first_array);
        free (second_array);
    }

    return 0;

}



int count_neighbours (edge *array_edges, int key, int size) {

    int count = 0;

    /*  Percorre todas as arestas da arvore e verifica se o inicio ou o fim
        de alguma é igual a chave procurada.
    */
    for (int i = 0; i < size; i++){
        if (array_edges[i].start == key || array_edges[i].end == key)
            count ++;
    }

    return count;
}



void find_neighbours (edge *array_edges, int *array, int number, int size) {

    int j = 0;

    for (int i = 0; i < size; i++) {

        /*  Se algum dos vertices da aresta for o numero buscado, o outro
            vertice é vizinho e é adicionado a array.
        */
        if (array_edges[i].start == number)
            array[j++] = array_edges[i].end;

        else if (array_edges[i].end == number)
            array[j++] = array_edges[i].start;
    }
}





int compare_arrays (int *first, int *second, int size) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (first[i] == second[j])
                j = size+1;
            if (j == size-1)
                return 1;
        }
    }

    return 0;
}





float calculate_time (asteroid *one, asteroid *two, asteroid *three,
    asteroid *four) {

    int a = pow ((float) one->x_velocity-two->x_velocity, 2)
        + pow ((float) one->y_velocity-two->y_velocity, 2)
        + pow ((float) one->z_velocity-two->z_velocity, 2)
        - pow ((float) three->x_velocity-four->x_velocity, 2)
        - pow ((float) three->y_velocity-four->y_velocity, 2)
        - pow ((float) three->z_velocity-four->z_velocity, 2);
    a = (float) a;

    if (a == 0)
        return -1;


    int b =
     (((one->x_position-two->x_position)*(one->x_velocity-two->x_velocity))
    +((one->y_position-two->y_position)*(one->y_velocity-two->y_velocity))
    +((one->z_position-two->z_position)*(one->z_velocity-two->z_velocity))
    -((three->x_position-four->x_position)*(three->x_velocity-four->x_velocity))
    -((three->y_position-four->y_position)*(three->y_velocity-four->y_velocity))
    -((three->z_position-four->z_position)*(three->z_velocity-four->z_velocity))
    );
    b = (float) b*2;


    float c = calculate_distance (one, two, 0)
    - calculate_distance (three, four, 0);

    float delta;
    delta = (b*b) - (4*a*c);


    if (delta < 0)
        return -1;

    float first_time = (((-1)*b) + sqrt(delta)) / (2*a);
    float sec_time = (((-1)*b) - sqrt(delta)) / (2*a);


    if (first_time > 0)
        return first_time;
    if (sec_time > 0)
        return sec_time;
    return -1;
}
