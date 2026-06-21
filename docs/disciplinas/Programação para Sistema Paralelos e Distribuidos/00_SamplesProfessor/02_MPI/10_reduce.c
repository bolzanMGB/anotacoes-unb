#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

#define N 2

int main(int argc, char *argv[])
{
    int rank, num_procs, ret;
    int vet[N];

    ret = MPI_Init(&argc, &argv);
    if (ret != MPI_SUCCESS)
    {
        printf("Erro fatal %d.\n", ret);
        MPI_Abort(MPI_COMM_WORLD, ret);
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    srand(MPI_Wtime() * 100000);
    printf("[%d] Enviando: ", rank);
    for (int i = 0; i < N; i++)
    {
        vet[i] = rand() % 10;
        printf("%d ", vet[i]);
    }
    printf("\n");

    int raiz = 0;
    int total[N] = { };
    MPI_Reduce(vet, total, N, MPI_INT, MPI_SUM, raiz, MPI_COMM_WORLD);

    //if (rank == raiz)
    {
        printf("Recebido: ");
        for (int i = 0; i < N; i++)
        {
            printf("%d ", total[i]);
        }
        printf("\n");
    }
    MPI_Finalize();

    //Operacoes:
    //MPI_SUM
    //MPI_MAX
    //MPI_MIN
    //MPI_PROD
    //MPI_LAND (E logico)
    //MPI_BAND (E bit-a-bit)
    //MPI_LOR
    //MPI_BOR
    return 0;
}
