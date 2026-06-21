#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel for num_threads(4) schedule(runtime)
    for (int i = 0; i < 8; i++)
    {
        printf("Thread %d calculando %d\n", omp_get_thread_num(), i);
    }
    return 0;
    
    /* 
     * Use o comando para mudar (escolha o schedule adequado)
     * export OMP_SCHEDULE=static
     */
}
