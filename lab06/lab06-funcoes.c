// Leticia Mayumi Araujo Tateishi - RA 201454

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab06.h"


/* Insere a chave na arvore de busca binaria.
   Caso este elemento ja esteja na arvore, a funcao retorna 1 e a insercao nao
   ocorre.
   Retorna 0 se a insercao for bem sucedida.
*/
void inserir (no **raiz, int chave_inserir) {
   no* existente = buscar ((*raiz), chave_inserir);
   if (existente)
      return;

   no *novo = malloc (sizeof (no));

   // Verifica se ha memoria para a insercao
   if (!novo){
      printf ("memoria insuficiente\n");
      return;
   }

   novo->chave = chave_inserir;
   novo->esquerda = novo->direita = NULL;

   // Se a arvore estiver vazia
   if (!(*raiz)) {
      *raiz = novo;
      return;
   }

   no *posicao = *raiz, *pai = NULL;

   // Encontra a posicao onde sera feita insercao, que sera apontada por pai
   while (posicao) {
      pai = posicao;
      if (posicao->chave > chave_inserir)
         posicao = posicao->esquerda;
      else
         posicao = posicao->direita;
   }

   // Verifica se a insercao sera feita a direita ou a esquerda
   if (chave_inserir > pai->chave)
      pai->direita = novo;

   else
      pai->esquerda = novo;

}



/* Exclui a chave na arvore de busca binaria.
   Caso este elemento nao exista na arvore, nada ocorre.
   Se o elemento removido possuir dois filhos, seu sucessor é utilizado na
   substituicao.
*/
void excluir (no** raiz, int chave_excluir) {

   // Verifica se o no a ser excluido esta na arvore
   no* no_excluir = buscar ((*raiz), chave_excluir);

   // Se o no a ser excluido nao estiver na arvore
   if (!no_excluir)
      return;


   // Se o no a ser excluido for a raiz
   if (chave_excluir == (*raiz)->chave) {

      // Se nao houver filho da direita, a raiz passa a ser o filho da esquerda
      if (!(*raiz)->direita) {
         no *aux = (*raiz);
         (*raiz) = (*raiz)->esquerda;
         free (aux);
         return;
      }

      // No a ser excluido passa a ser o sucessor da raiz
      no *sucessor = buscar ((*raiz)->direita, minimo ((*raiz)->direita));
      no *pai = buscar_pai (*raiz, sucessor);

      // A chave da raiz é atualizada para seu sucessor
      (*raiz)->chave = sucessor->chave;


      // Se o pai for a raiz
      if (pai->chave != sucessor->chave)
         pai->esquerda = sucessor->direita;

      // Se o pai do sucessor nao for a raiz
      else if (pai->chave == sucessor->chave)
         pai->direita = sucessor->direita;

      // Aponta pra nulo o filho onde antes estava o no que foi excluido
      if (pai->chave > sucessor->chave)
         pai->esquerda = NULL;
      else if (pai->chave < sucessor->chave)
         pai->direita = NULL;

      free (sucessor);
      return;
   }


   no* pai = buscar_pai ((*raiz), no_excluir);


   // Se o no a ser excluido nao possuir filhos, ou seja, se for uma folha,
   // nenhuma manipulacao de ponteiros é necessaria.
   if (!no_excluir->direita && !no_excluir->esquerda && pai) {
      if (pai->esquerda && pai->esquerda->chave == chave_excluir)
         pai->esquerda = NULL;
      else if (pai->direita && pai->direita->chave == chave_excluir)
         pai->direita = NULL;
      free (no_excluir);
      return;
   }


   no* sucessor = sucessao ((*raiz), no_excluir);


   // Se houver sucessor
   if (sucessor) {

   // Os filhos da esquerda do no a ser excluido serao filhos da esquerda do
   // sucessor, que, por regra, nao pode possuir filhos da esquerda por possuir
   // a menor chave maior que a chave a ser excluida
      if (no_excluir->esquerda)
         sucessor->esquerda = no_excluir->esquerda;


      // Se o sucessor possuir filho da direita e o no excluido tambem.
      // O extremo maximo de sucessor->direito apontara a no_excluir->direita.
      if (sucessor->direita && no_excluir->direita && no_excluir->direita->chave != sucessor->chave) {
         no *aux = malloc (sizeof(no));
         aux = buscar ((*raiz), maximo(sucessor));
         aux->direita = no_excluir->direita;
         sucessor->direita = no_excluir->direita;
      }

      // Se o sucessor nao for a raiz, seu pai é buscado.
      if (sucessor->chave != (*raiz)->chave) {
         no* pai_sucessor = buscar_pai(*raiz, sucessor);

         // Se o pai do sucessor nao for o no a ser excluido, a posicao que
         // antes apontava para sucessor passa a ser nulo.
         if (pai_sucessor->chave != no_excluir->chave) {
            if (pai_sucessor->chave > sucessor->chave)
               pai_sucessor->esquerda = NULL;
            else
               pai_sucessor->direita = NULL;
         }

      }


      // Se o pai do no a ser excluido nao for o proprio sucessor, ou seja,
      // se o no a ser excluido possuir filho da direita.
      if (pai->chave != sucessor->chave) {

         // Se existirem chaves menores que a do pai e maiores que a do no a
         // ser excluido, dentre elas o proprio sucessor.
         if (no_excluir->chave < pai->chave)
            pai->esquerda = sucessor;


         // Se o no a ser excluido for filho da direita
         else {

            // Se o sucessor nao for o filho direito do no a ser excluido, ou
            // seja, se o filho da direita do no a excluir possuir subarvore
            // a esquerda.
            if (no_excluir->direita->chave != sucessor->chave){
               if (sucessor->chave < no_excluir->direita->chave)
                  sucessor->direita = no_excluir->direita;
               else
                  sucessor->esquerda = no_excluir->direita;
            }
            pai->direita = sucessor;
         }
      }

      free (no_excluir);
   }


   // Se o no a ser excluido for o maximo da arvore, seu filho da esquerda
   // passa a ser filho da direita de seu pai.
   else {
      no* pai = malloc (sizeof(no));
      pai = buscar_pai (*raiz, no_excluir);
      pai->direita = no_excluir->esquerda;
      if (pai->chave > chave_excluir)
         pai->esquerda = NULL;
      else
         pai->direita = NULL;
      free (no_excluir);
      return;
   }

}



