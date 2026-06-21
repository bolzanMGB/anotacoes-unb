#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main()
{
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int total = omp_get_num_threads();

        printf("Oi da thread %d/%d\n", id, total);
    }
    return 0;
}
