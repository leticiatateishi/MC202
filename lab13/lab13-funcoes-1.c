//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab 13 - Crise na Krakovia


#include <stdio.h>
#include <stdlib.h>
#include "lab13.h"


int percurso_profundidade (int *corredores) {

    int *tempos = calloc (50, sizeof(int));

    int k = visitar_vertice (corredores, 0, 0, tempos);
    free (tempos);
    return k;
}




int visitar_vertice (int *corredores, int vertice, int antecessor, int *tempos,
int subtrair){


    int n_bifurcacoes = cont_bifurcacao (corredores, vertice, antecessor);

    int ultimo = 0;


    if (n_bifurcacoes == 0) {
        // printf ("sala %d nao possui mais vizinhos\n", vertice);

        int k;
        if (vertice > antecessor)
            k = soma_pa(vertice) + antecessor;
        else
            k = soma_pa(antecessor) + vertice;
        // tempos[vertice] = corredores[k];
        tempos[vertice] = tempos[antecessor] + corredores[k];
        // printf ("%d = %d + %d\n", tempos[vertice], tempos[antecessor],
        // corredores[k]);
        return tempos[vertice];
    }


    int total = 0;
    for (int j = 0; j < 50; j++) {

        int numero;
        if (j == vertice || j == antecessor)
            continue;
        if (j < vertice)
            numero = soma_pa(vertice) +j;
        else
            numero = soma_pa(j) + vertice;


        if (corredores[numero] != 0) {

            // printf ("analisando corredor %d no segundo for\n", numero);

            // if (vertice != antecessor) {
            //
            //     int valor;
            //     if (vertice > antecessor)
            //         valor = soma_pa(vertice) + antecessor;
            //     else
            //         valor = soma_pa(antecessor) + vertice;
            //     // tempos[vertice] = tempos[antecessor] + corredores[valor];
            //     // printf ("%d = %d + %d --", tempos[vertice],
            //     // tempos[antecessor], corredores[valor]);
            //     // printf ("vertice = %d, antecessor = %d, numero = %d\n",
            //     // vertice, antecessor, numero);
            // }

            int x = visitar_vertice (corredores, j, vertice, tempos, subtrair);

            print_tempos(tempos, 16);

            if (ultimo == 0)
                ultimo = x;
            else{
                // printf ("ultimo = %d (20), x = %d (10)\n", ultimo, x);
                if (x < ultimo) {
                    total += 2*(x-tempos[vertice]);
                    subtrair = ultimo;
                }
                else {
                    total += 2*(ultimo-tempos[vertice]);
                    ultimo = x;
                    subtrair = ultimo;
                }

            }
        }
    }


    if (n_bifurcacoes > 1 && vertice != 0) {
        tempos[vertice] += total;
        // tempos[vertice] += total;
    }
    if (vertice == 0) {
        tempos[vertice] += total+ultimo - subtrair;
    }
    return tempos[vertice];
    // return ultimo;

}




int cont_bifurcacao (int *corredores, int chave, int pai) {

    int cont = 0;

    for (int i = 0; i < chave; i++) {
        if (corredores[soma_pa (chave) + i] != 0 && i != pai)
            cont ++;
    }

    for (int j = chave+1; j < 50; j++){
        if (corredores[soma_pa(j) + chave] != 0 && j != pai)
            cont ++;
    }

    // printf ("%d possui %d vizinhos\n", chave, cont);
    return cont;
}



void print_tempos (int *tempos, int tamanho) {

    for (int i = 0; i < tamanho; i++)
        printf ("%d ", tempos[i]);
    printf ("\n");
}




int soma_pa (int n) {
    return (((n-1)*n)/2);
}
