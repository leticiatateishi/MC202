//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Lab 99 - Conjunto em vetor de bits.


#include <stdio.h>


/*  Cria um vetor de bits com n_bytes chars.
*/
char* create_array (int n_bytes);

/*  Torna um bit verdadeiro.
*/
void bit_true (char *array, int key);

/*  Torna um bit falso.
*/
void bit_false (char *array, int key);

/*  Verifica se um bit é verdadeiro ou falso.
*/
int check_bit (char *array, int key);

/*  Conta a quantidade de bits verdadeiros no vetor.
*/
int count_elements (char *array, int size);
