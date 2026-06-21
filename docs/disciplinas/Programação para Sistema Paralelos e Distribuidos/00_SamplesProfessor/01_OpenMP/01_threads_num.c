#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main()
{
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("Oi da thread %d\n", id);
    }
    return 0;
}
