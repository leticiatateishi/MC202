//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab 11 - Escala de edicoes com grafo.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "lab11.h"



void create_node (node **dictionary, char new_word[21], int i) {

    node *new_node = malloc (sizeof(node));

    strcpy(new_node->word, new_word);
    new_node->key = i;
    new_node->distance = 0;


    /*  A primeira posicao do vetor de arestas armazena a quantidade de
        vizinhos de uma palvra (inicilamente igual a zero). A segunda posicao
        armazena o tamanho do vetor (inicialmente cinco). A capacidade do vetor
        inicial é de tres vizinhos, mas ocorre realocacao caso necessario.
    */
    new_node->edges = malloc (5*sizeof(int));
    new_node->edges[0] = 0;
    new_node->edges[1] = 5;


    /*  O novo vertice é inserido no inicio do dicionario.
    */
    new_node->next = *dictionary;
    *dictionary = new_node;

}




node *search_key (int key, node *dictionary){

    node *temp = dictionary;

    /*  Percorre todo o dicionario comparando as chaves.  */
    while (temp != NULL) {

        /*  Retorna o vertice cuja chave é buscada.  */
    	if (key == temp->key)
    	    return temp;

    	temp = temp->next;
    }

    return NULL;
}




void create_graph (node *dictionary){

    node *first_word = dictionary;
    node *second_word;

    while (first_word != NULL) {

    	second_word = dictionary;

    	while (second_word != NULL) {

    	    /*  Verifica a quantidade de letras diferentes entre todas as
    	       palavras do dicionario, duas a duas.
            */
    	    int n_letters = compare_words(first_word->word, second_word->word);


    	    /*  Se elas estiverem a um passo de edicao uma da outra.  */
    	    if (n_letters == 1) {


                /*  position é a posicao onde deve ser inserida a nova aresta
                    no vetor de vizinhos edge.
                    size é o tamanho do vetor de vizinhos edge.
                */
                int position = first_word->edges[0] + 2;
                int size = first_word->edges[1];


                /*  Se position for menor do que o tamanho do vetor de arestas,
                    a segunda palavra pode ser diretamente inserida como vizinha
                */
                if (position < size) {
                    first_word->edges[0] ++;
                    first_word->edges[position] = second_word->key;
                }


                /*  Se nao houver espaco no vetor para insercao, este é
                    realocado, e so entao o vizinho é inserido.
                */
                else {
                    first_word->edges =
                        (int*) realloc (first_word->edges, 2*size*sizeof(int));
                    first_word->edges[1] *= 2;
                    first_word->edges[0] ++;
                    first_word->edges[position] = second_word->key;
                }

    	    }

    	    second_word = second_word->next;
    	}

    	first_word = first_word->next;
    }
}




int compare_words(char first_word[21], char second_word[21]) {

    int i, different_letters = 0;
    int first_size = strlen (first_word);
    int second_size = strlen (second_word);


    /*  Caso as duas palavras nao tenham o mesmo tamanho, nao sao comparadas
        e a funcao retorna -1.
    */
    if (first_size != second_size)
	   return -1;


    /*  Percorre as duas palavras simultaneamente e conta as letras que estao
        na mesma posicao e sao diferentes.
    */
    for (i = 0; i < first_size; i++) {
    	if (first_word[i] != second_word[i])
    	    different_letters++;
    }


    return different_letters;
}



int width_search (node *dictionary, char *marks, int n_bytes, node *position,
    int *queue, int n_words) {

    int maximum = 0;


    /*  Zera as distancias armazenadas em todos os nos e o vetor de bits.
    */
    null_nodes (dictionary, marks, n_bytes);


    /*  Marca a posicao inicial como ja visitada.
    */
    bit_true (marks, position->key);


    /*  q_start indica o inicio da fila e é utilizado para desinfilerar um
        vertice.
        q_end indica a posicao posterior ao fim da fila e é utilizado para
        inserir um novo vertice a fila.
    */
    int q_start = 0, q_end = 1;
    queue[q_start] = position->key;


    while (q_start < n_words) {

        if (position != NULL) {

            /*  O vertice em q_start é desenfilerado.  */
            q_start ++;
            int pos_edge = 2;


            /*  Enquanto pos_edge percorre todas as posicoes de position->edges
                que sao ocupadas por chaves de vizinhos.
                (A posicao zero de edges armazena a quantidade de vizinhos).
            */
            while (pos_edge <= 1 + position->edges[0]) {


                /*  Se tal vizinho ainda nao foi visitado pela busca em largura.
                */
                if (!check_bit (marks, position->edges[pos_edge])) {

                    /*  O vertice do vizinho é procurado e apontado por
                        found_node.
                    */
                    node *found_node = search_key (position->edges[pos_edge],
                        dictionary);
                    if (found_node != NULL) {


                        /*  Sua distancia é incrementada de um em comparacao
                            ao de seu antecessor.
                       */
                        found_node->distance = position->distance + 1;
                        if (found_node->distance > maximum)
                            maximum = found_node->distance;


                        /*  O vizinho é enfileirado e sua chave é marcada como
                            ja visitado pela busca.
                        */
                        queue[q_end] = found_node->key;
                        bit_true (marks, found_node->key);
                        q_end ++;
                    }
                }

                pos_edge ++;
            }

            if (q_start < q_end)
                position = search_key (queue[q_start], dictionary);
        }
    }

    return maximum;
}




void bit_true (char *marks, int key) {

    /*  Calcula em qual byte a chave esta.
    */
    int pos_byte = key / CHAR_BIT;


    /*  Utiliza uma mascara com o operador OU para tornar o bit verdadeiro.
        A mascara é shift-left de 1 com o resto da divisao inteira da chave
        pela quantidade de bits em um char, ou seja, a posicao do bit dentro
        do byte.
    */
    marks[pos_byte] = (marks[pos_byte] | (1 << (key%CHAR_BIT)));
}




int check_bit (char *marks, int key) {

    /*  Calcula em qual byte a chave esta.
    */
    int pos_byte = key / CHAR_BIT;


    /*  Utiliza uma mascara com o operador E para verificar o valor do bit.
        A mascara é shift-left de 1 pela posicao do bit dentro do byte.
    */
    return ((marks[pos_byte] & (1<<(key%CHAR_BIT))) > 0);
}




void null_nodes (node *dictionary, char *marks, int n_bytes) {

    node *temp = dictionary;

    /*  Zera as distancias.
    */
    while (temp != NULL) {
    	temp->distance = 0;
    	temp = temp->next;
    }

    /*  Zera o vetor de bits.
    */
    for (int i = 0; i < n_bytes; i ++)
        marks[i] = 0;
}




void free_memory (node **dictionary) {

    node *temp;

    while (*dictionary != NULL) {
    	temp = *dictionary;
    	*dictionary = (*dictionary)->next;
        free (temp->edges);
    	free(temp);
    }
}
