#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lab03.h"


int main() {

   int i, num_operacoes, tam_disco, tam_inserir, disco_cheio = 0;
   bloco *disco = NULL;
   char formato[4], operacao[8], nome[10], formato_inserir[4];

   /* Num_operacoes representa a quantidade de operacoes que serao realizadas,
      com 0 < num_operacoes < 10000, podendo ser insercao, remocao ou otimizacao.
      O programa termina quando num_operacoes for zero. */
   while (scanf ("%d", &num_operacoes) != 0 && num_operacoes != 0){
      disco_cheio = 0;

      /*  tam_disco é inteiro, 0 < tam_disco <= 1023, seguido de sua respectiva
         unidade (Kb, Mb ou Gb). */
      scanf ("%d", &tam_disco);
      fgets (formato, 4, stdin);

      /* Transforma o tamanho do disco, caso os valores sejam dados em Mg ou Gb */
      if (strcmp (formato, "Kb\n")) {
         tam_disco = transforma_formato (tam_disco, formato);
         strcpy (formato, "Kb");
      }

      criar_bloco (&disco, tam_disco);
      imprimir (disco);

      for (i=0; i<num_operacoes; i++){
         scanf("%s", &operacao);

         /* Caso a operacao seja insercao, o nome do bloco a ser incrementado,
            o tamanho do incremento e sua unidade sao lidas.*/
         if (!strcmp (operacao, "insere")) {
            scanf ("%s", &nome);
            scanf ("%d", &tam_inserir);
            fgets (formato_inserir, 4, stdin);

            /* Transforma o tamanho a ser inserido em Kb */
            if (strcmp (formato_inserir, "Kb\n")){
               tam_inserir = transforma_formato (tam_inserir, formato_inserir);
               printf ("tamanho a inserir = %d\n", tam_inserir);
               strcpy (formato_inserir, "Kb");
            }

            /* Caso disco esteja vazio */
            if (!disco->proximo && (!disco_cheio)){
               printf ("inserir no inicio da lista\n");
               inserir_inicio (&disco, tam_inserir, nome);
            }

            /* Quando o disco ja possui outros arquivos, checar_memoria retorna
               a posicao do bloco anterior ao menor bloco de tamanho maior ou igual
               ao tamanho do arquivo. Caso nao haja bloco com tamanho suficiente,
               ocorre a otimizacao da lista e a disponibilidade é novamente
               conferida. Se ainda nao houver espaco, uma mensagem de erro é
               impressa e as operacoes seguintes para o mesmo teste sao ignoradas
               devido a inicializacao de disco_cheio com 1. */
            else if (!disco_cheio){
               bloco *anterior = checar_memoria (disco, tam_inserir);

               if (!anterior) {
                  otimizar (&disco);
                  anterior = checar_memoria (disco, tam_inserir);
                  if (!anterior) {
                     disco_cheio = 1;
                     printf ("ERRO: disco cheio\n");
                  }
               }

               if (anterior){
                  printf ("inserir no meio da lista\n");
                  printf ("tam anterior = %d\n", anterior->tamanho);
                  inserir (anterior, tam_inserir, nome);
               }
            }
        }


        else if (!strcmp (operacao, "remove")) {
           scanf ("%s\n", &nome);
           if (!disco_cheio)
               remover (disco, nome);
        }


        else {
           if (!disco_cheio)
                otimizar (&disco);
        }

        imprimir (disco);
     }
  }

   bloco *final = NULL;
   for (i=0; i<8; i++)
      criar_bloco (&final, 0);
   imprimir_saida (disco, final, tam_disco/8, 0);

   liberar_memoria (&disco);
   return 0;
}
