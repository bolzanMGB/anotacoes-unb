#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define VET_SIZE 100
int main()
{
    srand(123);
    int *vet;
    vet = malloc(VET_SIZE*sizeof(int));
    for (int i = 0; i < VET_SIZE; i++)
        vet[i] = rand() % 50;

    int n = 1;
    int q_n = 0;
    for (int i = 0; i < VET_SIZE; i++)
    {
        if (vet[i] == n)
            q_n++;
    }
    printf("q_n = %d\n", q_n);
    return 0;
}
