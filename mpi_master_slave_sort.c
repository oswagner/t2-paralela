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

void split_num_between_processes(int elements_to_split, int num_bins,
                                 int *num_elements_by_process,
                                 int *displacements)
{
    // Specify how these will be distributed amongst the processes
    int element_position = 0;
    int i;
    for (i = 0; i < num_bins - 1; i++)
    {
        displacements[i] = element_position;
        // Integer division
        num_elements_by_process[i] = elements_to_split / num_bins;
        element_position += elements_to_split / num_bins;
    }
    // Assign the remaining elements to the last process.  If num_bins does
    // not divide elements_to_split exactly, the last process will be assigned
    // the more elements that the others.
    displacements[num_bins - 1] = element_position;
    num_elements_by_process[num_bins - 1] = elements_to_split - element_position;
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

    srand(time(NULL));

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
    int *chunk_size = (int *)malloc(sizeof(int) * number_of_process);
    int *displacements = (int *)malloc(sizeof(int) * number_of_process);

    split_num_between_processes(size_arr, number_of_process, chunk_size, displacements);

    float *recv_chunk_arr = (float *)malloc(sizeof(float) * chunk_size[process_id]);

    if (process_id == 0)
    {
        // show all unordered array
        printf("Original array: \n");
        printArray(arr, (sizeof(arr) * sizeof(int)));
    }

    // Scatterv distribute the chunks to all processors
    MPI_Scatterv(arr, chunk_size, displacements, MPI_UNSIGNED, recv_chunk_arr, chunk_size[process_id], MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // bubbleSort(recv_chunk_arr, chunk[process_id]);

    // show all ordered array
    printf("Ordered chunk array: \n");
    printf("chunk[process_id] = %d", chunk_size[process_id]);
    int a = 0;
    for (a; a < chunk_size[process_id]; a++)
        printf("%d ", recv_chunk_arr[a]);
    printf("\n");

    // printArray(recv_chunk_arr, chunk[process_id]);

    // if (process_id == 0)
    // {
    //     recv_chunk_arr = (int *)malloc(number_of_process * sizeof(int)); // clean chunks on root to gather the values
    // }

    // // gatherv collects the chunks from all processors
    // MPI_Gatherv(&recv_chunk_arr, chunk, MPI_UNSIGNED, &recv_arr, chunk, displacements, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // if (process_id == 0)
    // {
    //     // show all unordered array
    //     printf("Original ordered array: \n");
    //     printArray(recv_arr, size_arr);
    // }

    printf("\n");

    ret = MPI_Finalize();
    if (ret != MPI_SUCCESS)
    {
        mpi_err(1, "MPI_Finalize");
    }

    return 0;
}