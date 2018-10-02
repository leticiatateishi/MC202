//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab09 - dicionario baseado em uma tabela de hashing com sondagem usando
//  hashing duplo.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct hash {
    int indice;
    unsigned char chave[251];
} hash;



unsigned long funcao1 (unsigned char *palavra) {

    unsigned long resultado = 5381;
    int c;

    /*  Enquanto a string nao terminar, calcula (resultado * 2^5) + resultado +
        c, sendo c = valor do caracter atual transformado em inteiro.
    */
    while ((c = *palavra ++))
        resultado = ((resultado << 5) + resultado) + c;

    return resultado;
}



unsigned long funcao2 (unsigned char *palavra) {

    unsigned long resultado = 3759;
    int c;

    /*  Enquanto a string nao terminar, calcula (resultado * 4) + resultado +
        c, sendo c = valor do caracter atual transformado em inteiro.
    */
    while ((c = *palavra++))
        resultado = ((resultado << 2) + resultado) + c;

    return resultado;
}



/*  Retorna a posicao da palavra buscada, se ela estiver no dicionario.
    Retorna a posicao da primeira palavra vazia, caso contrario.
    Retorna -1 se a palavra nao estiver no dicionario e nao houver espaco vazio
    para que ocorra a insercao.
*/
int busca (hash *tabela, int *ocupacao, unsigned char *palavra) {

    int i = 0;
    unsigned long resultado1, resultado2;
    int posicao;


    // Calcula a funcao de hash duplo com incremento unitario
    resultado1 = funcao1 (palavra);
    resultado2 = funcao2 (palavra);

    while (1) {

        posicao = (resultado1 + (i * resultado2) ) % 8000;


        // Caso a chave nao tenha sido encontrada em nenhuma posicao
        if (posicao == resultado1 && i != 0)
            return -1;


        // Caso uma posicao vazia seja encontrada
        else if (ocupacao[posicao] == 0)
            return posicao;


        // Caso a chave buscada seja encontrada
        else if ( !strcmp ( (*(tabela + posicao)).chave, palavra))
            return posicao;


        i++;
    }
}



/*  Retorna 1 caso a insercao seja realizada com exito.
    Retorna 0 caso contrario.
*/
int inserir (hash *tabela, int *ocupacao, unsigned char *str_inserir, int x) {

    int posicao = busca (tabela, ocupacao, str_inserir);

    // Caso nao haja espaco para insercao ou a chave ja esteja no dicionario.
    if (posicao == -1 || ocupacao[posicao] == 1)
        return 0;

    ocupacao[posicao] = 1;
    strcpy ( (*(tabela + posicao)).chave, str_inserir);
    (*(tabela + posicao)).indice = x;
    return 1;
}



/*  Procura a palavra a ser removida no dicionario.
    Se ela estiver presente, remove-a com a alteracao de sua posicao no Vetor
    de inteiros ocupacao.
*/
void remover (hash *tabela, int *ocupacao, unsigned char *string) {

    int posicao = busca (tabela, ocupacao, string);

    if (posicao != -1 && ocupacao[posicao] == 1)
        ocupacao[posicao] = -1;

}
