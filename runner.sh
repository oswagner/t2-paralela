#!/bin/bash

rm -rf ./out/*

make clean

make

mpirun -np 8 ./mpi_master_slave_sort 1000
