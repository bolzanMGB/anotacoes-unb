#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <omp.h>

int main()
{
    printf("Iniciando! %d\n", omp_get_thread_num());
#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            {
                printf("Ola mundo! %d\n", omp_get_thread_num());
            }
#pragma omp section
            {
                printf("Ola de outra thread! %d\n", omp_get_thread_num());
            }
#pragma omp section
            {
                printf("Fim da thread! %d\n", omp_get_thread_num());
            }
        }
        printf("Fim... %d\n", omp_get_thread_num());
    }
    return 0;
}
