#include <stdio.h>
#include "mpi.h"

int main (int argc, char *argv[]){
    int rank;
    int num_procs;
    int ret;

    ret = MPI_Init(&argc, &argv);
    if (ret != MPI_SUCCESS){
        MPI_Abort (MPI_COMM_WORLD, ret);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    
    printf ("Hello World do processo %d/%d\n", rank, num_procs);

    MPI_Finalize();
    return 0;
}