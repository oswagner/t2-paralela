#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#include "utils.h"
#include <time.h>
#include "bubble_sort.h"

#define rand_between(min, max) \
    ((rand() % (int)(((max) + 1) - (min))) + (min))

void set_random_values_to_arr(int arr[], int arr_size)
{
    int i = 0;
    for (i; i < arr_size; i++)
        arr[i] = rand_between(0, arr_size);
}

int main(int argc, char **argv)
{
    // provided by teacher
    int ret;
    char *hostname;
    int my_Rank;
    int proc_size = 8;
    MPI_Status status;

    unsigned int soma;
    unsigned int total;
    int count;

    int size_arr = atoi(argv[1]);
    int *arr = (int *)malloc(size_arr * sizeof(int));

    // clock_t start_execution, end_execution;
    // double execution_time;

    // hostname_init(&hostname);

    // generate random values in the array
    set_random_values_to_arr(arr, size_arr);

    int *chunk_arr = 0;
    int *chunk_arr_remainder = 0;

    // evaluate chunks sizes
    int chunk_size = size_arr / proc_size;
    int chunk_remainder_size = size_arr % proc_size;

    if (chunk_remainder_size != 0)
        chunk_arr_remainder = (int *)malloc(chunk_remainder_size * sizeof(int));

    chunk_arr = (int *)malloc(chunk_size * sizeof(int));

    printArray(arr, size_arr);
    printf("original array");
    printArray(chunk_arr, chunk_size);
    printf("chunk array");
    printArray(chunk_arr_remainder, chunk_remainder_size);
    printf("chunk_reainder array");

    return 0;
}