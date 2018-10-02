#include <stdio.h>
#include "lab10.h"


void selection_sort (int *array, int size_array) {

    for (int i = size_array-1; i > 0; i--) {
        int max = 0;
        for (int j = 1; j <= i; j++){
            if (array[j] > array[max])
                max = j;
        }
        int temp = array[i];
        array[i] = array[max];
        array[max] = temp;
    }
}



/*  Insertion sort goes from position 1 downto size_array, and calls the value
    of the actual position key. j goes from the actual position downto a value
    smaller than key. So, key is positioned on its right place, leaving the
    array on crescent order from 0 to new position of key (but new insertions
    can occur on this organized array).
*/
void insertion_sort (int *array, int size_array) {

    int i, j, key;

    for (i = 1; i < size_array; i++) {
        key = array[i];
        j = i-1;
        while (j>=0 && array[j] > key) {
            array[j+1] = array[j];
            j --;
        }
        array[j+1] = key;
    }
}



/*  The function recursively partitions the array until the resultant arrays
    are sized one. Then, merge is called to organize this smaller arrays and
    put them together in a bigger array.
*/
void merge_sort (int *array, int *new_array, int low, int high) {

    if (low < high) {
        int mid = (low + high) / 2;
        merge_sort (array, new_array, low, mid);
        merge_sort (array, new_array, mid+1, high);
        merge (array, new_array, low, mid+1, high);
    }
}


/*  Merge walks through both arrays (that are, in fact, different parts of a
    single array) and compares every single key from each array and organizes
    them in crescent order in a new array. As the walk through each array isn't
    going to me symetrical, at the end, the array that wasn't finished is just
    copied the the new one. At last, everything is copied to the old array.
*/
void merge (int *array, int *new_array, int low, int mid, int high) {

    int i = low, j = mid-1, size = high-low+1;

    while (low <= j && mid <= high) {

        if (array[low] <= array[mid])
            new_array[i++] = array[low++];
        else
            new_array[i++] = array[mid++];
    }

    while (low <= j)
        new_array[i++] = array[low++];

    while (mid <= high)
        new_array[i++] = array[mid++];

    for (int k = 0; k <= size; k ++) {
        array[high] = new_array[high];
        high --;
    }

}



/*  Builds a maximum heap with the given array and puts the larger key in the
    last position, and so on.
*/
void heap_sort (int *array, int size_array) {

    int old_size = size_array;

    build_max_heap (array, size_array);
    for (int i = size_array-1; i > 0; i--) {
        remove_max (array, size_array);
        size_array --;
    }

    size_array = old_size;
}


/*  Builds a maximun heap by placing the biggest key in the start, respecting
    the property that each child key must be smaller than its father's key.
*/
void build_max_heap (int *array, int size_array) {

    int i;
    for (i = size_array/2 - 1; i >= 0; i--)
        down (size_array, array, i);

}


/*  Goes down on the given array, and organizes it to be a maximum heap.
*/
void down (int size_array, int *array, int i) {

    int father;
    int left = 2*i + 1;
    int right = left + 1;

    if (left < size_array && array[left] > array[i])
        father = left;
    else
        father = i;

    if (right < size_array && array[right] > array[father])
        father = right;

    if (father != i) {
        int aux = array[i];
        array[i] = array[father];
        array[father] = aux;
        down (size_array, array, father);
    }
}


/*  Returns the value of the highest key in the heap and organizes it
*/
void remove_max (int *array, int size_array) {

    int maximum = array[0];
    array[0] = array[size_array-1];
    array[size_array-1] = maximum;

    down (size_array-1, array, 0);
}




void quicksort (int *array, int low, int high) {

    if (low < high) {
        int pivot = partition (array, low, high);
        quicksort (array, low, pivot-1);
        quicksort (array, pivot+1, high);
    }
}


int partition (int *array, int low, int high) {

    int left = low, right = high, pivot_item = array[low];

    while (left < right) {

        while (array[left] <= pivot_item)
            left ++;

        while (array[right] > pivot_item)
            right --;

        if (left < right) {
            int temp = array[left];
            array[left] = array[right];
            array[right] = temp;
        }
    }

    array[low] = array[right];
    array[right] = pivot_item;
    return right;
}




void counting_sort (int *array, int size_array) {

    int range = 3*size_array;
    int temp[range], final_array[size_array];

    for (int i=0; i<range; i++)
        temp[i] = 0;

    for (int j=0; j<size_array; j++)
        temp[array[j]] = temp[array[j]]+1;

    for (int i=1; i<range; i++)
        temp[i] = temp[i] + temp[i-1];

    for (int j=size_array-1; j>=0; j--) {
        final_array[temp[array[j]]] = array[j];
        temp[array[j]] --;
    }

}