/* Retorna um apontador par o no buscado caso este pertenca a arvore.
   Retorna nulo caso o no nao esteja na arvore.
*/
no* buscar (no *raiz, int chave_buscada) {

   if (!raiz)
      return NULL;

   else if (chave_buscada == raiz->chave)
      return raiz;;

   if (chave_buscada < raiz->chave)
      return buscar (raiz->esquerda, chave_buscada);

   else
      return buscar (raiz->direita, chave_buscada);

}



/* Retorna -1 se a arvore estiver vazia.
   Caso contrario, retorna o valor da menor chave da arvore.
*/
int minimo (no *raiz) {

   if (!raiz)
      return -1;

   /* Por se tratar de uma arvore binaria de busca, a menor chave estara
      posicionada na extrema esquerda. */
   no *posicao = raiz;
   while (posicao->esquerda != NULL)
      posicao = posicao->esquerda;
   return posicao->chave;

}



/* Retorna -1 se a arvore estiver vazia
   Caso contrario, retorna o valor da maior chave da arvore
*/
int maximo (no* raiz) {

   if (!raiz)
      return -1;

   /* Por se tratar de uma arvore binaria de busca, a maior chave estara
      posicionada na extrema direita. */
   no *posicao = raiz;
   while (posicao->direita != NULL)
      posicao = posicao->direita;
   return posicao->chave;
}



/* Imprime a arvore em pre ordem: primeiro visita a raiz, em seguida a subarvore
   esquerda e, por ultimo, a subarvore direita.
*/
void pre_ordem (no* raiz) {

   if (!raiz)
      return;

   printf ("%d ", raiz->chave);
   pre_ordem (raiz->esquerda);
   pre_ordem (raiz->direita);
}



/* Imprime a arvore em pos ordem: primeiro visita a subarvore esquerda, depois
   a subarvore direita e, por ultimo, a raiz.
*/
void pos_ordem (no* raiz) {

   if (!raiz)
      return;

   pos_ordem (raiz->esquerda);
   pos_ordem (raiz->direita);
   printf ("%d ", raiz->chave);
}



