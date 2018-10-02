// Leticia Mayumi Araujo Tateishi - RA 201454

#include <stdio.h>

typedef struct no {
    int chave;
    struct no* filho;
    struct no* irmao;
} no;


void link (no **arvores, int filho, int pai);
void cut (no **arvores, int n_cortar);
void lca (no *arvores, int descendente_1, int descendente_2, int tam_floresta);
no* buscar (no *arvores, int n_buscado);
void liberar_arvores (no* arvores);
no *buscar_pai (no *arvore, int filho);
