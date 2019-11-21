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
    {
        arr[i] = rand_between(0, arr_size);
    }
}

int main(int argc, char **argv)
{
    // provided by teacher
    int ret;
    char *hostname;
    int my_Rank;
    int proc_size;
    MPI_Status status;

    unsigned int soma;
    unsigned int total;
    int count;

    int size_arr = atoi(argv[1]);
    int *arr = (int *)malloc(size_arr * sizeof(int));

    clock_t start_execution, end_execution;
    double execution_time;

    hostname_init(&hostname);

    set_random_values_to_arr(arr, size_arr);

    printArray(arr, size_arr);

    return 0;
}