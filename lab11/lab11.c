//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab 11 - Escala de edicoes com grafo.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "lab11.h"


int main(){

    int n_words = 0;
    char temp[21];
    node *dictionary = NULL;

    while (scanf("%s", temp) != EOF) {

    	create_node(&dictionary, temp, n_words);
    	n_words++;

    }

    /*  Inicializa o vetor de bits que indica se um vertice ja foi visitado
        na busca em largura.
        n_bytes é a quantidade de chars que o vetor de bits ocupara. É
        arredondado para cima para que nenhum bit seja deixado de fora.
    */
    int n_bytes = n_words / CHAR_BIT;
    if (n_words % CHAR_BIT != 0)
        n_bytes ++;
    char *marks = calloc (n_bytes, sizeof(char));


    /*  O grafo é criado.
    */
    create_graph(dictionary);


    /*  Fila de inteiros que armazena a chave dos vertices a serem visitados
        pela busca em largura.
    */
    int *queue = malloc (n_words * sizeof(int));


    node *position = dictionary;
    int maximum = 0;


    /*  Realiza a busca em largura iniciando em todos os vertices possiveis.
        A maior distancia é armazenada em maximum.
    */
    while (position != NULL) {

    	int aux = width_search (dictionary, marks, n_bytes, position, queue,
            n_words);
    	if (aux > maximum)
    	    maximum = aux;
    	position = position->next;
    }


    printf("%d\n", maximum);


    /*  Libera toda a memoria alocada dinamicamente.
    */
    free_memory (&dictionary);
    free (marks);
    free (queue);

    return 0;
}
