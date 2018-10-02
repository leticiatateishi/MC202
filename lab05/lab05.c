#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct no {
   char chave;
   struct no *esquerda;
   struct no *direita;
} no;

void imprimir (no* raiz);
void destruir (no* raiz);
void reconstruir (no* raiz, int posicao, char* pre_ordem, int *pos_letras);


int main (){

   char em_ordem[1000], pre_ordem[1000];

   while (scanf ("%s", pre_ordem) != EOF) {
      scanf ("%s", em_ordem);

      /* pos_letras possui a mesmo tamanho da arvore. Uma posicao n no vetor
         representa a mesma posicao n da string em ordem. O n-esimo inteiro de
         pos_letras indica a posicao da n-esima letra da string em_ordem na
         string da pre_ordem. */
      int *pos_letras = malloc (strlen(pre_ordem) * sizeof (int));
      int i, j;
      for (i=0; i<strlen(pre_ordem); i++) {
         for (j=0; j<strlen(pre_ordem); j++){
            if (pre_ordem[j] == em_ordem[i]) {
               pos_letras[i] = j;
            }
         }
      }

      /* A posicao da raiz (primeira letra da string pre-ordem) divide a string
         em ordem em duas: a letras anteriores a pos_raiz pertencem a subarvore
         esquerda, enquanto as posteriores pertencem a subarvore direita */
      int pos_raiz = pos_letras[0];

      no *raiz = malloc (sizeof(no));
      raiz->direita = raiz->esquerda = NULL;
      raiz->chave = pre_ordem[0];
      reconstruir (raiz, 0, pre_ordem, pos_letras);

      imprimir (raiz);
      destruir (raiz);
      printf ("\n");
   }
}
