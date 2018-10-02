// Leticia Mayumi Araujo Tateishi - RA 201454

#include <stdio.h>
#include <stdlib.h>
#include "lab04.1.h"


/* Inicializa o vetor de tamanho n com as respectivas cartas do baralho. O
   inicio do vetor sera a primeira posicao, enquanto o final sera sempre o
   (tamanho do vetor-1+posicao de inicio) % (tamanho do vetor).
*/
void criar_vetor(int tamanho, int *vet_circular, dados_vetor * dados)
{
    int i;
    for (i = 0; i < tamanho; i++)
	vet_circular[i] = i + 1;

    dados->inicio = 0;
    dados->tamanho = tamanho;
    dados->capacidade = tamanho;
}



/* Imprime a primeira carta do baralho e em seguida a descarta, atraves da
   funcao realocar. Quando o tamanho Ã© 1, ou seja, so ha uma carta no monte,
   essa posicao do vetor Ã© impressa como sendo a carta restante.
*/
void retirar_cartas(int *vetor, dados_vetor * dados)
{

    /* Imprime a carta restante no baralho */
    if (dados->tamanho == 1) {
	printf("Carta restante: %d\n", vetor[dados->inicio]);
	free(vetor);
	return;
    }

    /* Imprime a ultima carta a ser retirada do monte sem a virgula */
    if (dados->tamanho == 2) {
	printf("%d\n", vetor[dados->inicio]);
	vetor[dados->inicio] = 0;
    }

    /* Imprime a primera carta do baralho */
    else {
	printf("%d, ", vetor[dados->inicio]);
	vetor[dados->inicio] = 0;
    }

    nova_posicao(dados, vetor);
    dados->tamanho--;

    /* Caso o tamanho de fato ocupado do vetor seja menor ou igual a um quarto
       de sua capacidade, o vetor sera realocado para seu tamanho atual. */
    if (dados->tamanho <= dados->capacidade / 4)
	vetor = realocar(vetor, dados);
    retirar_cartas(vetor, dados);

}


/* A posicao inicial avanca uma posicao e em seguida pula todas as possiveis
   posicoes vazias, ou seja, ocupadas por zero.
   Repete o processo, pois a primeira posicao diferente de zero encontrada
   (condicao de parada do while) deve ser a carta colocado no fim do baralho.
   Encontra a proxima posicao diferente de zero, que passa a ser o topo.
*/
void nova_posicao(dados_vetor * dados, int *vetor)
{

    dados->inicio = (dados->inicio + 1) % dados->capacidade;
    while (vetor[dados->inicio] == 0)
	dados->inicio = (dados->inicio + 1) % dados->capacidade;

    dados->inicio = (dados->inicio + 1) % dados->capacidade;
    while (vetor[dados->inicio] == 0)
	dados->inicio = (dados->inicio + 1) % dados->capacidade;
}



/* Cria um novo vetor, uma tamanho menor que o anterior. Todos os valores
   diferentes da carta que acabou de ser descartada sao copiados. O tamanho Ã©
   decrementado e o inicio recebe a segunda posicao do vetor, indicando que a
   primeira posicao foi pulada.
*/
int *realocar(int *vet_original, dados_vetor * dados)
{
    /* O indicador de inicio recebe o numero da carta qu esta no topo, para que,
       depois da realocacao, esta carta seja encontrada e inicio indique sua
       posicao no novo vetor. */
    int x = 0;
    dados->inicio = vet_original[dados->inicio];

    int *vet_novo = malloc((dados->tamanho) * sizeof(int));
    int i, j = 0;

    for (i = 0; i < dados->capacidade; i++) {
	if (vet_original[i] != 0)
	    vet_novo[j++] = vet_original[i];

	if (vet_original[i] == dados->inicio && (!x)) {
	    x = 1;
	    dados->inicio = j - 1;
	}
    }

    dados->capacidade = dados->tamanho;
    free(vet_original);
    return vet_novo;
}
