#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel
    {
        int id = 0;
        printf("Oi da thread %d\n", id);
    }
    return 0;
}
