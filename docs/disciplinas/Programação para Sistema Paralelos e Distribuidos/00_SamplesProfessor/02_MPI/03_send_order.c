#include <stdio.h>
#include <string.h>
#include "mpi.h"

#define N_MSGS 4

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
        for (int i = 0; i < N_MSGS; i++)
        {
            //Observe que a ordem das mensagens sao obedecidas
            int ret = sprintf(msg, "Hello, world! Number %d [%d]", i, rank);
            printf("->%s\n",msg);
            MPI_Send(msg, ret+1, MPI_CHAR, dst, tag, MPI_COMM_WORLD);
        }
    }
    // Processo com ranque 0 recebe num_procs-1 mensagens
    else
    {
        int ver, subver;
        MPI_Get_version(&ver, &subver);
        printf("Rodando em ambiente com versao %d.%d\n", ver, subver);
        for (int org = 1; org < num_procs; org++)
        {
            for (int i = 0; i < N_MSGS; i++)
            {
                MPI_Recv(msg, 200, MPI_CHAR, org, tag, MPI_COMM_WORLD, &status);
                printf("%s\n",msg);
            }
        }
    }
    MPI_Finalize();
    return 0;
}
