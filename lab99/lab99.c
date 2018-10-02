//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab 99 - Conjunto em vetor de bits.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "bits.h"


int main () {

    char command[15];
    char *array;
    int size, bit, n_bytes;

    while (1) {

        scanf ("%s", command);


        /*  Cria um vetor que indica um conjunto.
            Calcula a quantidade de bytes que serao necessarios para armazenar
            os bits e aloca a memoria em chars.
        */
        if (!strcmp (command, "create")) {

            scanf ("%d\n", &size);
            free (array);
            n_bytes = (size / CHAR_BIT) + 1;
            array = create_array (n_bytes);
        }


        /*  Adiciona um elemento ao conjunto.
            Torna tal bit verdadeiro (1bit).
        */
        else if (!strcmp (command, "add")) {

            scanf ("%d\n", &bit);
            bit_true (array, bit-1);
        }


        /*  Remove um elemento do conjunto.
            Torna o bit falso (0).
        */
        else if (!strcmp (command, "remove")) {

            scanf ("%d\n", &bit);
            bit_false (array, bit-1);
        }


        /*  Verifica se um elemento pertence ao conjunto.
            Analisa se o bit é verdadeiro (1) ou falso (0).
        */
        else if (!strcmp (command, "in")) {

            scanf ("%d\n", &bit);
            if (!check_bit (array, bit-1))
                printf ("belongs(%d) = false\n", bit);
            else
                printf ("belongs(%d) = true\n", bit);
        }


        /*  Recebe um numero como parametro e verifica quantos elementos sao
            menores ou iguais a ele.
            Conta quantos bits são verdadeiros, do início até a posicao desejada
        */
        else if (!strcmp (command, "rank")) {

            int count = 0;
            scanf ("%d\n", &bit);

            if (bit > size) {
                printf ("rank(%d) = 0\n", bit);
                continue;
            }

            for (int i = 0; i < bit; i++) {
                if (check_bit (array, i))
                    count ++;
            }

            printf ("rank(%d) = %d\n", bit, count);
        }


        /*  Verifica qual o i-esimo elemento da lista.
            Desde o inicio do vetor, passa por todos os i-1 bits verdadeiros
            e imprime a posicao do i-esimo bit verdadeiro.
        */
        else if (!strcmp (command, "select")) {

            scanf ("%d\n", &bit);
            int count = 0, i;

            for (i = 0; i < size; i++) {
                if (check_bit (array, i))
                    count ++;
                if (count == bit) {
                    printf ("select(%d) = %d\n", bit, i+1);
                    i = size + 1;
                }
            }

            if (i == size)
                printf ("select(%d) = 0\n", bit);

        }


        /*  Verifica quantos elementos ha no intervalo [start, end].
            Conta quantos bits sao positivos nesse intervalo.
        */
        else if (!strcmp (command, "rangecount")) {

            int start, end, count = 0;
            scanf ("%d %d\n", &start, &end);

            for (int i = start; i <= end; i++) {
                if (check_bit (array, i-1))
                    count ++;
            }

            printf ("rangecount(%d,%d) = %d\n", start, end, count);

        }


        /*  Imprime todos os elementos do conjunto.
            Imprime os bits verdadeiros do vetor.
        */
        else if (!strcmp (command, "print")) {

            int n_elements = count_elements (array, size);
            int count = 0;

            printf ("S = {");
            for (int i = 0; i < size; i++) {
                if (check_bit (array, i)) {
                    if (count < n_elements-1)
                        printf ("%d,", i+1);
                    else
                        printf ("%d", i+1);
                    count ++;
                }
            }
            printf ("}\n");
        }

        else
            break;
    }


    free (array);
}
