// Leticia Mayumi Araujo Tateishi - RA 201454

/* O programa recebe um numero n e cria um vetor circular de tamanho n. Cada
   posicao do vetor representa uma carta do baralho. O objetivo Ã© alternar
   as acoes de descartar uma carta e de coloca-la no fim do baralho ate que
   reste apenas uma. O programa imprime as cartas descartas e, por fim, a
   que restou.
*/

#include <stdio.h>
#include <stdlib.h>
#include "lab04.1.h"

int main()
{
    int n;

    while (scanf("%d", &n) && n) {

	/* Quando ha apenas uma carta no baralho */
	if (n == 1) {
	    printf("Cartas jogadas:\n");
	    printf("Carta restante: %d\n", n);
	    continue;
	}

	/* Quando ha n>1 cartas no baralho */
	int *vet_circular = malloc(n * sizeof(int));
	dados_vetor *dados = malloc(sizeof(dados_vetor));
	criar_vetor(n, vet_circular, dados);

	if (n == 2) {
	    printf("Cartas jogadas: %d\n", vet_circular[0]);
	    printf("Carta restante: %d\n", vet_circular[1]);
	    free(vet_circular);
	    free(dados);
	    continue;
	}

	printf("Cartas jogadas: ");
	retirar_cartas(vet_circular, dados);

	free(dados);
    }

    return 0;
}
