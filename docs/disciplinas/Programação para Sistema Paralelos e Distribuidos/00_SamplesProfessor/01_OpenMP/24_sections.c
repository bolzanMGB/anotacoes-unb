#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <omp.h>

int main()
{
    printf("Iniciando! %d\n", omp_get_thread_num());
#pragma omp parallel sections
    {
#pragma omp section
        {
            printf("Ola mundo! %d\n", omp_get_thread_num());
        }
#pragma omp section
        {
            printf("Ola de outra thread! %d\n", omp_get_thread_num());
        }
    }
    return 0;
}
