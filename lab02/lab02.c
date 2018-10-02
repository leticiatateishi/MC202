/* Leticia Mayumi Araujo Tateishi - RA 201454 */

#include <stdio.h>
#include <stdlib.h>

typedef struct no {
   int chave;
   int contador;
   struct no* proximo;
} no;

void criar_lista (no** lista, int n);
void zerar_lista (no* lista, int n);
int mtf (int tam_sequencia, int *sequencia, no** lista);
int tr (int tam_sequencia, int *sequencia, no** lista);
int c (int tam_sequencia, int *sequencia, no** lista);



int main (){
   int i, n, recuperacoes, *sequencia, custo_mtf, custo_tr, custo_c;
   no *lista = NULL, *p = lista;

   /* n é o tamanho da lista. A chave de cada nó recebe um numero, em ordem
      crescente, de 1 a n.
   */
   scanf ("%d", &n);
   criar_lista (&lista, n);

   /* Recuperacoes é a quantidade de chaves que serao buscadas. Sequencia é a
      ordem das chaves procuradas.
   */
   scanf ("%d", &recuperacoes);
   sequencia = malloc (recuperacoes * sizeof(int));

   for (i=0; i<recuperacoes; i++)
      scanf ("%d", &sequencia[i]);


   custo_mtf = mtf (recuperacoes, sequencia, &lista);
   zerar_lista (lista, n);
   custo_tr = tr (recuperacoes, sequencia, &lista);
   zerar_lista (lista, n);
   custo_c = c (recuperacoes, sequencia, &lista);


   printf ("%d %d %d\n", custo_mtf, custo_tr, custo_c);

   while (lista != NULL) {
      p = lista;
      lista = p->proximo;
      free (p);
   }
   free (sequencia);
   return 0;
}



/* A funcao cria n nos, preenchendo o campo chave com seu numero correspondente,
   de 1 a n, zerando o campo contador e apontando proximo para onde **lista
   inicialmente apontava. Lista passa a pontar para o mais recente elemento.
*/
void criar_lista (no** lista, int n) {
   int i;

   for (i=n; i>0; i--){
      no* elemento = malloc (sizeof(no));
      elemento->chave = i;
      elemento->contador = 0;
      elemento->proximo = *lista;
      *lista = elemento;
   }
}



/* Reinicia a lista, enumerando as chaves em ordem crescente de 1 a n.
*/
void zerar_lista (no* lista, int n) {
   int i = 1;
   no* p = lista;

   while (p != NULL){
      p->chave = i;
      p = p->proximo;
      i++;
   }
}



/* Em move-to-front, quando um arquivo é recuperado, ele é movido para o inicio
   da lista. Ao encontrar a chave desejada, o ponteiro lista passa a apontar
   para o respectivo registro, tornando-o primeiro. Um ponteiro do tipo no,
   chamado anterior, ocupa sempre uma posiçao anterior a posicao e auxilia na troca.
*/
int mtf (int tam_sequencia, int *sequencia, no** lista) {
   int i, contador = 0;
   no *posicao, *anterior;

   /* A cada iteracao, o apontador posicao retorna ao inicio da lista e anterior
      recebe nulo. Durante a busca, anterior permanece um nó atras de posicao,
      para que a troca ocorra quando posicao->chave == sequencia[i].
   */
   for (i=0; i<tam_sequencia; i++){
      posicao = *lista;
      anterior = NULL;

      while (posicao->chave != sequencia[i]){
         contador ++;
         anterior = posicao;
         posicao = posicao->proximo;
      }

      contador ++;
      if (anterior != NULL){
         anterior->proximo = posicao->proximo;
         posicao->proximo = *lista;
         *lista = posicao;
      }
   }
   return contador;
}



/* Em transpose, quando um registro é recuperado ele é trocado de posição com o
   registro que o precede, se ele ainda não estiver no início da lista.
*/
int tr (int tam_sequencia, int *sequencia, no** lista){
   int i, contador = 0;
   no *posicao, *aux, *anterior;

   for (i=0; i<tam_sequencia; i++){
      posicao = *lista;
      anterior = NULL;
      aux = NULL;

      /* Se a chave procurada pertencer ao primeiro elemento da lista, não ocorre
         alteracao na ordem dos elementos.
      */
      if (sequencia[i] == (*lista)->chave)
         contador++;

      /* Se a chave procurada for o segundo elemento da lista, inverte-se a
         posicao do primeiro e do segundo. A variavel contadora é incrementada
         de dois pois dois nos foram visitados até a chave requisitada.
      */
      else if (sequencia[i] == (*lista)->proximo->chave){
         anterior = *lista;
         posicao = (*lista)->proximo;
         *lista = posicao;
         anterior->proximo = posicao->proximo;
         posicao->proximo = anterior;
         contador = contador + 2;
      }

      /* Se a chave procurada estiver em outra posicao, que nao 1a ou 2a, o
         ponteiro posicao inicia no terceiro elemento da lista (justifica o
         inicial incremento da variavel contadora em 3, enquanto o ponteiro
         anterior aponta para o inicio da lista. A posicao avança e contador é
         incrementado até que a chave desejada seja encontrada. Entao, o no
         apontado por posicao tem sua ordem invertida pelo no apontado por
         anterior->proximo.
      */
      else {
         contador = contador + 3;
         posicao = (*lista)->proximo->proximo;
         anterior = *lista;

         while (posicao->chave != sequencia[i]){
            posicao = posicao->proximo;
            anterior = anterior->proximo;
            contador ++;
         }

         anterior->proximo->proximo = posicao->proximo;
         posicao->proximo = anterior->proximo;
         anterior->proximo = posicao;

      }
   }

   return contador;
}



/* Cada registro tem um contador do número de acessos. Quando um registro é
   recuperado o contador é incrementado e ele é movido para uma posição anterior
   a todos os registros com contador menor ou igual ao dele.
*/
int c (int tam_sequencia, int *sequencia, no** lista){
   int i;
   for (i=0; i<tam_sequencia; i++){
      no *posicao = *lista;
      no *anterior = NULL;

      /* O nó cuja chave é procurada é apontada por posicao e seu contador
         é incrementado.
      */
      while (posicao->chave != sequencia[i]){
         cont ++;
         anterior = posicao;
         posicao = posicao->proximo;
      }

      cont ++;
      posicao->contador ++;

      /* Quando a chave requisitada já está no inicio da lista
      */
      if (posicao == (*lista))
         continue;


      /* Se o contador da chave buscada for maior do que o contador do primeiro
         elemento da lista.
      */
      if ((*lista)->contador <= posicao->contador){
         anterior->proximo = posicao->proximo;
         posicao->proximo = *lista;
         *lista = posicao;
         continue;
      }

      /* Percorre a lista até posicao para encontrar nós cujos contadores são
         menores do que o que acabou de ser incrementado.
      */
      no *p = *lista;
      while (p != NULL){

         if (posicao->contador >= p->proximo->contador) {
            anterior->proximo = posicao->proximo;
            posicao->proximo = p->proximo;
            p->proximo = posicao;
            break;
         }

         p = p->proximo;
      }
   }

   return cont;
}
