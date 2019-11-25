# t2-paralela



## Execução do programa

Realizar a alocação das máquinas no cluster grad utilizando o comando abaixo:

X = nº de nodos

Y = tempo alocado

-s = maquinas shared

-e = maquinas exclusive

```
ladalloc -c grad -n X -t Y [ -s | -e ]
```
Exemplo:
```
ladalloc -c grad -n 8 -t 20 -s
```

Após alocação dos recursos podemos então executar nosso programa através do arquivo shell `runner.sh`

```
./runner.sh
```