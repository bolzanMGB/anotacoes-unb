#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main (int argc, char *argv[]){

    int ret;
    ret = MPI_Init (&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    char msg [200];
    int tag = 0;
    MPI_Status status;

    if (ret != MPI_SUCCESS){
        MPI_Abort(MPI_COMM_WORLD, ret);
    }

    if (rank != 0){
        int dst = 0;
        int size = sprintf (msg, "Mensagem do Processo %d/%d\n", rank, num_procs) + 1;
        MPI_Send(msg, size, MPI_CHAR, dst, tag, MPI_COMM_WORLD);
        printf ("Sou o processo %d/%d, Acabei de Enviar para o 0/%d\n", rank, num_procs, num_procs);
    } 

    MPI_Barrier(MPI_COMM_WORLD);
    
    if (rank == 0){
        printf ("Sou o processo %d/%d, Recebi essas mensagens:\n", rank, num_procs);
        for (int dst = 1; dst < num_procs; dst++){
            MPI_Recv (msg, 200, MPI_CHAR, dst, tag, MPI_COMM_WORLD, &status);
            printf ("%s", msg);
        }
    }

    MPI_Finalize();
    return 0;
}