/* Imprime a arvore em ordem: primeiro visita a subarvore esquerda, depois a
   raiz e, por ultimo, a subarvore direita.
*/
void em_ordem (no* raiz) {

   if (!raiz)
      return;

   em_ordem (raiz->esquerda);
   printf ("%d ", raiz->chave);
   em_ordem (raiz->direita);
}



void chamar_largura (no *raiz) {
   int *fim_arvore = calloc (1, sizeof(int));
   int nivel_desejado = 0;

   while (1){
      largura (raiz, 0, nivel_desejado, fim_arvore);
      if (fim_arvore[0] == 0)
         break;
      nivel_desejado ++;
      fim_arvore[0] = 0;
   }

   free (fim_arvore);
}



/* Imprime a arvore em largura: iniciando pela raiz, imprime todas as chaves de
   um nivel, da esquerda (menor) para a direita (maior), e em seguida desce ao
   nivel inferior.
   Nivel_atual representa a altura do no raiz, sendo a raiz inicial a altura 0.
   nivel_desejado representa o nivel que se deseja imprimir.
   A cada nivel descido, fim_arvore recebe 0, e passa a ser 1 caso haja chaves
   a serem impressas. Se ao final do nivel fim_arvore ainda possuir o valor 0,
   indica que a arvore ja foi totalmente impressa.
*/
void largura (no* raiz, int nivel_atual, int nivel_desejado, int *fim_arvore) {

   if (nivel_atual == nivel_desejado) {
      printf ("%d ", raiz->chave);
      fim_arvore[0] = 1;
      return;
   }

   if (raiz->esquerda && nivel_atual < nivel_desejado)
      largura (raiz->esquerda, nivel_atual+1, nivel_desejado, fim_arvore);

   if (raiz->direita && nivel_atual < nivel_desejado)
      largura (raiz->direita, nivel_atual+1, nivel_desejado, fim_arvore);

}



/* Desaloca a arvore e todos os seus nos.
*/
void terminar (no *raiz) {

   if (raiz) {
      terminar (raiz->esquerda);
      terminar (raiz->direita);
      free (raiz);
   }
}



/* Retorna um apontador para o sucessor de um numero, ou seja, o no que possui
   a menor chave maior que a dele proprio.
*/
no* sucessao (no *raiz, no *sucedido) {
   no *sucessor = NULL;

   if (sucedido->chave == maximo(raiz))
      return NULL;

   // O sucessor da raiz é a extremidade esquerda da subarvore direita
   if (sucedido->chave == raiz->chave) {
      sucessor = raiz->direita;
      while (sucessor->esquerda)
         sucessor = sucessor->esquerda;
      return sucessor;
   }

   // O sucessor da extremidade direita da subarvore esquerda é a raiz
   else if (maximo(raiz->esquerda) == sucedido->chave)
         return raiz;

   // A extremidade direita da arvore possui a maior chave e nao tem sucessor
   else if (maximo(raiz->direita) == sucedido->chave)
      return NULL;

   // O sucessor de um no que nao possui filho da direita é o avo
   else if (!sucedido->direita)
      return (buscar_avo(raiz, sucedido));

   // O sucessor de um no que possui filho da direita é a extremidade esquerda
   // de sua subarvore direita, ou seja, entra na primeira condicao da funcao,
   // para quando raiz = sucedido
   else if (sucedido->direita) {
      sucessor = sucessao (sucedido, sucedido);
      return sucessor;
   }

}



/* Retorna um apontador para o avo de um determinado no.
   Caso o neto esteja no segundo nivel da arvore, ou seja, se nao houver avo,
   a funcao retorna a posicao do pai (raiz).
*/
no* buscar_avo (no *raiz, no *neto) {
   no *posicao = raiz, *pai = NULL, *avo = NULL;

   while (posicao->chave != neto->chave) {
      avo = pai;
      pai = posicao;

      if (neto->chave < posicao->chave)
         posicao = posicao->esquerda;
      else
         posicao = posicao->direita;
   }

   if ((pai->esquerda && pai->esquerda->chave == neto->chave) || (!avo))
      return pai;
   return avo;
}



/* Retorna uma apontador para o pai de um no.
*/
no* buscar_pai (no *raiz, no *filho) {
   no *posicao = raiz, *pai = NULL;

   while (posicao->chave != filho->chave) {
      pai = posicao;

      if (filho->chave < posicao->chave)
         posicao = posicao->esquerda;
      else
         posicao = posicao->direita;
   }

   return pai;
}
