// Leticia Mayumi Araujo Tateishi - RA 201454

#include <stdio.h>

typedef struct no {
   int chave;
   struct no *esquerda;
   struct no *direita;
} no;


void inserir (no **raiz, int chave_inserir);
void excluir (no** raiz, int chave_excluir);
no* buscar (no *raiz, int chave_buscada);
int minimo (no* raiz);
int maximo (no* raiz);
void pos_ordem (no* raiz);
void pre_ordem (no* raiz);
void em_ordem (no* raiz);
void chamar_largura (no *raiz);
void largura (no* raiz, int nivel_atual, int nivel_desejado, int *fim_arvore);
void terminar (no* raiz);
no* sucessao (no *raiz, no *sucedido);
no* buscar_avo (no *raiz, no *neto);
no* buscar_pai (no *raiz, no *filho);
