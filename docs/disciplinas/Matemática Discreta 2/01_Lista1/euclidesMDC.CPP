#include <stdio.h>

long long MDC(long long a, long long b) {

    long long resto = a % b;

    if (resto == 0){
        return b;
    }

    return MDC (b, resto);
}

int main() {
    long long a;
    long long b;

    printf("Digite dois numeros: ");
    scanf("%lld %lld", &a, &b);

    long long mdc = MDC(a, b);
    printf("O MDC eh %lld\n", mdc); 

    return 0;
}
