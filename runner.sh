#!/bin/bash

helpFunction()
{
   echo ""
   echo "Usage: $0 -a 8 -b 1000"
   echo -e "\t-a Number of processors"
   echo -e "\t-b Size of array"
   exit 1 # Exit script after printing help
}

while getopts "a:b:" opt
do
   case "$opt" in
      a ) processors="$OPTARG" ;;
      b ) array_size="$OPTARG" ;;
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
