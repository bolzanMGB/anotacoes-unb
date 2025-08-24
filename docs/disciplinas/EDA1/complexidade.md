# Análise de Complexidade de Algoritmos

---

## 1. Definição

A **análise de complexidade** estuda o consumo de recursos (tempo e espaço) de um algoritmo em relação ao tamanho da entrada. 

A complexidade é expressa usando a **notação O** (Big O), que descreve o comportamento assintótico do algoritmo.

---

## 2. Classes de Complexidade

### 2.1 Complexidade Constante - O(1)
O tempo de execução não depende do tamanho da entrada.

#### 2.1.1 Características
- Instruções são realizadas um número fixo de vezes;
- Operações básicas: atribuição, comparação, acesso a índice;

#### 2.1.2 Quando ocorrre
- Acesso a elementos em arrays estáticos;
- Operações em listas duplamente encadeadas: remoção, inserção após/before um nó;
- Operações aritméticas básicas;

```c title="Exemplo:"
int operacao(int n, int a, char op) {
    int r = 0; // O(1) - atribuição
    
    if (op == '+')      // O(1) - comparação
        r = n + a;      // O(1) - aritmética + atribuição
    else if (op == '-') // O(1) - comparação
        r = n - a;      // O(1) - aritmética + atribuição
    else if (op == '*') // O(1) - comparação
        r = n * a;      // O(1) - aritmética + atribuição
    
    return r;           // O(1) - retorno
}
// Complexidade total: O(1)
```

---

### 2.2 Complexidade Linear - O(n)
O tempo de execução cresce linearmente com o tamanho da entrada.

#### 2.2.1 Características
- Percorre cada elemento da entrada uma vez
- Cresce a uma taxa constante

#### 2.2.2 Quando ocorrre
- Busca sequencial em array não ordenado
- Remoção de nó específico em lista simplesmente encadeada
- Fatorial por recursão (chamadas lineares)

```c title="Exemplo:"
int pesquisa(int x, int n, int v[]) {
    for (int i = 0; i < n && v[i] != x; i = i + 1); // O(n) - loop
    return i; // O(1)
}
// Complexidade total: O(n)

// Fatorial recursivo - O(n) linear
int fat(int n) {
    if (n == 0) return 1;        // O(1)
    return n * fat(n - 1);       // n chamadas recursivas
}
```

---

### 2.3 Complexidade Quadrática - O(n²)
O tempo de execução cresce proporcionalmente ao quadrado do tamanho da entrada.

#### 2.3.1 Características
- Dois loops aninhados, cada um percorrendo n elementos;
- Comum em algoritmos de ordenação simples;

#### 2.3.2 Quando ocorrre
- Bubble Sort, Selection Sort, Insertion Sort;
- Comparação de todos os pares em um conjunto;

```c title="Exemplo:"
void ordenacao(int v[], int n) {
    for (int i = 1; i < n; i++) {           // O(n)
        for (int j = i; j > 0 && v[j] < v[j - 1]; j--) { // O(n)
            troca(v[j], v[j - 1]);          // O(1) - operação constante
        }
    }
}
// Complexidade total: O(n²)
```

---

### 2.4 Complexidade Cúbica - O(n³)
O tempo de execução cresce proporcionalmente ao cubo do tamanho da entrada.

#### 2.4.1 Características
- Três loops aninhados, cada um percorrendo n elementos;
- Comum em operações com matrizes;

#### 2.4.2 Quando ocorrre
- Multiplicação de matrizes n × n;
- Algoritmos que processam dados tridimensionais;

```c title="Exemplo:"
void multiplica_matrizes(int A[3][3], int B[3][3], int C[3][3]) {
    for (int i = 0; i < 3; i++) {           // O(n)
        for (int j = 0; j < 3; j++) {       // O(n)
            C[i][j] = 0;                    // O(1)
            for (int k = 0; k < 3; k++) {   // O(n)
                C[i][j] += A[i][k] * B[k][j]; // O(1)
            }
        }
    }
}
// Complexidade total: O(n³)
```

---

### 2.5 Complexidade Exponencial - O(kⁿ)
O tempo de execução dobra (ou multiplica por k) a cada aumento unitário na entrada.

#### 2.5.1 Características
- Múltiplas chamadas recursivas em cada passo;
- Extremamente ineficiente para entradas grandes;

