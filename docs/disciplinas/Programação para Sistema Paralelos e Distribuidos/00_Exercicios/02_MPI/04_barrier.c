// funcao que receve um número e manda esse número de todos os procesos diferentes de 0 para o processo 0

#include <stdio.h>
#include <string.h>
#include "mpi.h"

void send_recv (int rank, int x, int num_procs){
    char msg [200];
    int tag = 0;
    MPI_Status status;

    if (rank != 0){
        int dst = 0;

        sprintf (msg, "Sou %d/%d. Envie %d para 0/%d", rank, num_procs, x, num_procs);
        int size = strlen(msg) + 1;
        MPI_Send(msg,size,MPI_CHAR,dst,tag,MPI_COMM_WORLD);
    }
    else{
        for (int org = 1; org < num_procs; org++){
            MPI_Recv(msg,200,MPI_CHAR,org,tag,MPI_COMM_WORLD,&status);
            printf ("%s\n", msg);
        }
    }
}


int main (int argc, char *argv []){

    int ret = MPI_Init (&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    
    if (ret != MPI_SUCCESS){
        MPI_Abort(MPI_COMM_WORLD, ret);
    }

    send_recv(rank,1,num_procs);
    MPI_Barrier(MPI_COMM_WORLD);
    send_recv(rank,2,num_procs);

    MPI_Finalize();

    return 0;
}

