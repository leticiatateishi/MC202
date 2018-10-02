//  Leticia Mayumi Araujo Tateishi - RA 201454
//  Funcoes em conjuntos disjuntos.

#include <stdio.h>
#include "conjuntos.h"


int main () {

    int array[10];

    make_set (array, 10);

    if (union_sets (array, 10, 2, 5) == 1)
        printf ("Conjuntos 2 e 5 unidos\n");
    printf ("representante 2=%d, representante 5=%d\n",
            find (array, 10, 2), find (array, 10, 5));

    if (union_sets (array, 10, 2, 8) == 1)
        printf ("Conjuntos 2 e 8 unidos\n");
    printf ("representante 2=%d, representante 8=%d\n",
            find (array, 10, 2), find (array, 10, 8));

    if (union_sets (array, 10, 2, 6) == 1)
        printf ("Conjuntos 2 e 6 unidos\n");
    printf ("representante 2=%d, representante 6=%d\n",
            find (array, 10, 2), find (array, 10, 6));

    if (union_sets (array, 10, 7, 3) == 1)
        printf ("Conjuntos 7 e 3 unidos\n");
    printf ("representante 7=%d, representante 3=%d\n\n",
            find (array, 10, 7), find (array, 10, 3));

    for (int i = 0; i < 10; i++) {
        printf ("representante %d = %d\n", i, find (array, 10, i));
    }
}
