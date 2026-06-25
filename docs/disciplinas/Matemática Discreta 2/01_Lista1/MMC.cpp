#include <stdio.h>

long long MDC(long long a, long long b) {
    long long resto = a % b;

    if (resto == 0){
        return b;
    }

    return MDC(b, resto);
}

long long MMC(long long a, long long b, long long mdc) {
    return (a * b) / mdc;
}

int main() {
    long long a;
    long long b;

    printf("Digite dois numeros: ");
    scanf("%lld %lld", &a, &b);

    long long mdc = MDC(a, b);  
    long long mmc = MMC(a, b, mdc); 
    printf("O MMC eh %lld\n", mmc); 

    return 0;
}
