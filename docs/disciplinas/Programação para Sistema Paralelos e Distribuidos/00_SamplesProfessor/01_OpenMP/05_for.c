#include <stdio.h>
#include <omp.h>

#define VET_SIZE 100
int main()
{
#pragma omp parallel for
    for (int i = 0; i < 10; i++)
    {
        printf("Laco %d da thread %d\n", i, omp_get_thread_num());
    }
    return 0;
}
