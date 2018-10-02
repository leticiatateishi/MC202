//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab 13 - Crise na Krakovia


#include <stdio.h>
#include <stdlib.h>
#include "lab13.h"


/*  Encontra o menor caminho para percorrer todas as salas e imprime o
    tempo total necessario.
*/
void menor_caminho (corredor *salas, int vertice, corredor *antecessor) {


    corredor *vizinhos[50] = {0};
    int cont_vizinhos = 0;


    /*  Analisa os corredores entre "vertice" e todas as outras salas.
    */
    for (int i = 0; i < 50; i++) {

        /*  Nao avalia se ha corredor entre uma sala e ela mesma.
        */
        if (i == vertice)
            continue;

        /*  Tambem ignora o corredor entre o vertice atual e seu antecessor,
            para que nao ocorra volta para um antecessor antes que todos os
            vizinhos de vertice sejam visitados.
        */
        corredor* pos = salas+calcular_indice(i, vertice);
        if(pos == antecessor)
            continue;

        /*  Se existir corredor entre as duas salas.
        */
        if (pos->custo != 0) {

            /*  Atualiza os custos de ida e de volta do corredor atual como
                sendo APENAS igual ao proprio custo do corredor.
            */
            pos->ida += pos->custo;
            pos->volta += pos->custo;

            /*  Visita o vizinho.
            */
            menor_caminho (salas, i, pos);

            /*  Apos vizitar o vizinho, este passa a ser apontado pelo vetor
                de apontadores "vizinho".
            */
            vizinhos[cont_vizinhos] = pos;
            cont_vizinhos++;
        }

    }


    /*  Se houver pelo menos um vizinho, o de custo de volta maior é movido
        para o inicio do vetor.
    */
    if (cont_vizinhos > 0)
        maior_vizinho (vizinhos, cont_vizinhos);

    else
        return;


    /*  Se o vertice atual nao for a sala inicial (de acesso), atualizamos
        o valor do corredor antecessor, para que ele seja a soma do custo
        entre antecessor-vertice atual com o custo entre vertice atual-vizinho
        (para todos os vizinhos apontados pelo vetor de apontadores, exceto
        o primeiro, que possui o maior custo de volta).
        Depois, somamos ainda apenas a ida do vizinho mais caro.
        Na volta do corredor antecessor-vertice atual, somamos apenas a volta
        do vertice mais caro. Dessa maneira, acumulamos sempre a volta mais
        cara.
    */
    if (vertice != 0) {

        for (int i = 1; i < cont_vizinhos; i++) {
            antecessor->ida += (*(vizinhos + i))->ida;
            antecessor->ida += (*(vizinhos + i))->volta;
        }

        antecessor->ida += (*vizinhos)->ida;
        antecessor->volta += (*vizinhos)->volta;
    }



    /*  Quando terminamos de visitar todos os vizinhos do vertice zero, todas
        as salas ja foram percorridas. Assim, o custo do percuros total deve
        ser a soma de ida para TODOS os vizinhos de zero com todas as voltas,
        exceto a do primeiro vizinho (que possui volta mais cara).
    */
    else {
        int resultado = 0;

        for (int i = 1; i < cont_vizinhos; i++) {
            resultado += (*(vizinhos+i))->ida;
            resultado += (*(vizinhos+i))->volta;
        }

        resultado += (*vizinhos)->ida;
        printf ("%d\n", resultado);
    }



}




/*  Recebe o vetor de apontador para corredores e a quantidade de vizinhos
    que ele armazena. Percorre esse vetor e aponta em "maior" o registro que
    possuir maior valor de volta. No final, troca a ordem do registro
    apontado por "maior" com o primeiro registro do vetor.
*/
void maior_vizinho (corredor *vizinhos[], int tamanho) {

    corredor *maior = vizinhos[0];
    int posicao = 0;

    /*  Percorre todas os vizinhos e encontra o de maior valor de volta.
    */
    for (int i = 1; i < tamanho; i++) {
        if ((*(vizinhos+i))->volta > maior->volta) {
            maior = *(vizinhos+i);
            posicao = i;
        }
    }

    /*  Coloca o vizinho de maior custo de volta no inicio do vetor.
    */
    if (maior != vizinhos[0]) {
        corredor *aux = vizinhos[0];
        vizinhos[0] = maior;
        (*(vizinhos+posicao)) = aux;

    }

}




/*  Limpa todas as salas, zerando as structs.
*/
void limpar_salas (corredor *salas) {

    for (int i = 0; i < soma_pa(50); i++) {
        (salas+i)->custo = 0;
        (salas+i)->ida = 0;
        (salas+i)->volta = 0;
    }
}




/*  Calcula a posicao do corredor entre a e b no vetor salas (matriz triangular
    inferior representada como vetor linear).
    Para calcular o indice, devemos fazer a soma da pa com n igual ao maior
    dos dois numeros, e somar o segundo numero ao final.
*/
int calcular_indice (int a, int b) {

    if (a > b)
        return soma_pa(a)+b;
    return soma_pa(b)+a;
}




/*  Retorna a soma da pa de n, para calcular o indice na linearizacao da
    matriz de corredores sala.
*/
int soma_pa (int n) {
    return (((n-1)*n)/2);
}
