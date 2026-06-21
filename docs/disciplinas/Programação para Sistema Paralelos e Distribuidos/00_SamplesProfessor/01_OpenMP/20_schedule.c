#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel for num_threads(4) schedule(guided,1)
    for (int i = 0; i < 8; i++)
    {
        printf("Thread %d calculando %d\n", omp_get_thread_num(), i);
    }
    return 0;
    
    /*
     * Guided e' parecido com dynamic
     * Mas o chunck_size da primeria thread e' maior
     */
}
