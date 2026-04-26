# Busca Binária

---

## 1. Conceitos Gerais

A **busca binária** é um algoritmo eficiente para encontrar elementos em arrays **ordenados**. 

Ele funciona dividindo repetidamente o intervalo de busca pela metade, aproveitando a propriedade de ordenação para descartar metade dos elementos a cada iteração.

**Princípio fundamental**: "Divide and Conquer" (Dividir e Conquistar).

---

## 2. Implementação da Busca Binária

### 2.1 Estruturas de Dados

```c title="Implementação:"
#define key(A) (A.chave)  // Macro para acessar a chave

typedef int Key;  // Tipo da chave

typedef struct data Item;  // Tipo do item
struct data { 
    Key chave;     // Chave para busca
    char info[100]; // Informação adicional
};
```

### 2.2 Implementação Recursiva

```c title="Implementação:"
int binary_search(Item *v, int l, int r, Key k) {
    // Condição de parada: intervalo inválido
    if (l > r) return -1;

    // Calcular o índice central (evita overflow)
    int m = l + (r - l) / 2;

    // Comparar k com o elemento central
    if (k == key(v[m])) return m;  // Elemento encontrado

    // Procurar na metade esquerda
    if (k < key(v[m]))
        return binary_search(v, l, m - 1, k);

    // Procurar na metade direita
    return binary_search(v, m + 1, r, k);
}
```

### 2.3 Implementação Iterativa

```c title="Implementação:"
int binary_search_iterative(Item *v, int n, Key k) {
    int l = 0, r = n - 1;
    
    while (l <= r) {
        int m = l + (r - l) / 2;
        
        if (k == key(v[m])) return m;      // Encontrado
        if (k < key(v[m])) r = m - 1;      // Buscar à esquerda
        else l = m + 1;                    // Buscar à direita
    }
    
    return -1;  // Não encontrado
}
```

---

## 3. Exemplo Passo a Passo

### 3.1 Dados de Entrada

```c title="Exemplo:"
V[10] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
Índices: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
Procurar: 7
```

### 3.2 Execução do Algoritmo
```c title="Exemplo:"
Passo 1: l = 0, r = 9
- m = (0 + 9) / 2 = 4
- V[4] = 5 < 7 → Buscar à direita

Passo 2: l = 5, r = 9  
- m = 5 + (9 - 5) / 2 = 7
- V[7] = 8 > 7 → Buscar à esquerda

Passo 3: l = 5, r = 6
- m = 5 + (6 - 5) / 2 = 5
- V[5] = 6 < 7 → Buscar à direita

Passo 4: l = 6, r = 6
- m = 6 + (6 - 6) / 2 = 6
- V[6] = 7 == 7 → **Elemento encontrado!**

Retorno: índice 6
```

---

## 4. Complexidade 

| Caso | Complexidade | Descrição |
|------|-------------|-----------|
| **Melhor caso** | O(1) | Elemento no meio do array |
| **Caso médio** | O(log n) | Distribuição uniforme |
| **Pior caso** | O(log n) | Elemento nas extremidades ou ausente |

---

## 5. Variações da Busca Binária

### 5.1 Encontrar Primeira Ocorrência
```c
int binary_search_first(Item *v, int n, Key k) {
    int l = 0, r = n - 1;
    int result = -1;
    
    while (l <= r) {
        int m = l + (r - l) / 2;
        
        if (k == key(v[m])) {
            result = m;      // Registra posição
            r = m - 1;       // Continua procurando à esquerda
        }
        else if (k < key(v[m])) r = m - 1;
        else l = m + 1;
    }
    
    return result;
}
```

### 5.2 Encontrar Última Ocorrência
```c
int binary_search_last(Item *v, int n, Key k) {
    int l = 0, r = n - 1;
    int result = -1;
    
    while (l <= r) {
        int m = l + (r - l) / 2;
        
        if (k == key(v[m])) {
            result = m;      // Registra posição
            l = m + 1;       // Continua procurando à direita
        }
        else if (k < key(v[m])) r = m - 1;
        else l = m + 1;
    }
    
    return result;
}
```

### 5.3 Encontrar Menor Elemento Maior ou Igual
```c
int binary_search_ceiling(Item *v, int n, Key k) {
    int l = 0, r = n - 1;
    int result = -1;
    
    while (l <= r) {
        int m = l + (r - l) / 2;
        
        if (k == key(v[m])) return m;
        
        if (k < key(v[m])) {
            result = m;      // Possível candidato
            r = m - 1;
        }
        else {
            l = m + 1;
        }
    }
    
    return result;
}
```


---

## 6. Análise do algoritmo

### 6.1 Pré-requisitos
- **Array deve estar ordenado**;
- **Acesso aleatório** aos elementos (índices);
- **Operador de comparação** definido;

### 6.2 Vantagens
- **Extremamente eficiente** (O(log n));
- **Baixo consumo de memória** (iterativa: O(1));
- **Previsível** e confiável;

### 7.3 Limitações
- **Requer array ordenado** (custo de ordenação);
- **Não funciona** com listas encadeadas;
- **Overhead** para dados muito pequenos;