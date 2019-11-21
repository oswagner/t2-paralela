#!/bin/bash

make clean

make

mpirun -np 12 ./mpi_master_slave_sort
