#include <cstdio>
#include <cctype>
#include <cmath> 

int totiente(int p, int q, int e) {
    int z = (p - 1) * (q - 1);
    if (1 < e && e < z) {
        return 1;
    } else {
        return 0;
    }
}

int letraParaValor(char letra) {
    letra = toupper(letra);
    return 11 + (letra - 'A');
}

int criptografia(int letra, int e, int n) {
    return ((int)pow(letra, e)) % n;
}

int main() {
    int p, q, e, b;
    char palavra[100]; 
    printf("Digite o valor de p: ");
    scanf("%d", &p);
    printf("Digite o valor de q: ");
    scanf("%d", &q);
    printf("Digite o valor de e: ");
    scanf("%d", &e);
    printf("Digite o tamanho do bloco: ");
    scanf("%d", &b);
    getchar();

    printf("Digite a palavra: ");
    scanf("%99s", palavra); 

    int n = p * q;

    if (totiente(p, q, e)) {
        printf("Aqui esta: \n");
        for (int i = 0; palavra[i] != '\0'; i++) {
            int valor = letraParaValor(palavra[i]);
            int criptografado = criptografia(valor, e, n);
            printf("%d", criptografado);
        }
        printf("\n");
    } else {
        printf("Os valores nao sao primos.\n");
    }
    return 0;
}
