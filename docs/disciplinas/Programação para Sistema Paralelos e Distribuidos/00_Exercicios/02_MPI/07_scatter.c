// processo raiz 0 possui um array com 5 elementos e vai distribuir os 4 primeiros entre os processos

#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main (int argc, char *argv[]){
    int ret = MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (ret != MPI_SUCCESS){
        MPI_Abort (MPI_COMM_WORLD, ret);
    }

    char num;
    char letras [5];

    if (rank == 0){
        letras[0] = 'A';
        letras[1] = 'B';
        letras[2] = 'C';
        letras[3] = 'D';
        letras[4] = 'E';
    }

    MPI_Scatter (letras,1,MPI_CHAR,&num,1,MPI_CHAR,0,MPI_COMM_WORLD);
    
    printf ("Sou %d/%d, recebi %c\n", rank, num_procs, num);

    MPI_Finalize();
    return 0;
}


// $ mpirun -np 4 ./programa
// Sou 0/4, recebi A
// Sou 1/4, recebi B
// Sou 2/4, recebi C
// Sou 3/4, recebi D