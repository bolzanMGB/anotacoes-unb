#include <stdio.h>
#include <omp.h>
int func()
{
    printf("Calculando...\n");
    return 0;
}

int main()
{
#pragma omp parallel
    {
#pragma omp single
        printf("Oi\n");
        int resp = func();
#pragma omp barrier
#pragma omp single
        printf("Resposta: %d\n", resp);
    }
}
