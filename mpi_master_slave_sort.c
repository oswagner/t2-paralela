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
    char *hostname;
    int ret;
    int process_id;
    int number_of_process;
    MPI_Status status;

    unsigned int soma;
    unsigned int total;

    int size_arr = atoi(argv[1]);
    int *arr = (int *)malloc(size_arr * sizeof(int));
    int *recv_arr = (int *)malloc(size_arr * sizeof(int));
    int *recv_chunk_arr = (int *)malloc(size_arr * sizeof(int));

    // clock_t start_execution, end_execution;
    // double execution_time;

    hostname_init(&hostname);

    ret = MPI_Init(&argc, &argv);
    if (ret != MPI_SUCCESS)
    {
        mpi_err(1, "MPI_Init");
    }

    ret = MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
    if (ret != MPI_SUCCESS)
    {
        mpi_err(1, "MPI_Comm_rank");
    }

    ret = MPI_Comm_size(MPI_COMM_WORLD, &number_of_process);
    if (ret != MPI_SUCCESS)
    {
        mpi_err(1, "MPI_Comm_size");
    }

    // generate random values in the array
    set_random_values_to_arr(arr, size_arr);

    // evaluate the size chunk and displacements
    int *chunk = malloc(sizeof(int) * number_of_process);
    int *displacements = malloc(sizeof(int) * number_of_process);
    int count = 0;
    int remainder = size_arr % number_of_process;

    int i = 0;
    for (i; i < number_of_process; i++)
    {
        chunk[i] = size_arr / number_of_process;

        if (remainder > 0)
        {
            chunk[i]++;
            remainder--;
        }

        displacements[i] = count;
        count += chunk[i];
    }

    // show all unordered array
    printf("Original array: \n");
    printArray(arr, (sizeof(arr) * sizeof(int)));

    // Scatterv distribute the chunks to all processors
    MPI_Scatterv(&arr, chunk, displacements, MPI_UNSIGNED, &recv_chunk_arr, chunk, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    bubbleSort(recv_chunk_arr, (sizeof(recv_chunk_arr) * sizeof(int)));

    // show all ordered array
    printf("Ordered chunk array: \n");
    printArray(recv_chunk_arr, (sizeof(recv_chunk_arr) * sizeof(int)));

    // gatherv collects the chunks from all processors
    MPI_Gatherv(&arr, chunk, MPI_UNSIGNED, &recv_arr, chunk, displacements, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    if (process_id == 0)
    {
        // show all unordered array
        printf("Original ordered array: \n");
        printArray(recv_arr, (sizeof(recv_arr) * sizeof(int)));
    }

    printf("\n");

    ret = MPI_Finalize();
    if (ret != MPI_SUCCESS)
    {
        mpi_err(1, "MPI_Finalize");
    }

    return 0;
}