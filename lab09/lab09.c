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



unsigned long funcao1 (unsigned char *palavra);
unsigned long funcao1 (unsigned char *palavra);
int busca (hash *tabela, int *ocupacao, unsigned char *palavra);
int inserir (hash *tabela, int *ocupacao, unsigned char *str_inserir, int x);
void remover (hash *tabela, int *ocupacao, unsigned char *string);



int main () {

    char comando;
    unsigned char palavra[251];
    int n_indice = 0;

    hash* tabela = malloc (8000 * sizeof(hash));


    /*  Indica a ocupacao de cada posicao do hash.
        Se ocupacao[x] == 0, hash[x] esta vazio.
           ocupacao[x] == -1, hash[x] foi removido.
           ocupacao[x] == 1, hash[x] esta ocupado.
    */
    int *ocupacao = calloc (8000, sizeof(int));


    while (1) {
        scanf ("%c", &comando);

        if (comando == 'i') {
            scanf (" %s\n", palavra);

            //  Incrementa o valor do indice caso a insercao seja feita
            if (inserir (tabela, ocupacao, palavra, n_indice) == 1)
                n_indice ++;
        }


        else if (comando == 'b') {
            scanf ("%s\n", palavra);
            int b = busca (tabela, ocupacao, palavra);
            if (b == -1 || ocupacao[b] != 1)
                printf ("nao encontrado\n");
            else
                printf ("encontrado %d\n", (*(tabela + b)).indice);
        }


        else if (comando == 'r') {
            scanf ("%s\n", palavra);
            remover (tabela, ocupacao, palavra);
        }

        else
            break;
    }


    free (ocupacao);
    free (tabela);

    return 0;
}
