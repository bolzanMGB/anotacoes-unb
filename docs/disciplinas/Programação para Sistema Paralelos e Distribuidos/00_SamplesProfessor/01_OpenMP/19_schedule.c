#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel for num_threads(4) schedule(dynamic,1)
    for (int i = 0; i < 8; i++)
    {
        printf("Thread %d calculando %d\n", omp_get_thread_num(), i);
    }
    return 0;
    
    /*              Static          | Dynamic
     * Atribuicao | Começo do Loop  | Durante a execucao
     * Overhead   | Baixo, sem sync | Alto, sempre sincroniza
     * Caso de uso| Cargas parecidas| Casos imprevisiveis, irregulares
     */
}
