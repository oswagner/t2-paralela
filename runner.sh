#!/bin/bash

make clean

make

mpirun -np 3 ./mpi_master_slave_sort 10
