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

ladalloc -c grad -n 3 -t 30 -e

mpirun -np 12 ./mpi_master_slave_sort


numero de nodos === numero de processos


https://mpitutorial.com/


MPI documents Ref
cornell mpi = https://cvw.cac.cornell.edu/MPIcc/default
scatterv explanaition = https://cvw.cac.cornell.edu/MPIcc/scatterv
mpi_gatherv = https://www.mpi-forum.org/docs/mpi-1.1/mpi-11-html/node70.html
mpi_scatterv = https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report/node106.htm#Node106

http://abd-tech.blogspot.com/2011/05/implementation-of-parallel-odd-even.html

https://www.mjr19.org.uk/courses/MPI/MPI.pdf

validar valores inteiros
https://www.geeksforgeeks.org/int_max-int_min-cc-applications/

evaluate times in MPI
https://www.mcs.anl.gov/research/projects/mpi/tutorial/gropp/node139.html



http://www.cs.kent.edu/~farrell/cc08/lectures/mpi_vops.pdf
https://cvw.cac.cornell.edu/MPIcc/gathervscatterv


MPI code inspiration
http://abd-tech.blogspot.com/2011/05/implementation-of-parallel-odd-even.html
https://github.com/wesleykendall/mpitutorial/blob/gh-pages/tutorials/mpi-scatter-gather-and-allgather/code/avg.c
https://gist.github.com/ehamberg/1263868
http://csweb.cs.wfu.edu/bigiron/LittleFE-PSRS/build/html/PSRSimplementation.html
https://www.sciencedirect.com/topics/computer-science/scatter-operation
https://github.com/stephenpcook/mpitutorial/blob/mpi-scatterv/tutorials/mpi-scatter-gather-and-allgather/code/avgv.c