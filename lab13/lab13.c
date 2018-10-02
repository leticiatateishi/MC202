//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab 13 - Crise na Krakovia


#include <stdio.h>
#include <stdlib.h>
#include "lab13.h"

int main () {

    int n_corredores;

    /*  O numero de salas é 50. Entao, o numero maximo de corredores entre
        elas é (50*49)/2.
    */
    corredor *salas = calloc (soma_pa(50), sizeof (corredor));

    while (1) {

        scanf ("%d\n", &n_corredores);

        if (n_corredores == 0)
            break;


        int sala1, sala2, tempo_necessario;

        for (int i = 0; i < n_corredores; i ++) {
            scanf ("%d %d %d", &sala1, &sala2, &tempo_necessario);


            /*  Linearizando a matriz triangular inferior de adjacencias,
                atualizamos o seu custo.
            */
            int posicao;
            posicao = calcular_indice(sala1, sala2);
            (salas+posicao)->custo = tempo_necessario;
        }

        menor_caminho (salas, 0, 0);

        limpar_salas (salas);

    }

    free (salas);
    return 0;
}
