#!/bin/bash

make clean

make

mpirun -np 1 ./mpi_master_slave_sort 100
