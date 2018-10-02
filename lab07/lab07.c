// Leticia Mayumi Araujo Tateishi - RA 201454

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab07.h"

int main () {

    char comando[10];
    int n_arvores, n_comandos;
    scanf ("%d %d", &n_arvores, &n_comandos);

    int i;

    no *arvores, *no_anterior;


    /*  Numera as posicoes do vetor floresta de 1 a n_arvores.
        Cria nos novos representando as arvores, que inicialmente nao possuem
        filhos.
        O irmao de um no novo é a proxima arvore a ser adicionada.
    */
    for (i=1; i<=n_arvores; i++) {

        no *novo = malloc (sizeof(no));
        novo->chave = i;
        novo->filho = NULL;

        // arvores aponta para a primeira arvore.
        if (i == 1)
            arvores = novo;

        //  A ultima arvore (cuja chave é n_arvores) nao possui irmao.
        else if (i == n_arvores)
            novo->irmao = NULL;

        // Une as arvores com chaves consecutivas.
        if (i != 1)
            no_anterior->irmao = novo;

        no_anterior = novo;
    }



    for (i=0; i<n_comandos; i++) {

        scanf ("\n%s", comando);

        if (!strcmp (comando, "link")){
            int filho, pai;
            scanf ("%d %d", &filho, &pai);
            link (&arvores, filho, pai);
        }


        else if (!strcmp (comando, "cut")) {
            int n_cortar;
            scanf ("%d", &n_cortar);
            cut (&arvores, n_cortar);
        }


        else {
            int descendente_1, descendente_2;
            scanf ("%d %d", &descendente_1, &descendente_2);
            lca (arvores, descendente_1, descendente_2, n_arvores);
        }
    }

    liberar_arvores (arvores);
    return 0;
}
