#include <cstdio>  

void imprimirBordaSuperior(long long n) {
    printf("    ");
    for (long long j = 0; j < n; j++) {
        printf("%4lld", j);
    }
    printf("\n    ");
    for (long long j = 0; j < n; j++) {
        printf("_______");
    }
    printf("\n");
}

void adicaoModular(long long n, long long i, long long j) {
    if (i >= n) return;

    if (j == 0) {
        printf("%2lld |", i);
    }

    if (j < n) {
        printf("%4lld", (i + j) % n);
        adicaoModular(n, i, j + 1);
    } else {
        printf("\n");
        adicaoModular(n, i + 1, 0);
    }
}

int main() {
    long long n;

    printf("Digite o valor de n: ");
    scanf("%lld", &n);
    printf("Tabela de adicao modular Z%lld:\n", n);

    imprimirBordaSuperior(n);
    adicaoModular(n, 0, 0);

    return 0;
}
