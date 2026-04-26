# Intro Sort

---

## 1. Conceitos Gerais

O **IntroSort** (Introsort ou Introspective Sort) é um algoritmo de ordenação híbrido que combina as melhores características do QuickSort, HeapSort e InsertionSort. Desenvolvido por David Musser em 1997, oferece excelente performance na prática com garantia de complexidade O(n log n) no pior caso.

**Princípio fundamental**: "Combinar eficiências e evitar deficiências" - utiliza QuickSort para eficiência média, HeapSort para garantir complexidade ótima, e InsertionSort para pequenos subarrays.

---

## 2. Implementação do IntroSort

### 2.1 Função Principal de Ordenação

```cpp title="Função principal do IntroSort:"
#include <cmath>
#include <algorithm>

// Função auxiliar para trocar elementos
void exch(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Função auxiliar para comparação e troca
void compexch(int &a, int &b) {
    if (b < a) exch(a, b);
}

// Insertion Sort para pequenos arrays
void insertion_sort(int *v, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        int key = v[i];
        int j = i - 1;
        while (j >= l && v[j] > key) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

// Partition do QuickSort (versão Lomuto)
int partition(int *v, int l, int r) {
    int pivot = v[r];
    int i = l - 1;
    
    for (int j = l; j < r; j++) {
        if (v[j] <= pivot) {
            i++;
            exch(v[i], v[j]);
        }
    }
    exch(v[i + 1], v[r]);
    return i + 1;
}

// Função recursiva principal
void intro(int *v, int l, int r, int maxdepth) {
    // Caso base: array pequeno → InsertionSort
    if (r - l <= 15) {
        insertion_sort(v, l, r);
        return;
    }
    // Profundidade máxima atingida → HeapSort
    else if (maxdepth == 0) {
        std::make_heap(v + l, v + r + 1);
        std::sort_heap(v + l, v + r + 1);
        return;
    }
    // QuickSort com otimizações
    else {
        // Mediana de três para escolha do pivô
        compexch(v[l], v[(l + r) / 2]);
        compexch(v[l], v[r]);
        compexch(v[r], v[(l + r) / 2]);
        
        int p = partition(v, l, r);
        intro(v, l, p - 1, maxdepth - 1);
        intro(v, p + 1, r, maxdepth - 1);
    }
}

// Função wrapper principal
void intro_sort(int *v, int l, int r) {
    if (r <= l) return;
    
    // Calcula profundidade máxima (2 * log2(n))
    int n = r - l + 1;
    int maxdepth = 2 * static_cast<int>(std::log2(n));
    
    intro(v, l, r, maxdepth);
}
```

### 2.2 Passos do Algoritmo

**Fase 1 - QuickSort:**
- Divide o array recursivamente usando partição;
- Usa mediana de três para escolha otimizada do pivô;
- Continua enquanto a profundidade de recursão estiver dentro do limite;

**Fase 2 - HeapSort:**
- Se a profundidade de recursão exceder 2 * log₂(n);
- Garante complexidade O(n log n) no pior caso;

**Fase 3 - InsertionSort:**
- Quando os subarrays ficam pequenos (≤ 15 elementos);
- Refina a ordenação final com algoritmo adaptativo;

---

## 3. Funcionamento Passo a Passo

### 3.1 Exemplo com Array

```cpp title="Exemplo: Array de 20 elementos"
Array inicial: [5, 2, 8, 3, 9, 1, 6, 4, 7, 0, ...]

Passo 1: QuickSort com mediana de três
- Escolhe pivô otimizado (mediana de primeiro, meio, último)
- Particiona o array
- Continua recursivamente

Passo 2: Monitoramento de profundidade
- Profundidade atual: 0, 1, 2, ... 
- Se profundidade > 2 * log₂(20) ≈ 8.6 → muda para HeapSort

Passo 3: Para subarrays pequenos
- Quando tamanho ≤ 15 → aplica InsertionSort
- Exemplo: subarray [2, 3, 1, 0, 4] → ordena com InsertionSort

Resultado final: Array completamente ordenado
```

### 3.2 Estratégia de Transição

```cpp title="Lógica de transição entre algoritmos:"
Tamanho do subarray → Algoritmo usado
-------------------------------------
n ≤ 15           → Insertion Sort
15 < n ≤ limite  → Quick Sort
n > limite       → Heap Sort

Limite = 2 * log2(n) (profundidade máxima)
```

---

## 4. Análise do Algoritmo

### 4.1 Características
| Aspecto | IntroSort |
|---------|-----------|
| **Estabilidade** | Não |
| **Adaptabilidade** | Parcialmente |
| **In-Place** | Sim |
| **Híbrido** | Sim |

### 4.2 Complexidade
| Caso | Complexidade | Descrição |
|------|-------------|-----------|
| **Melhor caso** | O(n log n) | QuickSort com pivô ideal |
| **Caso médio** | O(n log n) | Performance prática excelente |
| **Pior caso** | O(n log n) | Garantido pelo HeapSort |
| **Complexidade de espaço** | O(log n) | Pilha de recursão |

### 4.3 Vantagens
- **Performance prática do QuickSort**: Eficiente na maioria dos casos;
- **Garantia O(n log n)**: HeapSort evita o pior caso do QuickSort;
- **Eficiência para pequenos arrays**: InsertionSort para refinamento;
- **Otimizado com mediana de três**: Escolha inteligente de pivô;
- **Padrão da indústria**: Usado em std::sort de C++ STL;

### 4.4 Desvantagens
- **Não estável**: Pode alterar ordem relativa de elementos iguais;
- **Implementação complexa**: Combina três algoritmos diferentes;
- **Overhead de monitoramento**: Controle de profundidade adiciona complexidade;

### 4.5 Quando Escolher 
- **Para ordenação geral de propósito geral**;
- **Quando garantia de O(n log n) é necessária**;
- **Em bibliotecas e frameworks** onde robustez é importante;
- **Para dados mistos** com características variadas;

---


## 5. Aplicações Especiais
- **std::sort na C++ STL**: Implementação padrão de muitas bibliotecas;
- **Sistemas de alto desempenho**: Onde robustez e performance são críticas;
- **Aplicações científicas**: Processamento de dados com tamanhos variados;
- **Frameworks de machine learning**: Pré-processamento de datasets;