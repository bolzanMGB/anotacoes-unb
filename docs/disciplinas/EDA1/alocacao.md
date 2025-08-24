# Alocação de Memória em C

---

## 1. Tipos de Espaço de Endereços

A memória de um processo é dividida em segmentos distintos, cada um com propósito específico:

- **Text**: contém o código do programa e suas constantes. Este segmento é alocado durante a criação do processo (`exec`) e permanece do mesmo tamanho durante toda a vida do processo.

- **Data**: este segmento é a memória de trabalho do processo, onde ficam alocadas as variáveis globais e estáticas. Tem tamanho fixo ao longo da execução do processo.

- **Stack**: contém a pilha de execução, onde são armazenadas os parâmetros, endereços de retorno e variáveis locais de funções. Pode variar de tamanho durante a execução do processo.

- **Heap**: contém blocos de memória alocadas dinamicamente, a pedido do processo, durante sua execução. Varia de tamanho durante a vida do processo. Gerenciado pelo sistema operacional.

---

## 2. Tipos de Alocação de Memória

### 2.1 Alocação Estática
- Ocorre quando são declaradas variáveis globais (alocadas fora de funções) ou estáticas (usando o modificador `static`)
- Geralmente alocadas em *Data*
- Uma variável alocada estaticamente mantém seu valor durante toda a vida do programa, exceto quando explicitamente modificada

### 2.2 Alocação Automática
- Ocorre quando são declaradas variáveis locais e parâmetros de funções
- Geralmente é usada a pilha (*stack*)
- O espaço para a alocação dessas variáveis é reservado de forma automática na pilha de execução do programa a cada chamada da função, e liberado quando a função termina
- Alocação e desalocação automática (SO — sistema operacional)

### 2.3 Alocação Dinâmica
- O programa solicita explicitamente áreas de memória ao sistema operacional, as utiliza e depois as libera quando não forem mais necessárias
- O controle das áreas alocadas dinamicamente é manual: o programador é responsável por liberar as áreas alocadas
- Geralmente alocadas na área de memória *heap*
- Permite alocar memória durante a execução do programa
- Permite alocar tamanhos maiores que a área reservada na stack
```c title="Exemplo:"
#include <stdio.h>

int a = 0;  // variável global, aloc. estática

void incrementa(void)
{
    int b = 0;        // variável local, aloc. automática
    static int c = 0; // variável local, aloc. estática

    printf("a: %d, b: %d, c: %d\n", a, b, c);
    a++;
    b++;
    c++;
}

int main(void)
{
    int i;

    for (i = 0; i < 5; i++)
        incrementa();

    return 0;
}
```

---

## 3. Operadores e Funções para Alocação Dinâmica

### 3.1 sizeof()
Retorna o tamanho em bytes de um tipo de dado ou estrutura

```c title="Exemplo:"
#include <stdio.h>

struct endereco {
    char rua[100];
    int numero;
};

int main() {
    printf("%lu bytes \n", sizeof(int)); // 4 bytes
    printf("%lu bytes \n", sizeof(float)); // 4 bytes
    printf("%lu bytes \n", sizeof(double)); // 8 bytes
    printf("%lu bytes \n", sizeof(char)); // 1 byte
    printf("%lu bytes \n", sizeof(struct endereco)); // 104 bytes
    return 0;
}
```

### 3.2 malloc()
Aloca uma quantidade específica de bytes na memória heap

```c title="Exemplo:"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = (int *)malloc(sizeof(int)); // Aloca espaço para um inteiro
    if (p == NULL) {
        printf("Falha na alocação de memória!\n");
        return 1;
    }
    
    *p = 42;
    printf("Valor: %d\n", *p);
    
    free(p); // Libera a memória alocada
    return 0;
}
```

### 3.3 calloc()
Aloca memória para um array de elementos, inicializando todos os bytes com zero

```c title="Exemplo:"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = calloc(5, sizeof(int)); // Aloca array de 5 inteiros (todos zeros)
    if (p == NULL) {
        printf("Falha na alocação de memória!\n");
        return 1;
    }
    
    for (int i = 0; i < 5; i++) {
        printf("p[%d] = %d\n", i, p[i]); // Todos serão zero
    }
    
    free(p); // Libera a memória alocada
    return 0;
}
```

### 3.4 realloc()
Altera o tamanho do bloco de memória apontado por um ponteiro

```c title="Exemplo:"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = malloc(sizeof(int)); // Aloca espaço para 1 inteiro
    *p = 10;
    
    p = realloc(p, 4 * sizeof(int)); // Redimensiona para 4 inteiros
    
    p[1] = 20;
    p[2] = 30;
    p[3] = 40;
    
    for (int i = 0; i < 4; i++) {
        printf("p[%d] = %d\n", i, p[i]);
    }
    
    free(p); // Libera a memória alocada
    return 0;
}
```

### 3.5 free()
Libera o espaço de memória apontado por um ponteiro previamente alocado

```c title="Exemplo:"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = malloc(10 * sizeof(int)); // Aloca array de 10 inteiros
    
    if (p != NULL) {
        for (int i = 0; i < 10; i++) {
            p[i] = i * 10;
        }
        
        // Usa o array...
        
        free(p); // Libera a memória quando não for mais necessária
        p = NULL; // Boa prática: definir ponteiro como NULL após liberar
    }
    
    return 0;
}
```

---

## 4. Boas Práticas com Alocação Dinâmica

1. **Sempre verifique** se a alocação foi bem-sucedida (ponteiro != NULL)
2. **Sempre libere** a memória alocada quando não for mais necessária
3. **Defina ponteiros como NULL** após liberar a memória para evitar "dangling pointers"
4. **Evite vazamentos de memória** - toda memória alocada deve ser liberada
5. **Use free() apenas com ponteiros** que foram alocados com malloc, calloc ou realloc

```c title="Exemplo de uso correto:"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array = NULL;
    int tamanho = 5;
    
    // Aloca memória
    array = (int *)malloc(tamanho * sizeof(int));
    if (array == NULL) {
        printf("Erro: não foi possível alocar memória!\n");
        return 1;
    }
    
    // Usa a memória alocada
    for (int i = 0; i < tamanho; i++) {
        array[i] = i * 2;
    }
    
    // Libera a memória quando não for mais necessária
    free(array);
    array = NULL; // Boa prática
    
    return 0;
}
```