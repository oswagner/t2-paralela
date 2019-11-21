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

ladalloc -c grad -n 3 -t 20 -s

mpirun -np 12 ./mpi_master_slave_sort


numero de nodos === numero de processos

ssh pp13814@grad.lad.pucrs.br
