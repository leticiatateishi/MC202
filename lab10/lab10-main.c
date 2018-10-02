#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lab10.h"

struct timespec time_difference (struct timespec start, struct timespec end);

int main () {

    FILE *output = fopen ("selectionsort.txt", "w");
    // FILE *output = fopen ("insertionsort.txt", "w");
    // FILE *output = fopen ("mergesort.txt", "w");
    // FILE *output = fopen ("heapsort.txt", "w");
    // FILE *output = fopen ("quicksort.txt", "w");
    // FILE *output = fopen ("coutingsort.txt", "w");

    for (long int i=5000; i <= 125000; i = i + 20000) {

        fprintf (output, "\n-------------------------------\n\n");
        fprintf (output, "array size = %d\n", i);

        for (int j=0; j<50; j++) {

            int *array = malloc (i*sizeof(int));
            for (int k = 0; k<i; k++) {
                array[k] = rand()%(3*i);
            }

            struct timespec start;
            struct timespec end;
            struct timespec temp;

            // int *new_array = malloc (i * sizeof(int));

            clock_gettime (CLOCK_PROCESS_CPUTIME_ID, &start);
            selection_sort (array, i);
            // insertion_sort (array, i);
            // merge_sort (array, new_array, 0, i-1);
            // heap_sort (array, i);
            // quicksort (array, 0, i-1);
            // counting_sort (array, i);
            clock_gettime (CLOCK_PROCESS_CPUTIME_ID, &end);

            temp = time_difference (start, end);

            fprintf (output, "%ld%ld\n", temp.tv_sec, temp.tv_nsec);
            // fprintf (output, "%ld\n", temp.tv_nsec);

        }

    }

    fclose (output);
}



struct timespec time_difference (struct timespec start, struct timespec end) {

    struct timespec temp;

    if ((end.tv_nsec - start.tv_nsec) < 0) {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }

    else {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }

    return temp;
}
