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
    int count;

    int size_arr = atoi(argv[1]);
    int *arr = (int *)malloc(size_arr * sizeof(int));

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

    // int *chunk_arr = 0;
    // int *chunk_arr_remainder = 0;

    // evaluate number of chunks
    // int chunk_total = size_arr / number_of_process;
    // int chunk_remainder_size = size_arr % number_of_process;

    // if (chunk_remainder_size != 0)
    //     chunk_arr_remainder = (int *)malloc(chunk_remainder_size * sizeof(int));

    // chunk_arr = (int *)malloc(chunk_size * sizeof(int));

    





    
    soma = 1;
    total = 0;
    if(process_id == 0){
        int aux = 1;
        for(aux ; aux < number_of_process ; aux++){
            ret = MPI_Send(&soma, 1, MPI_UNSIGNED, aux, 0, MPI_COMM_WORLD);
            if(ret != MPI_SUCCESS){
                mpi_err(1,"MPI_Send");
            }
        }
        aux = 1;
        for(aux ; aux < number_of_process ; aux++){
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
        printf("[%s] soma tem o valor de %d. my rank: %d\n", hostname, soma, process_id);

        ret = MPI_Send(&soma, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);
        if(ret != MPI_SUCCESS){
            mpi_err(1,"MPI_Send");
        }
    }

    ret = MPI_Finalize();
    if (ret != MPI_SUCCESS)
    {
      mpi_err(1, "MPI_Finalize");
    }

    return 0;
}