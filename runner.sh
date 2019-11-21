#!/bin/bash

make clean

make

mpirun -np 8 ./mpi_master_slave_sort 100
