#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct no {
   char chave;
   struct no *esquerda;
   struct no *direita;
} no;

/* Imprime a arvore em pos-ordem: primeiro imprime a subarvore esquerda, depois
   a subarvore direita e, por fim, a raiz.
*/
void imprimir (no* raiz) {

   if (raiz) {
      imprimir (raiz->esquerda);
      imprimir (raiz->direita);
      printf ("%c", raiz->chave);
   }
}



/* Utiliza a mesma logica de imprimir em pos-ordem para destruir a arvore, pois
   libera memoria de "baixo para cima", para que nao haja liberacao de um no
   que da acesso a outro que tambem precisa ser liberado.
*/
void destruir (no* raiz) {

   if (raiz) {
      destruir (raiz->esquerda);
      destruir (raiz->direita);
      free (raiz);
   }
}



/*
*/
void reconstruir (no* raiz, int posicao, char* pre_ordem, int *pos_letras) {

   if (posicao == strlen (pre_ordem)-1)
      return;

   if (pos_letras[posicao+1] <= pos_letras[posicao]+1) {
      no *filho_esquerda = malloc (sizeof (no));
      filho_esquerda->chave = pre_ordem[posicao+1];
      filho_esquerda->esquerda = filho_esquerda->direita = NULL;
      raiz->esquerda = filho_esquerda;
      reconstruir (filho_esquerda, posicao+1, pre_ordem, pos_letras);
   }

   int i;
   for (i=0; i<(strlen(pre_ordem) - posicao-1); i++) {
      int pos_menor=0, pos_maior=0, j;
      for (j=0; j<strlen(pre_ordem); j++) {
         if (pos_letras[j] == posicao)
            pos_menor = j;
         if (pos_letras[j] == posicao+1+i)
            pos_maior = j;
      }
      if (pos_letras[posicao+1+i] > 1+pos_letras[posicao] && pos_maior > pos_menor) {
         no *filho_direita = malloc (sizeof(no));
         filho_direita->chave = pre_ordem[posicao+1+i];
         filho_direita->esquerda = filho_direita->direita = NULL;
         raiz->direita = filho_direita;
         reconstruir (filho_direita, posicao+1+i, pre_ordem, pos_letras);
         break;
      }
   }

}
