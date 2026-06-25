#include <stdio.h>

long long fibonaci(long long a) {

    if (a == 1) 
        return 1;
    if (a ==0){
        return 0;
    }
    else{
        return fibonaci(a - 1) + fibonaci (a - 2); 
    }
}

int main() {
    long long numTeste;
    printf("Digite um numero: ");
    scanf("%lld", &numTeste);

    int resultado = fibonaci(numTeste);
    printf("Fibonacci de %lld eh %lld\n", numTeste, resultado); 

    return 0;
}


