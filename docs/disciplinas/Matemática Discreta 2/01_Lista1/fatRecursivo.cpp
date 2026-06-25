#include <stdio.h>

long long fatRecursivo(long long a) {
    if (a == 0 || a == 1) 
        return 1;
    else
        return a * fatRecursivo(a - 1); 
}

int main() {
    int numTeste;
    printf("Digite um numero: ");
    scanf("%d", &numTeste);

    if (numTeste < 0) {
        printf("Fatorial de numero negativo nao existe.\n");
    } else {
        long long resultado = fatRecursivo(numTeste);
        printf("Fatorial de %lld eh %lld\n", numTeste, resultado); 
    }

    return 0;
}
