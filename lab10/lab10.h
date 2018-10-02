#include <stdio.h>

/*  Selection sort  */
void selection_sort (int *array, int size_array);

/*  Insertion sort  */
void insertion_sort (int *array, int size_array);

/*  Merge sort  */
void merge_sort (int *array, int *new_array, int low, int high);
void merge (int *array, int *new_array, int low, int mid, int high);

/*  Heap sort  */
void heap_sort (int *array, int size_array);
void build_max_heap (int *array, int size_array);
void down (int size_array, int *array, int i);
void remove_max (int *array, int size_array);

/*  Quick sort  */
void quicksort (int *array, int low, int high);
int partition (int *array, int low, int high);
