#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lab03.h"

/* Cria uma lista, com nome "vazio", representando um bloco inicial com tamanho
   igual ao tamanho fornecido na entrada.
*/
void criar_bloco (bloco **arquivos, int tam_bloco){

   bloco* arquivo = malloc (sizeof(bloco));
   strcpy (arquivo->nome, "vazio");
   arquivo->tamanho = tam_bloco;
   arquivo->proximo = *arquivos;
   *arquivos = arquivo;

}



/* Transforma formatos de Mb para Kb, multiplicando por 1024.
   Tambem transforma Gb para Kb, multiplicando por 1024*1024.
*/
int transforma_formato (int numero, char *formato){
   int numero_novo;

   if (!strcmp (formato, "Mb\n"))
      numero_novo = numero * 1024;

   else if (!strcmp (formato, "Gb\n"))
      numero_novo = numero * 1024 * 1024;

   return numero_novo;
}



/* Retorna um ponteiro com a posicao anterior ao primeiro bloco vazio com
   tamanho maior ou igual ao do arquivo que deve ser inserido.
   Retorna nulo caso nao haja espaco para insercao do arquivo.
*/
bloco* checar_memoria (bloco *disco, int tam_inserir) {
   bloco *p = disco, *pp = NULL, *menor_bloco = NULL;

   while (p->proximo != NULL) {
      if (p->proximo->tamanho >= tam_inserir && (!strcmp (p->proximo->nome, "vazio"))) {
         if (!menor_bloco)
            menor_bloco = p;
         else if (menor_bloco != NULL && p->proximo->tamanho < menor_bloco->tamanho) {
            menor_bloco = p;
         }
      }
      pp = p;
      p = p->proximo;
   }

   if (p->tamanho >= tam_inserir && (!strcmp (p->nome, "vazio")))
      return pp;
   return menor_bloco;
}



/* Insere o arquivo no inicio da lista (ocorre apenas quando a lista esta vazia).
   Caso o menor bloco encontrado por checar_memoria tenha tamanho maior ao do
   arquivo, um novo bloco de nome vazio é criado e recebe os Kb restantes.
*/
void inserir_inicio (bloco **disco, int tam_inserir, char* nome) {

   bloco *arquivo = malloc (sizeof (bloco));
   strcpy (arquivo->nome, nome);
   arquivo->tamanho = tam_inserir;

   if ((*disco)->tamanho > tam_inserir) {
      bloco *vazio = malloc (sizeof (bloco));
      strcpy (vazio->nome, "vazio");
      vazio->tamanho = (*disco)->tamanho - tam_inserir;
      vazio->proximo = (*disco)->proximo;
      arquivo->proximo = vazio;
   }

   else
      arquivo->proximo = (*disco)->proximo;
   *disco = arquivo;

}



/* Insere o arquivo no meio ou no final do disco (ocorre apenas quando o disco
   nao esta vazio). O arquivo é armazenado no menor bloco de tamanho maior ou
   igual ao seu tamanho. Caso sobre espaco, este é armazenado em um bloco que
   o segue, chamado vazio.
*/
void inserir (bloco *anterior, int tam_inserir, char *nome) {

   bloco *arquivo = malloc (sizeof (bloco));
   strcpy (arquivo->nome, nome);
   arquivo->tamanho = tam_inserir;

   if (anterior->proximo->tamanho > tam_inserir) {
      bloco *vazio = malloc (sizeof (bloco));
      strcpy (vazio->nome, "vazio");
      vazio->tamanho = anterior->proximo->tamanho - tam_inserir;
      vazio->proximo = anterior->proximo->proximo;
      arquivo->proximo = vazio;
   }

   anterior->proximo = arquivo;
}



/* A ordem dos arquivos no disco nao é alterada, apenas o nome do arquivo é
   alterado para "vazio", e este passa a indicar um bloco vazio no disco. Caso
   nao exista bloco com este nome, nada é feito.
*/
void remover (bloco *disco, char *nome) {
   bloco *posicao = disco;

   while (strcmp(posicao->nome, nome)) {
      posicao = posicao->proximo;
      if (!posicao)
         return;
   }

   strcpy (posicao->nome, "vazio");
}



/* A funcao percorre toda a lista, salvando o tamanho dos arquivos vazios na
   variavel tam_vazio. Os ponteiros sao alterados para que os blocos vazios
   sejam liberados. No final, um novo bloco é criado no fim do disco, com
   tamanho equivalente a soma de todos os outros arquivos em branco.
*/
void otimizar (bloco **disco) {
   int tam_vazio = 0;
   bloco *posicao = *disco, *anterior = NULL;

   if (!strcmp (posicao->nome, "vazio")) {
      while (!strcmp (posicao->nome, "vazio")) {
         tam_vazio += posicao->tamanho;
         posicao = posicao->proximo;
         *disco = posicao;
      }
   }

   while (posicao != NULL) {

      if (!strcmp (posicao->nome, "vazio")) {
         tam_vazio += posicao->tamanho;
         anterior->proximo = posicao->proximo;
         posicao = anterior;
      }

      anterior = posicao;
      posicao = posicao->proximo;
   }

   if (tam_vazio != 0) {
      bloco *vazio = malloc (sizeof (bloco));
      strcpy (vazio->nome, "vazio");
      vazio->tamanho = tam_vazio;
      vazio->proximo = posicao;
      anterior->proximo = vazio;
   }
}



void liberar_memoria (bloco **disco) {
   bloco *aux;

   while (*disco != NULL) {
      aux = *disco;
      *disco = (*disco)->proximo;
      free (aux);
   }
}


/* Imprime a lista */
void imprimir (bloco *disco) {
   bloco *p = disco;

   while (p != NULL) {
      printf ("nome: %s\ntamanho: %d\n\n", p->nome, p->tamanho);
      p = p->proximo;
   }
}



void imprimir_saida (bloco *disco, bloco *final, int tam_bloco) {
   bloco *f = final, *p = disco;
   int i, anterior = 0, anterior_sinal = 0;

   if (anterior_sinal == 1) {
      if ((anterior + p->tamanho) == tam_bloco) {
         if (!strcmp (p->nome, "vazio"))
            f->tamanho = 0;
         else
            f->tamanho = 100;
         anterior = 0;
         anterior_sinal = 0;
         f = f->proximo;
      }

      else if ((anterior + p->tamanho) > tam_bloco) {
         if (!strcmp (p->nome, "vazio")){
            anterior_sinal = 0;
            f->tamanho += anterior;
            anterior = 0;
         }
         else {
            anterior_sinal = 1;
            f->tamanho = 100;
            anterior += p->tamanho - tam_bloco;
         }
         f = f->proximo;
      }

      else {
         if (!strcmp (p->nome, "vazio")) {
            anterior_sinal = 0;

         }
      }

      if (!f)
         break;
   }
   printf ("\n");
}
