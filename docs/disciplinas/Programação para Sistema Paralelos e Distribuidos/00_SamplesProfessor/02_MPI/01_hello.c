#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int rank, num_procs, ret;
    int tag = 0;
    char msg[200];

    MPI_Status status;
    ret = MPI_Init(&argc, &argv);
    if (ret != MPI_SUCCESS)
    {
        printf("Erro fatal %d.\n", ret);
        MPI_Abort(MPI_COMM_WORLD, ret);
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    // Todos processos que nao sejam 0 enviam mensagens
    if (rank != 0)
    {
        int dst = 0;
        int ret = sprintf(msg, "Hello, world! [%d]", rank);
        MPI_Send(msg, ret+1, MPI_CHAR, dst, tag, MPI_COMM_WORLD);
//MPI_Send(void *msg, int size, MPI_datatype type, int destiny, int tag, MPI_Comm com)
//MPI_CHAR, MPI_INT, MPI_FLOAT, MPI_BYTE, MPI_LONG, MPI_UNSIGNED_CHAR, ...
//Tag, inteiro usado para diferenciar msgs
    }
    // Processo com ranque 0 recebe num_procs-1 mensagens
    else
    {
        for (int org = 1; org < num_procs; org++)
        {
            MPI_Recv(msg, 200, MPI_CHAR, org, tag, MPI_COMM_WORLD, &status);
//MPI_Recv(void *msg, int size, MPI_datatype type, int destiny, int tag, MPI_Comm com, MPI_Status stat)
            // Imprime as mensagens recebidas
            printf("%s\n",msg);
        }
    }
    MPI_Finalize();
    return 0;
}
