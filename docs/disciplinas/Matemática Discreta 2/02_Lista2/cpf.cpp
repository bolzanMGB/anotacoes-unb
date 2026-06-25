#include <stdio.h>
#include <string.h>

int validar_cpf(char cpf[9]) {
    
    if (strlen(cpf) != 9) return 0;

    for (int i = 0; i < 9; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') return 0;
    }
    return 1;
}

int validar_isbn(char isbn[12]) {

    if (strlen(isbn) != 12) return 0;

    for (int i = 0; i < 12; i++) {
        if (isbn[i] < '0' || isbn[i] > '9') return 0;
    }
    return 1;
}

void calcular_digitos_cpf(char cpf[9]) {
    int soma_1 = 0, soma_2 = 0, digito_1, digito_2;

    for (int i = 0; i < 9; i++) {
        soma_1 += (cpf[i] - '0') * (10 - i);
    }
    digito_1 = (soma_1 * 10) % 11;
    if (digito_1 == 10 || digito_1 == 11) digito_1 = 0;

    for (int i = 0; i < 9; i++) {
        soma_2 += (cpf[i] - '0') * (11 - i);
    }
    soma_2 += digito_1 * 2;
    digito_2 = (soma_2 * 10) % 11;
    if (digito_2 == 10 || digito_2 == 11) digito_2 = 0;

    printf("Os dois ultimos digitos do CPF sao: %d%d\n", digito_1, digito_2);
}

void calcular_digito_isbn(char isbn[12]) {
    int soma = 0, digito;

    for (int i = 0; i < 12; i++) {
        if (i % 2 == 0) {
            soma += (isbn[i] - '0');
        } else {
            soma += (isbn[i] - '0') * 3;
        }
    }

    digito = 10 - (soma % 10);
    if (digito == 10) digito = 0;

    printf("O ultimo digito do ISBN e: %d\n", digito);
}

int main() {
    int opcao;
    char numero[13];

    printf("Escolha a opcao:\n");
    printf("0 - Inserir CPF\n");
    printf("1 - Inserir ISBN\n");
    printf("Digite sua escolha: ");
    scanf("%d", &opcao);

    if (opcao == 0) {
        printf("Digite os 9 primeiros numeros do CPF: ");
        scanf("%s", numero);

        if (validar_cpf(numero)) {
            calcular_digitos_cpf(numero);
        } else {
            printf("CPF invalido!\n");
        }
    } else if (opcao == 1) {
        printf("Digite os 12 primeiros numeros do ISBN: ");
        scanf("%s", numero);

        if (validar_isbn(numero)) {
            calcular_digito_isbn(numero);
        } else {
            printf("ISBN invalido!\n");
        }
    } else {
        printf("Opcao invalida!\n");
    }

    return 0;
}
