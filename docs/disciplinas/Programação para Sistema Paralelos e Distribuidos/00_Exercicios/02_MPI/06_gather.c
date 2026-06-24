// cada processo vai te um array com dois números aleátorios, 
// esses números vão ser coletados e juntados em um array na raiz

#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int ret = MPI_Init (&argc, &argv);

    int rank;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (ret != MPI_SUCCESS){
        MPI_Abort(MPI_COMM_WORLD, ret);
    }

    int nums [2];

    double init = MPI_Wtime();
    srand(init * 1000000); 
    for (int i = 0; i < 2; i++){
        nums [i] = rand () % 100;
    }

    printf ("%d/%d: nums[%d,%d]\n", rank,num_procs,nums[0],nums[1]);

    MPI_Barrier(MPI_COMM_WORLD);

    int nums_coletados [num_procs * 2];
    
    MPI_Gather (&nums,2,MPI_INT,nums_coletados,2,MPI_INT,0,MPI_COMM_WORLD);

    if (rank == 0){
        for (int i =0; i < (num_procs * 2); i++){
            printf ("Recebido: %d\n", nums_coletados[i]);
        }
    }

    MPI_Finalize();

    return 0;
}
