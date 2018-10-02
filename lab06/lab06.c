// Leticia Mayumi Araujo Tateishi - RA 201454

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab06.h"


int main () {
   char comando[20];
   no *raiz = NULL;

   while (1) {
      scanf ("%s", comando);

      /* Insere um elemento na arvore caso ele ja nao esteja nela.
         Caso contrario, nada ocorre.
      */
      if (!strcmp (comando, "inserir")) {
         int chave_inserir;
         scanf ("%d", &chave_inserir);
         inserir (&raiz, chave_inserir);
      }


      /* Exclui um elemento da arvore caso ele ja esteja nela.
         Caso contrario, nada ocorre.
      */
      else if (!strcmp (comando, "excluir")) {
         if (raiz) {
            int chave_excluir;
            scanf ("%d", &chave_excluir);
            excluir (&raiz, chave_excluir);
         }
      }


      /* Busca a chave na arvore de busca binaria.
         Imprime "pertence" caso o elemento seja encontrado.
         Imprime "nao pertence" caso contrario.
      */
      else if (!strcmp (comando, "buscar")) {
         int chave_buscada;
         scanf ("%d", &chave_buscada);
         if (buscar (raiz, chave_buscada))
            printf ("pertence\n");
         else
            printf ("nao pertence\n");
      }


      /* Imprime o valor da menor chave presente na arvore.
      */
      else if (!strcmp (comando, "minimo")) {
         int menor = minimo (raiz);
         if (menor == -1)
            printf ("vazia\n");
         else
            printf ("%d\n", menor);
      }


      /* Imprime o valor da maior chave presente na arvore.
      */
      else if (!strcmp (comando, "maximo")) {
         int maior = maximo (raiz);
         if (maior == -1)
            printf ("vazia\n");
         else
            printf ("%d\n", maior);
      }


      /* Imprime a arvore em pos ordem.
      */
      else if (!strcmp (comando, "pos-ordem")) {
         if (!raiz)
            printf ("vazia");
         else
            pos_ordem (raiz);
         printf ("\n");
      }


      /* Imprime a arvore em ordem crescente.
      */
      else if (!strcmp (comando, "em-ordem")) {
         if (!raiz)
            printf ("vazia");
         else
            em_ordem (raiz);
         printf ("\n");
      }


      /* Imprime a arvore em pre ordem
      */
      else if (!strcmp (comando, "pre-ordem")) {
         if (!raiz)
            printf ("vazia");
         else
            pre_ordem (raiz);
         printf ("\n");
      }


      /* Imprime a arvore por camadas, da raiz as folhas e da esquerda a direita
      */
      else if (!strcmp (comando, "largura")) {
         if (!raiz)
            printf ("vazia");
         else
            chamar_largura(raiz);
         printf ("\n");
      }


      /* Libera memoria e interrompe o laco de leitura.
      */
      else if (!strcmp (comando, "terminar")) {
         terminar (raiz);
         break;
      }
   }

   return 0;
}
