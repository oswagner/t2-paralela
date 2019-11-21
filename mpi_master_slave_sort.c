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

void mpi_initialization(int ret, int my_Rank, int proc_size, int argc, char **argv)
{
    // MPI initialization
    ret = MPI_Init(&argc, &argv);
    if (ret != MPI_SUCCESS)
    {
      mpi_err(1, "MPI_Init");
    }
    
    ret = MPI_Comm_rank(MPI_COMM_WORLD, &my_Rank);
    if (ret != MPI_SUCCESS)
    {
      mpi_err(1, "MPI_Comm_rank");
    }
    
    ret = MPI_Comm_size(MPI_COMM_WORLD, &proc_size);
    if (ret != MPI_SUCCESS)
    {
      mpi_err(1, "MPI_Comm_size");
    }
}

void mpi_finalization(int ret)
{
    ret = MPI_Finalize();
    if (ret != MPI_SUCCESS)
    {
      mpi_err(1, "MPI_Finalize");
    }
}

int main(int argc, char **argv)
{
    // provided by teacher
    char *hostname;
    int ret;
    int my_Rank;
    int proc_size;
    MPI_Status status;

    unsigned int soma;
    unsigned int total;
    int count;

    int size_arr = atoi(argv[1]);
    int *arr = (int *)malloc(size_arr * sizeof(int));

    // clock_t start_execution, end_execution;
    // double execution_time;

    hostname_init(&hostname);

    mpi_initialization(ret, my_Rank, proc_size, argc, argv);

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

    mpi_finalization(ret);    

    return 0;
}