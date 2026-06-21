#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>

#define N 100
int main()
{
    float a[N], b[N];
    int i, n = N;
    float temp, csum = 0;
    srand(123);
    for (int i = 0; i < N; i++)
    {
        a[i] = (rand() % 50) + 1;
        b[i] = (rand() % 50) + 1;
    }

    n = N;
#pragma omp parallel shared(a,b,n) private(i, temp) firstprivate(csum)
    {
        for(i = 0; i < n; i++)
        {
            temp = a[i] / b[i];
            csum += cos(temp);
        }
        printf("[%d] %f\n", omp_get_thread_num(), csum);
    }
    printf("%f\n", csum);
    return 0;
}
