# t2-paralela



Execução do programa
X = número de processadores

```
mpirun -np X ./exe
```

Alocação de recursos

X  = número de nodos

Y  = tempo de alocação

-s = máquinas compartilhadas

-e = máquinas exclusivas

```
ladalloc -c grad -n X -t Y -s
```

ladalloc -c grad -n 1 -t 20 -s

mpirun -np 12 ./mpi_master_slave_sort


numero de nodos === numero de processos


https://mpitutorial.com/

scatterv sample = https://gist.github.com/ehamberg/1263868

cornell mpi = https://cvw.cac.cornell.edu/MPIcc/default

scatterv explanaition = https://cvw.cac.cornell.edu/MPIcc/scatterv

mpi_gatherv = https://www.mpi-forum.org/docs/mpi-1.1/mpi-11-html/node70.html

mpi_scatterv = https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report/node106.htm#Node106


se não rolar de usar o scatterv

https://www.geeksforgeeks.org/sum-of-an-array-using-mpi/