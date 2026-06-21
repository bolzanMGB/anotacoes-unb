#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

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

    double init = MPI_Wtime();
    srand(init * 1000000); //Os processos iniciam em tempo parecido... Multiplicar por 1M diferencia os seeds
    int num = rand() % 100;
    printf("[%d] %lf: num %d\n", rank, init, num);

    MPI_Barrier(MPI_COMM_WORLD);
    int vetor[num_procs];
    int raiz = 0;
    //Veja os argumentos:
    //num, 1: cada processo envia 1 numero
    //vetor, 1: o processo 'raiz' recebe 1 numero de cada processo
    //A ordem de concatenacao nao depende da raiz
    MPI_Gather(&num, 1, MPI_INT, vetor, 1, MPI_INT, raiz, MPI_COMM_WORLD);
    if (rank == raiz)
    {
        for (int i = 0; i < num_procs; i++)
        {
            printf("Recebido [%d] %d\n", i, vetor[i]);
        }
    }
    MPI_Finalize();
    return 0;
}
