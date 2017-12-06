#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=8
#SBATCH --output=output2.txt

cp problem2.c $PFSDIR/.
cd $PFSDIR
gcc -o problem2 problem2.c -lrt -pthread -lm
./problem2 1
./problem2 2
./problem2 4
./problem2 6
./problem2 8
