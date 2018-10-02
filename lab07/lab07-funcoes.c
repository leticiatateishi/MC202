// Leticia Mayumi Araujo Tateishi - RA 201454

#include <stdio.h>
#include <stdlib.h>
#include "lab07.h"


/*  Recebe como parametro dois inteiros. O primeiro (filho) é uma raiz, e o
    segundo (pai) pertence a uma arvore cuja raiz nao é o primeiro.
    Cria uma aresta entre pai e filho, fazendo com que filho deixe de ser raiz,
    ou seja, seja removido do vetor de inteiros (floresta).
*/
void link (no **arvores, int filho, int pai) {

    no* no_filho = buscar (*arvores, filho);
    no* no_pai = buscar (*arvores, pai);

    //  Caso a primeira arvore se torne filha de alguma outra
    if ((*arvores)->chave == filho)
        *arvores = no_filho->irmao;


    //  Procura o no anterior a no_filho, e aponta o irmao desse no para o irmao
    //    do no filho.
    else {
        no *posicao = *arvores;
        while (1) {
            if (posicao->irmao && posicao->irmao->chave == filho)
                break;
            posicao = posicao->irmao;
        }
        posicao->irmao = no_filho->irmao;
    }



    //  Se o no_pai ainda nao possuir filhos, no_filho sera seu primeiro filho.
    if (!no_pai->filho) {
        no_pai->filho = no_filho;
        no_filho->irmao = NULL;
        return;
    }

    //  Se no_pai ja possuir filhos, no_filho sera irmao do ultimo irmao de
    //  no_pai->filho.
    else {
        no *aux = no_pai->filho;
        while (aux->irmao)
            aux = aux->irmao;
        aux->irmao = no_filho;
        no_filho->irmao = NULL;
        return;
    }

}



/*  Recebe a chave de um no e remove a aresta do pai desse no com ele. A chave
    recebida por parametro nao é chave de alguma arvore, mas passa a ser apos
    ser cortado.
*/
void cut (no **arvores, int n_cortar) {

    no *no_cortar = buscar (*arvores, n_cortar);
    no *pai = buscar_pai (*arvores, n_cortar);

    /*   Se o no a ser cortado for o primeiro filho de seu pai, o apontador
        "filho" do pai passara a apontar para o segundo filho, e o no recortado
        passa a ser irmao de seu pai (volta a ser raiz de uma arvore).
    */
    if (pai->filho && pai->filho->chave == n_cortar) {
        pai->filho = no_cortar->irmao;
        no_cortar->irmao = pai->irmao;
        pai->irmao = no_cortar;
        return;
    }

    /*  Se o no a ser cortado nao for o primeiro filho, o filho que o precede
        é encontrado e seu apontador "irmao" passa a apontar para o no que
        sucede no_cortar.
    */
    no *aux = pai->filho;
    while (aux->irmao) {
        if (aux->irmao->chave == n_cortar)
            break;
        aux = aux->irmao;
    }

    aux->irmao = no_cortar->irmao;

    // No_cortar passa a ser a primeira raiz da floresta.
    no_cortar->irmao = (*arvores);
    (*arvores) = no_cortar;
}



/*  Recebe duas chaves e imprime o ancestral comum mais baixo de ambos, que
    estao inicialmente na mesma arvores.
*/
void lca (no *arvores, int descendente_1, int descendente_2, int tam_floresta) {

    //  Caso as duas chaves recebidas sejam iguais, o lca é a propria chave.
    if (descendente_1 == descendente_2) {
        printf ("%d\n", descendente_1);
        return;
    }

    no* a = buscar (arvores, descendente_1);
    no* b = buscar (arvores, descendente_2);

    /*  Cria um vetor de inteiros para cada chave, que armazenara a chave de
        todos os ancestrais, do mais baixo para o mais alto.
    */
    int *ancestrais_a = calloc (tam_floresta, sizeof(int));
    int *ancestrais_b = calloc (tam_floresta, sizeof(int));

    //  O primeiro ancestral de cada chave é a propria chave.
    ancestrais_a[0] = descendente_1;
    ancestrais_b[0] = descendente_2;


    /*  Busca os ancestrais de descendente_1 e descendente_2 atraves da funcao
        buscar_pai e atualizando a (no com chave inicial descendente_1) e b
        (no com chave inicial descendente_2) para seu pai.
        A cada loop, se a e b nao forem raizes de arvores (ou seja, se houver
        ancestrais), a chave de seus pais serao armazenados em seus vetores de
        inteiros. O loop termina quando a e b forem raizes de arvores.
    */
    int i=1, j=1;
    while (1) {
        if (a) {
            a = buscar_pai (arvores, a->chave);
            if (a)
                ancestrais_a[i++] = a->chave;
        }

        if (b) {
            b = buscar_pai (arvores, b->chave);
            if (b)
                ancestrais_b[j++] = b->chave;
        }

        if (!a && !b)
            break;
    }


    /*  Encontra o primeiro valor (chave mais baixa) que aparece nos dois
        vetores de inteiros e o impreme.
    */
    for (i=0; i<tam_floresta; i++) {
        for (j=0; j<tam_floresta; j++) {
            if (ancestrais_a[i] == ancestrais_b[j] && (ancestrais_a[i] != 0)) {
                printf ("%d\n", ancestrais_a[i]);
                free (ancestrais_a);
                free (ancestrais_b);
                return;
            }
        }
    }

}



/*  Percorre a floresta, primeiro em profundidade (descendo atraves dos filhos)
    e depois em largura (atraves dos irmaos) e retorna um apontador para o no
    cuja chave esta sendo buscada.
*/
no* buscar (no *arvores, int n_buscado) {

    if (arvores->chave == n_buscado)
        return arvores;

    if (arvores->filho) {
        no *busca = NULL;
        if ((busca = buscar (arvores->filho, n_buscado)))
            return busca;
    }

    if (arvores->irmao)
        return buscar (arvores->irmao, n_buscado);

    return NULL;
}



/* Retorna um apontador para o pai de um no cuja chave é passada como parametro.
*/
no *buscar_pai (no *arvore, int filho) {

    // Raizes de arvores nao possuem pai.
    if (arvore->chave == filho)
        return NULL;

    no *aux = arvore->filho;
    while (aux){
        if (aux->chave == filho)
            return arvore;
        if (aux->filho) {
            no *busca = NULL;
            if ((busca = buscar_pai(aux, filho)))
                return busca;
        }
        aux = aux->irmao;
    }

    //  Percorre a arvore em largura.
    if (arvore->irmao)
        return buscar_pai (arvore->irmao, filho);

    //  Caso o no com chave procurada nao esteja na floresta.
    return NULL;
}



/*  Libera a memoria utilizada pela floresta.
    Inicia no ultimo filho da primeira arvore, libera as subarvores que unem
    esse no a raiz. Em seguida, libera as arvores seguintes (irmas).
*/
void liberar_arvores (no* arvore) {

    no *aux = arvore->irmao;

    if (arvore->filho)
        liberar_arvores (arvore->filho);

    free (arvore);

    if (aux)
        liberar_arvores (aux);
    return;
}
