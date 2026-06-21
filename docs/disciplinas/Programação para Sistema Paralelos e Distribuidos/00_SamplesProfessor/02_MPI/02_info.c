#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int rank, num_procs, ret;
    int tag = 0;
    char msg[200 + MPI_MAX_PROCESSOR_NAME];

    char name[MPI_MAX_PROCESSOR_NAME];
    double t_init, t_end;

    MPI_Status status;
    ret = MPI_Init(&argc, &argv);
    t_init = MPI_Wtime();
    if (ret != MPI_SUCCESS)
    {
        printf("Erro fatal %d.\n", ret);
        MPI_Abort(MPI_COMM_WORLD, ret);
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    
    MPI_Get_processor_name(name, &ret);
    // Todos processos que nao sejam 0 enviam mensagens
    if (rank != 0)
    {
        int dst = 0;
        int ret = sprintf(msg, "Hello, world! [%s] [%d]", name, rank);
        printf("->%s\n",msg);
        MPI_Send(msg, ret+1, MPI_CHAR, dst, tag, MPI_COMM_WORLD);
    }
    // Processo com ranque 0 recebe num_procs-1 mensagens
    else
    {
        int ver, subver;
        MPI_Get_version(&ver, &subver);
        printf("Rodando em ambiente com versao %d.%d\n", ver, subver);
        for (int org = 1; org < num_procs; org++)
        {
            MPI_Recv(msg, 200, MPI_CHAR, org, tag, MPI_COMM_WORLD, &status);
            // Imprime as mensagens recebidas
            printf("%s\n",msg);
        }
        t_end = MPI_Wtime();
        //Wtick retorna a precisao do ambiente.
        //Normalmente nao executamos em toda execucao
        printf("Tempo gasto %3.3lf +- %3.3e\n", t_end - t_init, MPI_Wtick());
    }
    MPI_Finalize();
    return 0;
}



