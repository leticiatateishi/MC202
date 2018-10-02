#include <stdio.h>

typedef struct bloco {
   char nome[11];
   int tamanho;
   struct bloco *proximo;
}bloco;


void criar_bloco (bloco **arquivos, int tam_bloco);
int transforma_formato (int numero, char *formato);
bloco* checar_memoria (bloco *disco, int tam_inserir);
void inserir (bloco *anterior, int tam_inserir, char *nome);
void inserir_inicio (bloco **disco, int tam_inserir, char* nome);
void remover (bloco *disco, char *nome);
void otimizar (bloco **disco);
void liberar_memoria (bloco **disco);
void imprimir_saida (bloco *disco, int tam_disco);
void imprimir (bloco *disco);
