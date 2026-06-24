// processo 0 vai receber um número do usuário e madnar para todos os outros processos.

#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main (int argc, char* argv []){
    int ret = MPI_Init (&argc, &argv);
    
    int rank;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    int num_procs;
    MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

    if (ret != MPI_SUCCESS){
        MPI_Abort(MPI_COMM_WORLD, ret);
    }

    char msg [200];
    int x = 0;

    if (rank == 0){
        scanf ("%d", &x);
        
    }

    sprintf(msg, "Recebi isso do Processo 0");
    int size = strlen(msg) + 1;
    
    MPI_Bcast (&msg,size,MPI_CHAR,0,MPI_COMM_WORLD);
    
    printf ("%s, sou o processo %d\n", msg, rank);

    MPI_Finalize();
    return 0;
}
