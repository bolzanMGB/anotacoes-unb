# Quick Sort

---

## 1. Conceitos Gerais

O **Quick Sort** (Ordenação Rápida) é um algoritmo de ordenação eficiente que segue a abordagem **"dividir para conquistar"**. Desenvolvido por Tony Hoare em 1959, é um dos algoritmos mais utilizados na prática devido à sua excelente performance.

**Princípio fundamental**: "Selecionar um pivô, particionar e ordenar recursivamente" - escolhe um elemento como pivô, rearranja o array colocando elementos menores à esquerda e maiores à direita, e aplica recursivamente o processo.

---

## 2. Implementação do Quick Sort

### 2.1 Função Principal de Ordenação

```cpp title="Função principal do Quick Sort:"
void quick_sort(int *v, int l, int r) {
    // Condição de parada: subarray de tamanho 0 ou 1
    if (r <= l) return;

    // Posicionar o pivô e obter sua posição final
    int p = partition(v, l, r);

    // Ordenar recursivamente os subarrays
    quick_sort(v, l, p - 1); // Elementos menores que o pivô
    quick_sort(v, p + 1, r);  // Elementos maiores que o pivô
}
```

### 2.2 Particionamento com Pivô à Direita (Sedgewick)

```cpp title="Partição com pivô à direita:"
int partition(int *v, int l, int r) {
    int pivot = v[r];  // O pivô é o último elemento
    int i = l - 1, j = r;

    // Enquanto os índices não se cruzarem
    while (i < j) {
        // Procurar elementos maiores que o pivô (da esquerda para direita)
        while (v[++i] < pivot) ; 

        // Procurar elementos menores que o pivô (da direita para esquerda)
        while (v[--j] > pivot && j > l) ; 

        // Se o maior está atrás do menor, troca-os
        if (i < j) {
            exch(v[i], v[j]); // Troca os elementos
        }
    }

    // Posiciona o pivô na posição correta
    exch(v[i], v[r]); 

    // Retorna a nova posição do pivô
    return i;
}
```

### 2.3 Particionamento com Pivô à Esquerda (Sedgewick)

```cpp title="Partição com pivô à esquerda:"
int partition(int *v, int l, int r) {
    int pivot = v[l];    // O pivô é o primeiro elemento
    int i = l;           // Índice que avança da esquerda
    int j = r + 1;       // Índice que recua da direita

    while (i < j) {
        // Procurar elementos maiores que o pivô (E→D)
        while (v[++i] < pivot && i < r) ; 

        // Procurar elementos menores que o pivô (D→E)
        while (pivot < v[--j] && j > l) ; 

        // Se os elementos estão na ordem errada, troca-os
        if (i < j) {
            exch(v[i], v[j]);  
        }
    }

    // Posiciona o pivô na posição correta
    exch(v[l], v[j]);  

    return j;  // Retorna a posição do pivô
}
```

---

## 3. Funcionamento Passo a Passo

### 3.1 Exemplo com Array Pequeno (Pivô à Direita)

```cpp title="Exemplo: [3, 7, 8, 5, 2, 1, 9, 5, 4]"
Array inicial: [3, 7, 8, 5, 2, 1, 9, 5, 4]
Pivô: 4 (último elemento)

Passo 1: i encontra 7 (>4), j encontra 1 (<4) → Troca: [3, 1, 8, 5, 2, 7, 9, 5, 4]
Passo 2: i encontra 8 (>4), j encontra 2 (<4) → Troca: [3, 1, 2, 5, 8, 7, 9, 5, 4]
Passo 3: i encontra 5 (>4), j encontra 2 → i > j, para
Posiciona pivô: [3, 1, 2, 4, 8, 7, 9, 5, 5]

Recursão: 
Esquerda: [3, 1, 2] → ordena
Direita: [8, 7, 9, 5, 5] → ordena
```

### 3.2 Visualização do Particionamento


```cpp title="Implementação:"
Array: [3, 7, 8, 5, 2, 1, 9, 5, 4]
Pivô: 4

i avança: 3✓, 7✗ (para em 7)
j recua: 5✓, 9✓, 5✓, 1✗ (para em 1)
Troca 7↔1: [3, 1, 8, 5, 2, 7, 9, 5, 4]

i avança: 8✗ (para em 8)
j recua: 2✗ (para em 2)
Troca 8↔2: [3, 1, 2, 5, 8, 7, 9, 5, 4]

i avança: 5✗ (para em 5)
j recua: 5✓, 8✓ → j=2, i=3 → i>j, para
Troca pivô 4↔5: [3, 1, 2, 4, 8, 7, 9, 5, 5]
```

---

## 4. Análise do Algoritmo

### 4.1 Características
| Aspecto | Quick Sort |
|---------|------------|
| **Estabilidade** | Não |
| **Adaptabilidade** | Sim |
| **In-Place** | Sim |
| **Lista Encadeada** | Sim |

### 4.2 Complexidade
| Caso | Complexidade | Descrição |
|------|-------------|-----------|
| **Melhor caso** | O(n log n) | Pivô sempre divide ao meio |
| **Caso médio** | O(n log n) | Pivô escolhido aleatoriamente |
| **Pior caso** | O(n²) | Pivô sempre menor/maior elemento |
| **Complexidade de espaço** | O(log n) | Pilha de recursão |

### 4.3 Vantagens
- **Muito rápido na prática**: Constant factors menores;
- **Ordenação in-place**: Baixo uso de memória adicional;
- **Cache-friendly**: Bom uso da hierarquia de memória;
- **Paralelizável**: Pode ser implementado de forma paralela;
- **Adaptável**: Performance melhora com arrays parcialmente ordenados;

### 4.4 Desvantagens
- **Não estável**: Pode alterar ordem relativa de elementos iguais;
- **Pior caso O(n²)**: Performance degrada com pivôs ruins;
- **Dependente da escolha do pivô**: Performance varia com a estratégia;

### 4.5 Quando Escolher 
- **Para arrays grandes** na memória principal;
- **Quando velocidade é crítica**;
- **Para implementações gerais** de ordenação;
- **Quando memória é limitada**;

---

## 5. Estratégias de Escolha do Pivô

### 5.1 Mediana de Três (Otimização Comum)

```cpp title="Escolha do pivô por mediana de três:"
int median_of_three(int *v, int l, int r) {
    int m = (l + r) / 2;
    
    // Ordena v[l], v[m], v[r]
    if (v[l] > v[m]) exch(v[l], v[m]);
    if (v[l] > v[r]) exch(v[l], v[r]);
    if (v[m] > v[r]) exch(v[m], v[r]);
    
    // Coloca a mediana na posição r-1
    exch(v[m], v[r - 1]);
    return v[r - 1];
}

int partition_median(int *v, int l, int r) {
    int pivot = median_of_three(v, l, r);
    int i = l, j = r - 1;
    
    while (true) {
        while (v[++i] < pivot) ;
        while (v[--j] > pivot) ;
        if (i < j) {
            exch(v[i], v[j]);
        } else {
            break;
        }
    }
    exch(v[i], v[r - 1]);
    return i;
}
```

### 5.2 Outras Estratégias
- **Primeiro elemento**: Simples mas vulnerável;
- **Último elemento**: Similar ao primeiro;
- **Elemento central**: Melhor que extremos;
- **Aleatório**: Boa performance esperada;
- **Mediana de três**: Excelente performance prática;

