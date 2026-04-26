# Ponteiros em C

---

## 1. Conceitos Gerais
- **\*ponteiro** = acessa o conteúdo armazenado no endereço apontado pelo ponteiro
- **&variavel** = mostra o endereço da variável
- **%p** = especificador de formato para mostrar endereços de memória


```c title="Exemplo:"
#include <stdio.h>
int main() {
    int age = 1;
    int *pAge = &age; // ponteiro pAge recebe o endereço de age

    printf("valor de age: %d \n", age);       
    // Saída: valor de age: 1
    // -> imprime o valor armazenado em age

    printf("endereco de age: %p \n", &age);   
    // Saída: endereco de age: 0x7ffee6d2c8ac
    // -> imprime o endereço de memória da variável age

    printf("valor de pAge: %d \n", *pAge);    
    // Saída: valor de pAge: 1
    // -> *pAge acessa o conteúdo do endereço que pAge aponta, ou seja, o valor de age

    printf("endereco de pAge: %p \n", &pAge); 
    // Saída: endereco de pAge: 0x7ffee6d2c8b0
    // -> imprime o endereço de memória da variável ponteiro pAge 
    //    (diferente do endereço armazenado dentro dele!)

    return 0;
}

```

---
## 2. Ponteiros como Parâmetros

A passagem de parâmetros por ponteiros permite modificar valores fora do escopo da função.

```c title="Exemplo:"
#include <stdio.h>

void troca(int *p, int *q) { 
    *p = 89;
    *q = 45;
}

int main() {
    int a = 3, b = 9;

    troca(&a, &b); // passando os endereços

    printf("%d %d\n", a, b); // printa 89 e 45
    return 0;
}
```

---

## 3. Ponteiros x Arrays x Matrizes

Em C, o **nome de um vetor** é equivalente ao endereço de seu primeiro elemento (`&v[0]`). Assim, um ponteiro pode percorrer arrays e até matrizes lineares.

```c title="Exemplo:"
#include <stdio.h>

int main() {
    int v[2] = {1, 2}; // array
    int *p;            // ponteiro de inteiro

    p = v; // ou p = &v[0]
    
    p[0] = 5; // altera o primeiro valor do array v

    printf("%d %d\n", p[0], p[1]); 
    printf("%d %d\n", v[0], v[1]); 

    --------------------------------------------------------------------------

    int m[2][2] = {{1, 2}, {3, 4}}; // matriz 2x2

    printf("%d\n", m[1][1]); // elemento da linha 2, coluna 2 (4)

    p = m[0]; // ou (int *)m
              // p aponta para o endereço de m[0][0]

    for (int i = 0; i < 4; i++)
        printf("%2d ", p[i]); // printa 1 2 3 4

    return 0;
}
```

---

## 4. Ponteiros x Structs
Quando trabalhamos com structs, 

- Usamos . para acessar campos de variáveis normais 
- Usamos -> para acessar campos de ponteiros para struct.

```c title="Exemplo:"
#include <stdio.h>

typedef struct {
    int value;
} Point;

int main() {
    Point s;
    Point *ptr = &s;

    s.value = 20;       // acesso direto pela struct
    (*ptr).value = 40;  // acesso via ponteiro com ()
    ptr->value = 30;    // acesso simplificado com ->

    printf("%d\n", s.value); // retorna 30
    return 0;
}
```