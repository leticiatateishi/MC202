//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab 12 - Conexoes entre asteroides.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lab12.h"
// #include "mst.h"

// Armazenar sorted edges pra nao precisar reorganizar?
// Matriz de bits que indica quais asteroides vao se cruzar: se locomovem em
// sentidos opostos ou em sentidos iguais mas com velocidades diferentes.

int main () {

    int n_asteroids;
    scanf ("%d\n", &n_asteroids);
    asteroid *solar_system = malloc (n_asteroids * sizeof(asteroid));


    /*  Leitura da posicao e da velocidade do asteroide no espaco.
    */
    for (int i = 0; i < n_asteroids; i++) {

        scanf ("%d %d %d %d %d %d", &solar_system[i].x_position,
            &solar_system[i].y_position, &solar_system[i].z_position,
            &solar_system[i].x_velocity, &solar_system[i].y_velocity,
            &solar_system[i].z_velocity);
    }

    /*  Quando ha apenas dois asteroides, ha apensas uma arvore geradora de
        minimo possivel, que é tal que ha uma unica aresta unindo os dois
        asteroides.
    */
    if (n_asteroids == 2) {
        printf ("1\n");
        free (solar_system);
        return 0;
    }

    // print_graph (solar_system, n_asteroids);

    // edge *tree = malloc (n * sizeof(edge));
    // int tree_size = initialize_tree (tree, solar_system, n_asteroids);

    int n_changes = tree_changes (solar_system, n_asteroids);
    printf ("%d\n", n_changes+1);

    free (solar_system);
    return 0;
}
