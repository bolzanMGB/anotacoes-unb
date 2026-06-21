#include <stdio.h>
#include <string.h>
#include "mpi.h"

void send_rcv_msgs(int try, int rank, int num_procs)
{
    int tag = 0;
    char msg[200];
    MPI_Status status;
    if (rank != 0)
    {
        int dst = 0;
        int ret = sprintf(msg, "Hello, world! Number %d [%d]", try, rank);
        //printf("->%s\n",msg);
        MPI_Send(msg, ret+1, MPI_CHAR, dst, tag, MPI_COMM_WORLD);
    }
    else
    {
        for (int org = 1; org < num_procs; org++)
        {
            MPI_Recv(msg, 200, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("%s\n",msg);
        }
    }
}

int main(int argc, char *argv[])
{
    int rank, num_procs, ret;
    ret = MPI_Init(&argc, &argv);
    if (ret != MPI_SUCCESS)
    {
        printf("Erro fatal %d.\n", ret);
        MPI_Abort(MPI_COMM_WORLD, ret);
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    send_rcv_msgs(1, rank, num_procs);
    MPI_Barrier(MPI_COMM_WORLD);
    send_rcv_msgs(2, rank, num_procs);
    MPI_Finalize();
    return 0;
}
