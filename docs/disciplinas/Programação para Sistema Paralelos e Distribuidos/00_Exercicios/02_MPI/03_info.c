#include <stdio.h>
#include "mpi.h"
#include <string.h>

#define n_msgs 3
// MSTDTC
int main (int argc, char * argv[]){
    
    double t_fim;
    int ret = MPI_Init (&argc, &argv);
    double t_inicio = MPI_Wtime();

    int rank;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    int num_procs;
    MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

    MPI_Status status;
    int tag = 0;
    char msg [200];

    if (ret != MPI_SUCCESS){
        MPI_Abort(MPI_COMM_WORLD, ret);
    }

    if (rank != 0){
        int dst = 0;

        for (int i = 0; i < n_msgs; i++){
            sprintf (msg, "Mensagem %d do processo %d/%d\n", i, rank, num_procs);
            int size = strlen(msg) + 1;
            MPI_Send (msg,size,MPI_CHAR,dst,tag,MPI_COMM_WORLD);
        } 
    }
    else{
        char name [MPI_MAX_PROCESSOR_NAME];
        MPI_Get_processor_name(name, &ret);

        int ver; 
        int subver;
        MPI_Get_version(&ver, &subver);

        printf("Sou o Processo 0, estou rodando em %s na versão %d.%d e recebi:\n", name, ver, subver);
        for (int org = 1; org < num_procs; org++){
            for (int j = 0; j < n_msgs; j++){
                MPI_Recv (msg,200,MPI_CHAR,org,tag,MPI_COMM_WORLD,&status);
                printf ("%s",msg);
            }
        }
        t_fim = MPI_Wtime();
        printf ("Tempo gasto = %3.6lf ms\n", (t_fim - t_inicio) * 1000.0);
    }

    MPI_Finalize();
    return 0;
}