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
    int vet[num_procs];

    if (rank == 0)
    {
        srand(MPI_Wtime() * 100000);
        printf("Vet: ");
        for (int i = 0; i < num_procs; i++)
        {
            vet[i] = rand() % 100;
            printf("%d ", vet[i]);
        }
        printf("\n");
    }
    int raiz = 0;
    //Veja os argumentos:
    //vet, 1: o processo 'raiz' envia 1 numero a cada processo
    //num, 1: cada processo recebe 1 numero
    //Scatterv pode ser usado para mudar o chunk e distribuir cargas nao igualmente (numero nao multiplo)
    int num = 0;
    MPI_Scatter(vet, 1, MPI_INT, &num, 1, MPI_INT, raiz, MPI_COMM_WORLD);

    printf("Recebido [%d] %d\n", rank, num);
    MPI_Finalize();
    return 0;
}
