#!/bin/bash
#SBATCH --job-name=mi_programa
#SBATCH --output=output.txt
#SBATCH --error=error.txt
#SBATCH --partition=batch
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=4
#SBATCH --time=00:30:00

module load gcc
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./postmanS
