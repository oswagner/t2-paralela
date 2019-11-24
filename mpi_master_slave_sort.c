#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
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

int main(int argc, char **argv)
{
    // provided by teacher
    char *hostname;
    int ret;
    int process_id;
    int number_of_process;
    MPI_Status status;

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

    // end of MPI initialization
    int size_arr = atoi(argv[1]);
    int *arr = (int *)malloc(size_arr * sizeof(int));

    double start_time;
    double end_time;

    if (process_id == 0) // root
    {
        // generate random values in the array
        set_random_values_to_arr(arr, size_arr);
        // show all unordered array
        printf("Original array: \n");
        // printArray(arr, size_arr);
    }

    // evaluate the size chunk and displacements
    int *send_counter = (int *)malloc(number_of_process * sizeof(int));
    int *displacements = (int *)malloc(sizeof(int) * number_of_process);
    int send_size = size_arr / number_of_process;

    int i;
    for (i = 0; i < number_of_process; i++)
    {
        displacements[i] = i * send_size;
        send_counter[i] = send_size;
        if (i == number_of_process - 1)
            send_counter[i] += size_arr % number_of_process;
    }

    int chunk_size = send_counter[process_id];
    int *chunk = (int *)malloc(chunk_size * sizeof(int));

    start_time = MPI_Wtime();

    // Scatterv distribute the chunks to all processors
    MPI_Scatterv(arr, send_counter, displacements, MPI_INT, chunk, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // show all ordered array
    printf("Sorted at [%s] process_id [%d] \n", hostname, process_id);
    // sort array
    bubbleSort(chunk, chunk_size);
    // printArray(chunk, chunk_size);

    // // gatherv collects the chunks from all processors
    MPI_Gatherv(chunk, chunk_size, MPI_INT, arr, send_counter, displacements, MPI_INT, 0, MPI_COMM_WORLD);

    if (process_id == 0) // merge all chunks back in result array
    {
        int *result;
        int *position;

        position = (int *)malloc(number_of_process * sizeof(int));
        result = (int *)malloc(size_arr * sizeof(int));

        for (i = 0; i < number_of_process; i++)
        {
            position[i] = 0;
        }

        for (i = 0; i < size_arr; i++)
        {
            int min_index = -1;
            int min = INT_MAX; // max value of interger

            int j;
            for (j = 0; j < number_of_process; j++) // merge values from each processor
            {
                if (position[j] < send_counter[j]) // add values sorted
                {
                    if (arr[displacements[j] + position[j]] < min) // ensure it's a valid value
                    {
                        min = arr[displacements[j] + position[j]]; // jump displacements and update index
                        min_index = j;
                    }
                }
            }

            result[i] = arr[displacements[min_index] + position[min_index]];
            position[min_index]++;
        }
        end_time = MPI_Wtime();

        printf("n= %d \n", size_arr);
        printf("number_of_process= %d \n", number_of_process);
        printf("time [s]=%g \n", (end_time - start_time));

        for (i = 0; i < size_arr; i++)
        {
            printf("%d ", result[i]);
        }

        free(result);
        free(position);
        free(arr);
    }

    printf("\n");

    ret = MPI_Finalize();
    if (ret != MPI_SUCCESS)
    {
        mpi_err(1, "MPI_Finalize");
    }

    return 0;
}