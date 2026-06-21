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
    //Qual escope das variaveis paralelas?
#pragma omp parallel
    {
        for(i = 0; i < n; i++)
        {
            temp = a[i] / b[i];
            csum += cos(temp);
        }
    }
    printf("%f\n", csum);
    return 0;
}
