#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define VET_SIZE 400000000
int main()
{
    srand(123);
    int *vet;
    vet = malloc(VET_SIZE*sizeof(int));
    for (int i = 0; i < VET_SIZE; i++)
        vet[i] = rand() % 50;

    int n = 1;
    int q_n = 0;
    int q_nt[256] = {};
    int threads_num = omp_get_max_threads();
#pragma omp parallel for reduction(+:q_n)
    for (int i = 0; i < VET_SIZE; i++)
    {
        const int id = omp_get_thread_num();
        if (vet[i] == n)
        {
            q_n++;
            q_nt[id]++;
        }
    }

    int tot = 0;
    for (int i = 0; i < threads_num; i++)
    {
        tot += q_nt[i];
    }
    printf("q_n = %d\n", q_n);
    printf("tot = %d\n", tot);
    return 0;
}
