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