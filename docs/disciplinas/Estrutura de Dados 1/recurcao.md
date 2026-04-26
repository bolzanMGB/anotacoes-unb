# Recursão em C

---

## 1. Conceitos Gerais

### 1.1 Definição:
**Recursão** é uma técnica de programação onde uma função chama a si mesma para resolver problemas menores da mesma natureza. Uma função recursiva deve ter:

- **Caso base**: Condição de parada que impede chamadas infinitas;
- **Passo recursivo**: Chamada à própria função com problema reduzido;

### 1.2 Vantagens:
- Código mais limpo e elegante para certos problemas;
- Facilita a solução de problemas complexos dividindo-os em subproblemas;

### 1.3 Desvantagens:
- Pode consumir mais memória (pilha de chamadas);
- Pode ser menos eficiente que soluções iterativas;

---

## 2.Usos de recurção
### 2.1 Fatorial por Recursão

O fatorial de um número n (n!) é o produto de todos os números inteiros positivos de 1 até n.

```c title="Exemplo:"
#include <stdio.h>

// Fatorial recursivo
int fat(int n) {
    if (n == 0) return 1;        // Caso base: 0! = 1
    return n * fat(n - 1);       // Passo recursivo: n! = n * (n-1)!
}

int main() {
    int n = 5;

    // Chamada da função e impressão do retorno
    printf("%d! = %d\n", n, fat(n)); // Saída: 5! = 120

    return 0;
}
```

```c title="Visualização do fluxo:"
fat(5) = 5 * fat(4)
       = 5 * (4 * fat(3))
       = 5 * (4 * (3 * fat(2)))
       = 5 * (4 * (3 * (2 * fat(1))))
       = 5 * (4 * (3 * (2 * (1 * fat(0)))))
       = 5 * (4 * (3 * (2 * (1 * 1))))
       = 5 * (4 * (3 * (2 * 1)))
       = 5 * (4 * (3 * 2))
       = 5 * (4 * 6)
       = 5 * 24
       = 120
```

---

### 2.2 Fibonacci por Recursão

A sequência de Fibonacci é definida como:

- Fib(0) = 0
- Fib(1) = 1  
- Fib(n) = Fib(n-2) + Fib(n-1)

```c title="Exemplo:"
#include <stdio.h>

int fib(int n) {
    if (n == 0 || n == 1) return n;  // Casos base
    return fib(n - 2) + fib(n - 1);  // Passo recursivo
}

int main() {
    int a = fib(6);
    printf("Fib(6) = %d\n", a); // Saída: Fib(6) = 8
    
    // Mostrando a sequência até o 6º termo
    for (int i = 0; i <= 6; i++) {
        printf("Fib(%d) = %d\n", i, fib(i));
    }
    return 0;
}
```

```c title="Visualização do fluxo:"
        fib(4)
        /    \
    fib(3)   fib(2)
    /    \    /    \
fib(2) fib(1) fib(1) fib(0)
/    \
fib(1) fib(0)
```

---

### 2.3 Avaliação de Expressões na Notação Polonesa

A notação polonesa (prefixa) coloca o operador antes dos operandos. Exemplo: `+ 3 4` em vez de `3 + 4`.

```c title="Exemplo:"
#include <stdio.h>

char a[] = "+ * 2 3 4"; // Expressão: (2 * 3) + 4 = 10
int i = 0;              // Índice global para percorrer a string

int eval() {
    int x = 0;
    
    // Pula espaços em branco
    while (a[i] == ' ') i++;
    
    if (a[i] == '+') {
        i++;
        return eval() + eval();  // Soma dos dois operandos seguintes
    }
    
    if (a[i] == '*') {
        i++;
        return eval() * eval();  // Multiplicação dos dois operandos seguintes
    }
    
    // Converte dígitos para número
    while (a[i] >= '0' && a[i] <= '9') {
        x = 10 * x + (a[i++] - '0');
    }
    
    return x;  // Retorna o número convertido
}

int main() {
    int resultado = eval();
    printf("Resultado: %d\n", resultado); // Saída: Resultado: 10
    return 0;
}
```

```c title="Visualização do fluxo:"
eval() → encontra '+' → chama eval() + eval()
    Primeiro eval(): encontra '*' → chama eval() * eval()
        Primeiro eval(): encontra '2' → retorna 2
        Segundo eval(): encontra '3' → retorna 3
        Retorna 2 * 3 = 6
    Segundo eval(): encontra '4' → retorna 4
    Retorna 6 + 4 = 10
```

---

### 2.4 Geração de Subconjuntos

Algoritmo para gerar todos os subconjuntos de um conjunto usando recursão.

```c title="Exemplo:"
#include <stdio.h>

void subsets(int sub[], int v[], int n, int i, int fim) {
    // Imprime o subconjunto atual
    printf("{ ");
    for (int j = 0; j < fim; j++) {
        printf("%d ", sub[j]);
    }
    printf("}\n");

    // Gera os subconjuntos recursivamente
    for (; i < n; i++) {
        sub[fim] = v[i];               // Adiciona o elemento atual ao subconjunto
        subsets(sub, v, n, i + 1, fim + 1);  // Chamada recursiva
    }
}

int main() {
    int v[] = {1, 2, 3};  // Array original
    int sub[3];           // Array para armazenar os subconjuntos
    int n = 3;            // Tamanho do array
    
    printf("Subconjuntos de {1, 2, 3}:\n");
    subsets(sub, v, n, 0, 0);  // Chama a função para gerar os subconjuntos
    
    return 0;
}
```

```c title="Saída:"
{ }
{ 1 }
{ 1 2 }
{ 1 2 3 }
{ 1 3 }
{ 2 }
{ 2 3 }
{ 3 }
```

**Explicação:** O algoritmo usa backtracking. Para cada elemento, temos duas opções: incluir ou não incluir no subconjunto atual. A recursão explora todas as combinações possíveis.

---

## 3. Considerações Importantes sobre Recursão

### 3.1 Recursão vs Iteração
- **Iteração**: geralmente é mais eficiente em termos de memória;
- **Recursão**: pode ser mais intuitiva para certos problemas (árvores, backtracking);

### 3.2 Recursão de Cauda (Tail Recursion)
Uma recursão onde a chamada recursiva é a última operação da função. Pode ser otimizada pelo compilador.

```c title="Exemplo de fatorial com recursão de cauda:"
int fat_tail(int n, int acc) {
    if (n == 0) return acc;
    return fat_tail(n - 1, n * acc);
}

int factorial(int n) {
    return fat_tail(n, 1);
}
```

### 3.3 Limitações
- **Estouro de pilha**: pode ocorrer com recursões muito profundas;
- **Múltiplas chamadas recursivas**: (como Fibonacci) podem ser extremamente ineficientes;

### 3.4 Memoização
Técnica para melhorar a eficiência armazenando resultados de chamadas anteriores.

```c title="Fibonacci com memoização:"
#include <stdio.h>
#define MAX 100

int memo[MAX] = {0};

int fib_memo(int n) {
    if (n == 0 || n == 1) return n;
    if (memo[n] != 0) return memo[n];
    
    memo[n] = fib_memo(n - 2) + fib_memo(n - 1);
    return memo[n];
}
```