#### 2.5.2 Quando ocorrre
- Fibonacci recursivo ingênuo;
- Problema da mochila (força bruta);
- Torre de Hanoi;

```c title="Exemplo:"
// Fibonacci recursivo - O(2ⁿ)
int fib(int n) {
    if (n == 0 || n == 1) return n;         // O(1)
    return fib(n - 2) + fib(n - 2);         // 2 chamadas recursivas
}

// Geração de permutações - O(n!)
void anagram(char str[], int k) {
    int len = strlen(str);                  // O(n)
    if (k == len)                           // O(1)
        printf("%s\n", str);                // O(n)
    else {
        for (int i = k; i < len; i++) {     // O(n)
            swap_char(str, k, i);           // O(1)
            anagram(str, k + 1);            // Chamada recursiva
            swap_char(str, i, k);           // O(1)
        }
    }
}
// Relação de recorrência: T(n) = n × T(n-1) = O(n!)
```

---

### 2.6 Complexidade Logarítmica - O(log n)
O tempo de execução cresce logarithmicamente com o tamanho da entrada.

#### 2.6.1 Características
- Inversa da função exponencial;
- Muito eficiente para grandes entradas;
- Divide o problema pela metade a cada passo;


#### 2.6.2 Quando ocorrre
- Busca binária em array ordenado;
- Operações em árvores binárias balanceadas;

```c title="Exemplo:"
int pesquisa(int x, int v[], int esq, int dir) {
    if (esq > dir) return -1;               // O(1)
    
    int meio = (esq + dir) / 2;             // O(1)
    
    if (v[meio] == x) return meio;          // O(1)
    else if (v[meio] < x)
        return pesquisa(x, v, meio + 1, dir); // T(n/2)
    else
        return pesquisa(x, v, esq, meio - 1); // T(n/2)
}
// Relação de recorrência: T(n) = T(n/2) + O(1) = O(log n)
```

---

### 2.7 Complexidade Linearítmica - O(n log n)
Combina características lineares e logarítmicas.

#### 2.7.1 Características
- Divide e conquista: quebra problemas em subproblemas menores;
- Resolve subproblemas independentemente e combina soluções;
- Muito eficiente para ordenação;

#### 2.7.2 Quando ocorrre
- Merge Sort, Quick Sort, Heap Sort;
- Algoritmos de transformada rápida de Fourier;

```c title="Exemplo conceitual:"
// Merge Sort - O(n log n)
void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;    // O(1)
        merge_sort(arr, l, m);       // T(n/2)
        merge_sort(arr, m + 1, r);   // T(n/2)
        merge(arr, l, m, r);         // O(n)
    }
}
// Relação: T(n) = 2T(n/2) + O(n) = O(n log n)
```

---

## 3. Comparação de Complexidades

| Complexidade | n = 10 | n = 100 | n = 1000 | Exemplo |
|-------------|--------|---------|----------|---------|
| O(1)        | 1      | 1       | 1        | Acesso a array |
| O(log n)    | ~3     | ~7      | ~10      | Busca binária |
| O(n)        | 10     | 100     | 1000     | Busca sequencial |
| O(n log n)  | ~30    | ~700    | ~10000   | Merge Sort |
| O(n²)       | 100    | 10000   | 1000000  | Bubble Sort |
| O(n³)       | 1000   | 1000000 | 10⁹      | Multiplicação de matrizes |
| O(2ⁿ)       | 1024   | 1.3×10³⁰ | 1.1×10³⁰¹ | Fibonacci recursivo |
| O(n!)       | 3.6×10⁶ | 9.3×10¹⁵⁷ | 4.0×10²⁵⁶⁷ | Permutações |

---

## 4. Considerações Importantes

### 4.1 Complexidade de Espaço
Além do tempo, também analisamos o consumo de memória:

- **O(1)**: espaço constante (variáveis fixas);
- **O(n)**: espaço linear (arrays, listas);
- **O(n²)**: espaço quadrático (matrizes n×n);

### 4.2 Melhor Caso, Caso Médio e Pior Caso
- **Melhor caso**: menor tempo possível (ex: elemento encontrado logo);
- **Caso médio**: tempo esperado para entradas aleatórias; 
- **Pior caso**: maior tempo possível (ex: elemento não existe);

