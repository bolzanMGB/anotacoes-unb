#include <stdio.h>

#include <string.h>
#include "mpi.h"
#include <stdlib.h>

#define N 2
int main (int argc, char * argv[]){
    int ret = MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    
    if (ret != MPI_SUCCESS){
        MPI_Abort(MPI_COMM_WORLD, ret);
    }
    
    int nums[N];
    int total [N];

    srand (MPI_Wtime() * 100000);

    printf ("Sou %d: meus valores são:\n", rank);
    for (int i = 0; i < N; i++){
        nums[i] = rand () % 10;
        printf ("%d\n", nums[i]);
    }

    MPI_Reduce (nums, total, N, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  
    if (rank == 0){
        printf ("O total é: ");
        for (int i = 0; i < N; i++){
            printf ("%d ", total[i]);
        }
    }

    MPI_Finalize();

    return 0;
}