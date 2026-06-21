#include <stdio.h>
#include <string.h>

#define N_PROCS 4
int main(int argc, char *argv[])
{
    char msg[200];
    char random_seeds[N_PROCS] = { };
    int n_msg;

    scanf("%d", &n_msg);
    for (int i = 1; i < N_PROCS; i++)
    {
        unsigned int seed;
        scanf("%u", &seed);

        srand(seed);
        int sum = 0;
        for (int j = 0; j < n_msg; j++)
            sum += rand();
        printf("%d\n", sum);
    }
    return 0;
}
