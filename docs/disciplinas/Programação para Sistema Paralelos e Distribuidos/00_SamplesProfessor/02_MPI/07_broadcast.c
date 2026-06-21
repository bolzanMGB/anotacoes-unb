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
    
    int num = rank;
    int raiz = 0;
    if (rank == raiz)
    {
        scanf("%d", &num);
    }
    //Todos precisam chamar Bcast
    //Processo 'raiz' (0) envia, os outros recebem
    //Nota: nao precisa ser o mesmo broadcast
    MPI_Bcast(&num, 1, MPI_INT, raiz, MPI_COMM_WORLD);

    //Cuidado para nao confundir...
    //raiz = 1;
    //MPI_Bcast(&num, 1, MPI_INT, raiz, MPI_COMM_WORLD);

    printf("Processo %d recebeu %d\n", rank, num);
    MPI_Finalize();
    return 0;
}
