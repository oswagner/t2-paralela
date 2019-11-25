#!/bin/bash

helpFunction()
{
   echo ""
   echo "Usage: $0 -p 8 -n 1000"
   echo -e "\t-p Number of processors"
   echo -e "\t-n Size of array"
   exit 1 # Exit script after printing help
}

while getopts "p:n:" opt
do
   case "$opt" in
      p ) processors="$OPTARG" ;;
      n ) array_size="$OPTARG" ;;
      ? ) helpFunction ;; # Print helpFunction in case parameter is non-existent
   esac
done

# Print helpFunction in case parameters are empty
if [ -z "$processors" ] || [ -z "$array_size" ]
then
   echo "Must pass a value to the parameters";
   helpFunction
fi

# Begin script in case all parameters are correct
echo "$processors"
echo "$array_size"

rm -rf ./out/*

make clean

make

mpirun -np $processors ./mpi_master_slave_sort $array_size
# mpirun -np 1 ./mpi_master_slave_sort 1000s
# mpirun -np 2 ./mpi_master_slave_sort 1000
# mpirun -np 4 ./mpi_master_slave_sort 1000
# mpirun -np 6 ./mpi_master_slave_sort 1000
# mpirun -np 8 ./mpi_master_slave_sort 1000
# mpirun -np 16 ./mpi_master_slave_sort 1000
# mpirun -np 32 ./mpi_master_slave_sort 1000
# mpirun -np 48 ./mpi_master_slave_sort 1000
