#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include "mpi.h"
#include "utils.h"

int main(int argc, char **argv)
{
	int ret;
	int count;
	/* who am i? */
	int my_rank;
	int proc_size;
	char *hostname;
	MPI_Status status;
	unsigned int soma;

	hostname_init(&hostname);

	ret = MPI_Init(&argc, &argv);
	if (ret != MPI_SUCCESS)
		mpi_err(ret, "MPI_Init");

	ret = MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // my_rank = num process
	if (ret != MPI_SUCCESS)
		mpi_err(ret, "MPI_Comm_rank");
	ret = MPI_Comm_size(MPI_COMM_WORLD, &proc_size); // proc_size = quantidade de processo
	if (ret != MPI_SUCCESS)
		mpi_err(ret, "MPI_Comm_size");

	if (my_rank == 0)
	{ // my_rank = 0 mestre
		soma = 0;
		ret = MPI_Send(&soma, 1, MPI_UNSIGNED, my_rank + 1, 0, MPI_COMM_WORLD);
		if (ret != MPI_SUCCESS)
			mpi_err(ret, "MPI_Send");
	}
	else
	{
		ret = MPI_Recv(&soma, 1, MPI_UNSIGNED, my_rank - 1, 0, MPI_COMM_WORLD, &status);
		if (ret != MPI_SUCCESS)
			mpi_err(ret, "MPI_Recv");

		ret = MPI_Get_count(&status, MPI_UNSIGNED, &count); // validar o recebimento das infos dos nodos
		if (ret != MPI_SUCCESS)
			mpi_err(ret, "MPI_Get_count");

		if (count != 1)
			mpi_err(ret, "MPI_Get_count %d", count);

		soma += (unsigned int)my_rank; // processamento que o nodo vai realizar
		printf("[%s][%d] valor atual da soma %u\n", hostname, my_rank, soma);

		if (my_rank + 1 == proc_size) // verifica que o é o último nodo executando, fizaliza o processamento de nodos do mpi
			goto end;
		ret = MPI_Send(&soma, 1, MPI_UNSIGNED, my_rank + 1, 0, MPI_COMM_WORLD);
		if (ret != MPI_SUCCESS)
			mpi_err(ret, "MPI_Send");
	}
end:
	hostname_end(hostname);
	ret = MPI_Finalize();
	if (ret != MPI_SUCCESS)
		mpi_err(ret, "MPI_Finalize");

	return (0);
}
