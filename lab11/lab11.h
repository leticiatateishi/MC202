//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab 11 - Escala de edicoes com grafo.


#include <stdio.h>
#include <stdlib.h>



/*  Struct que representa uma palavra no dicionario.
    Armazena a palavra, a distancia desta ao inicio do grafo (quando percorrido
    em largura), um apontador para a proxima palavra e um vetor de inteiros que
    armazena a chave de seus vizinhos.
*/
typedef struct node {
    char word[21];
    int key;
    int distance;
    struct node *next;
    int *edges;
} node;



/*  Adiciona vertices a lista de nos dicionario.
*/
void create_node (node **dictionary, char new_word[21], int i);



/*  Procura um vertice com a chave passada por parametro e retorna um apontador
    para esse no.
*/
node *search_key (int key, node * dictionary);



/*  Monta um grafo a partir do dicionario dado.
    Relaciona as palavras que possuem apenas um passo de edicao de diferenca.
*/
void create_graph(node * dictionary);



/*  Compara duas palavras e retorna a quantidade de letras diferentes que ha
    entre elas.
    Retorna -1 caso as duas palavras nao possuam o mesmo tamanho.
*/
int compare_words(char first_word[21], char second_word[21]);



/*  Busca em largura.
    Calcula a distancia de todos os vertices a partir de position.
*/
int width_search (node *dictionary, char *marks, int n_bytes, node *position,
    int *queue, int n_words);



/*  Torna o bit que esta na posicao key verdadeiro (== 1).
*/
void bit_true (char *marks, int key);



/*  Verifica se o bit que esta na posicao key é verdaeiro ou falso.
    Retorna o valor do bit na posicao key.
*/
int check_bit (char *marks, int key);



/*  Zera as distancias de todos os vertices e os chars do vetor de bits, para
    que a busca em largura possa ser realizada novamente.
*/
void null_nodes(node * dictionary, char *marks, int n_bytes);



/*  Libera a memoria alocada dinamicamente para os vertices e para os vetores
    de vizinhos (edges) de cada vertice.
*/
void free_memory(node ** dictionary);
