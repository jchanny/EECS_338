#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=8
#SBATCH --output=output3.txt

cp problem3.c $PFSDIR/.
cd $PFSDIR
-gcc -o problem3 problem3.c -lrt -pthread -lm
./problem3 1
./problem3 2
./problem3 4
./problem3 6
./problem3 8
