#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include "mpi.h"
#include "utils.h"

int
main(int argc, char **argv)
{
	int ret;
	/* who am i? */
	int my_rank;
	int proc_size;
	char *hostname;

	hostname_init(&hostname);

	ret = MPI_Init(&argc, &argv);
	if (ret != MPI_SUCCESS)
		mpi_err(ret, "MPI_Init");

	ret = MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	if (ret != MPI_SUCCESS)
		mpi_err(ret, "MPI_Comm_rank");
	ret = MPI_Comm_size(MPI_COMM_WORLD, &proc_size);
	if (ret != MPI_SUCCESS)
		mpi_err(ret, "MPI_Comm_size");

	printf("[%s] i am %d of total %d processes\n", hostname, my_rank, 
	    proc_size);
	hostname_end(hostname);
	ret = MPI_Finalize();
	if (ret != MPI_SUCCESS)
		mpi_err(ret, "MPI_Finalize");

	return (0);
}
