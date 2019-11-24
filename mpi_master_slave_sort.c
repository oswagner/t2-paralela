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
    srand(time(NULL));
    int i = 0;
    for (i; i < arr_size; i++)
        arr[i] = rand_between(0, arr_size);
}

void split_num_between_processes(int elements_to_split, int num_bins, int *num_elements_by_process, int *displacements)
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
// float *array, int *weights_array, int num_elements
// void group_chunk(recv_chunk_arr, chunk_size, number_of_process, recv_arr)
// {
//     float sum = 0.f;
//     float sum_weights = 0.f;
//     int i;
//     for (i = 0; i < num_elements; i++)
//     {
//         sum += weights_array[i] * array[i];
//         sum_weights += weights_array[i];
//     }
// }

// m - size of A
// n - size of B
// size of C array must be equal or greater than
// m + n
// void merge(int m, int n, int A[], int B[], int C[])
// {
//     int i, j, k;
//     i = 0;
//     j = 0;
//     k = 0;
//     while (i < m && j < n)
//     {
//         if (A[i] <= B[j])
//         {
//             C[k] = A[i];
//             i++;
//         }
//         else
//         {
//             C[k] = B[j];
//             j++;
//         }
//         k++;
//     }
//     if (i < m)
//     {
//         for (int p = i; p < m; p++)
//         {
//             C[k] = A[p];
//             k++;
//         }
//     }
//     else
//     {
//         for (int p = j; p < n; p++)
//         {
//             C[k] = B[p];
//             k++;
//         }
//     }
// }

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

    // clock_t start_execution, end_execution;
    // double execution_time;

    hostname_init(&hostname);

    ret = MPI_Init(&argc, &argv);
    if (ret != MPI_SUCCESS)
        mpi_err(1, "MPI_Init");

    ret = MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
    if (ret != MPI_SUCCESS)
        mpi_err(1, "MPI_Comm_rank");

    ret = MPI_Comm_size(MPI_COMM_WORLD, &number_of_process);
    if (ret != MPI_SUCCESS)
        mpi_err(1, "MPI_Comm_size");

    // generate random values in the array
    set_random_values_to_arr(arr, size_arr);

    // evaluate the size chunk and displacements
    int *chunk_size = (int *)malloc(sizeof(int) * number_of_process);
    int *displacements = (int *)malloc(sizeof(int) * number_of_process);

    split_num_between_processes(size_arr, number_of_process, chunk_size, displacements);

    int *recv_chunk_arr = (int *)malloc(sizeof(int) * chunk_size[process_id]);

    if (process_id == 0)
    {
        // show all unordered array
        printf("Original array: \n");
        printArray(arr, size_arr);
    }

    // Scatterv distribute the chunks to all processors
    MPI_Scatterv(arr, chunk_size, displacements, MPI_INT, recv_chunk_arr, chunk_size[process_id], MPI_INT, 0, MPI_COMM_WORLD);

    // show all ordered array
    printf("Processado no [%s] rank %d\n", hostname, process_id);
    bubbleSort(recv_chunk_arr, chunk_size[process_id]);
    printArray(recv_chunk_arr, chunk_size[process_id]);

    if (process_id == 0)
        recv_chunk_arr = (int *)malloc(sizeof(int) * number_of_process); // clean chunks on root to gather the values

    // // gatherv collects the chunks from all processors
    MPI_Gatherv(&recv_chunk_arr, chunk_size[process_id], MPI_INT, recv_arr, size_arr, displacements, MPI_INT, 0, MPI_COMM_WORLD);
    // MPI_Gather(&arr, chunk_size, MPI_INT, recv_chunk_arr, chunk_size[process_id], MPI_INT, 0, MPI_COMM_WORLD);

    if (process_id == 0)
    {
        // show all unordered array
        printf("Original ordered array: \n");
        printArray(recv_arr, size_arr);
    }

    printf("\n");

    ret = MPI_Finalize();
    if (ret != MPI_SUCCESS)
    {
        mpi_err(1, "MPI_Finalize");
    }

    return 0;
}