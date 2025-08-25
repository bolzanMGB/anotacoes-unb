# Heap Sort

---

## 1. Conceitos Gerais

O **Heap Sort** (Ordenação por Heap) é um algoritmo de ordenação baseado na estrutura de dados **heap**. Desenvolvido por J. W. J. Williams em 1964, é um algoritmo eficiente que combina as vantagens da ordenação por seleção com a eficiência do heap.

**Princípio fundamental**: "Transformar o array em um heap máximo, extrair repetidamente o maior elemento e reconstruir o heap" - converte o array em um heap máximo, extrai o elemento raiz (maior) e reconstrói o heap com os elementos restantes.

---

## 2. Implementação do Heap Sort

### 2.1 Função Principal de Ordenação

```cpp title="Função principal do Heap Sort:"
// Definição do tipo Item
typedef int Item;

// Função para trocar dois elementos
void exch(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

// Função para restaurar a propriedade de heap (max-heap)
void fixDown(Item *pq, int k, int N) {
    while (2 * k <= N) {
        int j = 2 * k; // Filho esquerdo
        if (j < N && pq[j] < pq[j + 1]) j++; // Escolhe o maior filho
        if (pq[k] >= pq[j]) break; // Se o pai é maior que o filho, para
        exch(&pq[k], &pq[j]); // Troca pai e filho
        k = j; // Continua no filho
    }
}

// Função principal do Heap Sort
void heap_sort(Item *v, int l, int r) {
    Item *pq = v + l - 1; // Ajusta o ponteiro para o heap
    int N = r - l + 1;    // Tamanho do heap

    // Constrói o heap (max-heap) - Fase 1
    for (int k = N / 2; k >= 1; k--) {
        fixDown(pq, k, N);
    }

    // Ordena o array - Fase 2
    while (N > 1) {
        exch(&pq[1], &pq[N]); // Troca o maior elemento (raiz) com o último
        fixDown(pq, 1, --N);  // Restaura a propriedade de heap
    }
}
```

### 2.2 Passos do Algoritmo

**Fase 1 - Construção do Heap Máximo:**
- Transformar a lista original em um heap máximo;
- Começa pela metade do array (último nó não-folha);
- Aplica `fixDown` em cada nó até chegar na raiz;

**Fase 2 - Ordenação:**
- Trocar a raiz (maior elemento) pelo último elemento;
- Remove a raiz do heap (diminui o tamanho);
- Aplica `fixDown` na nova raiz para restaurar a propriedade de heap;
- Repete o processo até que o heap tenha apenas um elemento;

---

## 3. Funcionamento Passo a Passo

### 3.1 Exemplo com Array Pequeno

```cpp title="Exemplo: [3, 7, 8, 5, 2, 1, 9, 5, 4]"
Array inicial: [3, 7, 8, 5, 2, 1, 9, 5, 4]

Fase 1 - Construção do Heap Máximo:
Heap construído: [9, 7, 8, 5, 4, 1, 3, 5, 2]

Fase 2 - Ordenação:
Passo 1: Troca 9↔2 → [2, 7, 8, 5, 4, 1, 3, 5, 9]
         fixDown: [8, 7, 3, 5, 4, 1, 2, 5, 9]

Passo 2: Troca 8↔5 → [5, 7, 3, 5, 4, 1, 2, 8, 9]
         fixDown: [7, 5, 3, 5, 4, 1, 2, 8, 9]

Passo 3: Troca 7↔2 → [2, 5, 3, 5, 4, 1, 7, 8, 9]
         fixDown: [5, 5, 3, 2, 4, 1, 7, 8, 9]

Continua até array ordenado: [1, 2, 3, 4, 5, 5, 7, 8, 9]
```

### 3.2 Visualização da Construção do Heap

```cpp title="Construção do heap máximo:"
Array original: [3, 7, 8, 5, 2, 1, 9, 5, 4]

Construção a partir do meio (k = 4):
- k=4: [3, 7, 8, 5, 2, 1, 9, 5, 4] ✓
- k=3: [3, 7, 8, 5, 2, 1, 9, 5, 4] → [3, 7, 9, 5, 2, 1, 8, 5, 4]
- k=2: [3, 7, 9, 5, 2, 1, 8, 5, 4] → [3, 5, 9, 7, 2, 1, 8, 5, 4]
- k=1: [3, 5, 9, 7, 2, 1, 8, 5, 4] → [9, 5, 8, 7, 2, 1, 3, 5, 4]

Heap máximo final: [9, 7, 8, 5, 4, 1, 3, 5, 2]
```

---

## 4. Análise do Algoritmo

### 4.1 Características
| Aspecto | Heap Sort |
|---------|-----------|
| **Estabilidade** | Não |
| **Adaptabilidade** | Não |
| **In-Place** | Sim |
| **Lista Encadeada** | Não |

### 4.2 Complexidade
| Caso | Complexidade | Descrição |
|------|-------------|-----------|
| **Melhor caso** | O(n log n) | Construção do heap + extrações |
| **Caso médio** | O(n log n) | Construção do heap + extrações |
| **Pior caso** | O(n log n) | Garantido em todos os casos |
| **Complexidade de espaço** | O(1) | Ordenação in-place |

### 4.3 Vantagens
- **Complexidade garantida O(n log n)**: Nunca degrada para O(n²);
- **Ordenação in-place**: Baixo uso de memória adicional (O(1));
- **Não recursivo**: Não usa pilha de chamadas;
- **Estável no pior caso**: Performance consistente;

### 4.4 Desvantagens
- **Não estável**: Pode alterar ordem relativa de elementos iguais;
- **Não adaptável**: Performance não melhora com arrays parcialmente ordenados;
- **Cache-unfriendly**: Acesso à memória não sequencial;
- **Constantes altas**: Na prática, mais lento que Quick Sort e Merge Sort;

### 4.5 Quando Escolher 
- **Quando garantia de O(n log n) é crítica**;
- **Em sistemas com memória limitada**;
- **Para implementações onde recursão é problemática**;
- **Em aplicações de tempo real** onde o pior caso importa;

---

## 5. Aplicações Especiais
- **Sistemas embarcados**: Por ser in-place e não recursivo;
- **K-way merge**: Utilizado em algoritmos de merge externo;
- **Seleção de k-ésimo elemento**: Adaptável para encontrar o k-ésimo maior/menor elemento;
- **Filas de prioridade**: Base para implementação eficiente de filas de prioridade;