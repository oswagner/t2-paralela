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

    
    soma = 1;
    total = 0;
    if(my_Rank == 0){
        int aux = 1;
        for(aux ; aux < proc_size ; aux++){
            ret = MPI_Send(&soma, 1, MPI_UNSIGNED, aux, 0, MPI_COMM_WORLD);
            if(ret != MPI_SUCCESS){
                mpi_err(1,"MPI_Send");
            }
        }
        aux = 1;
        for(aux ; aux < proc_size ; aux++){
            ret = MPI_Recv(&soma, 1, MPI_UNSIGNED,aux,0,MPI_COMM_WORLD, &status);
            if(ret != MPI_SUCCESS){
                mpi_err(1,"MPI_Recv");
            }
            total += soma;
        }

        printf("Soma total vale: %d\n", total);
        printf("\n");
    } else {
        ret = MPI_Recv(&soma, 1, MPI_UNSIGNED, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        if(ret != MPI_SUCCESS){
            mpi_err(1,"MPI_Recv");
        }

        ret = MPI_Get_count(&status, MPI_UNSIGNED, &count);
        if(ret != MPI_SUCCESS){
            mpi_err(1,"MPI_Get_count");
        }

        // poderia verificar quem não enviou, procurar função
        if(count != 1){
            mpi_err(1,"Count errado %d", count);
        }

        soma = soma + 1;
        printf("[%s] soma tem o valor de %d. my rank: %d\n", hostname, soma, my_Rank);

        ret = MPI_Send(&soma, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);
        if(ret != MPI_SUCCESS){
            mpi_err(1,"MPI_Send");
        }
    }

    mpi_finalization(ret);    

    return 0;
}