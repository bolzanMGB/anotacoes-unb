# Insertion Sort

---

## 1. Conceitos Gerais

O **Insertion Sort** (Ordenação por Inserção) é um algoritmo de ordenação simples que funciona construindo uma sequência ordenada um elemento de cada vez. Ele é eficiente para conjuntos de dados pequenos ou parcialmente ordenados.

**Princípio fundamental**: "Inserir ordenadamente" - cada elemento é inserido na posição correta dentro da parte já ordenada do array.

---

## 2. Implementações do Insertion Sort

### 2.1 Versão com Troca Direta

```cpp title="Implementação com trocas:"
void insertion_sort(int v[], int l, int r) {
    // Percorrer o array a partir do segundo elemento
    for (int i = l + 1; i <= r; i++) {
        // Procurar antecessores menores que v[i]
        for (int j = i; j > l && v[j] < v[j - 1]; j--) {
            // Inserir na posição correta através de trocas
            exch(v[j], v[j - 1]);
        }
    }
}
```

### 2.2 Versão Otimizada com Deslocamento

```cpp title="Implementação otimizada:"
void insertion_sort(int v[], int l, int r) {
    int elem, i, j;

    // Percorrer o array a partir do segundo elemento
    for (i = l + 1; i <= r; i++) {
        // Elemento que será (re) inserido
        elem = v[i];

        // Para cada elemento maior que 'elem'
        for (j = i; j > l && elem < v[j - 1]; j--) {
            // "Puxar" o maior elemento para a direita
            v[j] = v[j - 1];
        }

        // Inserir o elemento na sua posição correta
        v[j] = elem;
    }
}
```

---

## 3. Funcionamento Passo a Passo

### 3.1 Exemplo com Array Pequeno (Versão Otimizada)

```cpp title="Exemplo:"
Array inicial: [12, 11, 13, 5, 6]

Passo 1 (i=1, elem=11):
- j=1: 11 < 12? Sim → v[1] = v[0] → [12, 12, 13, 5, 6]
- j=0: j > 0? Não → v[0] = 11 → [11, 12, 13, 5, 6]

Passo 2 (i=2, elem=13):
- j=2: 13 < 12? Não → v[2] = 13 → [11, 12, 13, 5, 6]

Passo 3 (i=3, elem=5):
- j=3: 5 < 13? Sim → v[3] = v[2] → [11, 12, 13, 13, 6]
- j=2: 5 < 12? Sim → v[2] = v[1] → [11, 12, 12, 13, 6]  
- j=1: 5 < 11? Sim → v[1] = v[0] → [11, 11, 12, 13, 6]
- j=0: j > 0? Não → v[0] = 5 → [5, 11, 12, 13, 6]

Passo 4 (i=4, elem=6):
- j=4: 6 < 13? Sim → v[4] = v[3] → [5, 11, 12, 13, 13]
- j=3: 6 < 12? Sim → v[3] = v[2] → [5, 11, 12, 12, 13]
- j=2: 6 < 11? Sim → v[2] = v[1] → [5, 11, 11, 12, 13]
- j=1: 6 < 5? Não → v[1] = 6 → [5, 6, 11, 12, 13]

Array final ordenado: [5, 6, 11, 12, 13]
```

### 3.2 Visualização Gráfica

```cpp title="Implementação:"
Array inicial: [12, 11, 13, 5, 6]

Iteração 1: [11, 12, 13, 5, 6] (inseriu 11)
Iteração 2: [11, 12, 13, 5, 6] (manteve 13)  
Iteração 3: [5, 11, 12, 13, 6] (inseriu 5)
Iteração 4: [5, 6, 11, 12, 13] (inseriu 6)

Array ordenado: [5, 6, 11, 12, 13]
```

---

## 4. Análise do Algoritmo

### 4.1 Características
### 4.1 Características
| Aspecto | Quick Sort |
|---------|------------|
| **Estabilidade** | Sim |
| **Adaptabilidade** | Sim |
| **In-Place** | SIm |
| **Lista Encadeada** | Sim |

### 4.2 Complexidade
| Caso | Complexidade | Descrição |
|------|-------------|-----------|
| **Melhor caso** | O(n) | Array já ordenado |
| **Caso médio** | O(n²) | Array em ordem aleatória |
| **Pior caso** | O(n²) | Array em ordem inversa |

### 4.3 Vantagens
- **Simplicidade**: Fácil de implementar e entender;
- **Adaptabilidade**: Performance excelente em arrays quase ordenados;
- **Estabilidade**: Mantém a ordem relativa de elementos iguais;
- **Eficiente em pequenos arrays**: Melhor que algoritmos O(n log n) para n < 10-20;
- **Ordenação in-place**: Baixo uso de memória adicional;
- **Online**: Pode ordenar dados à medida que são recebidos;

### 4.4 Desvantagens
- **Complexidade quadrática**: Ineficiente para arrays grandes;
- **Muitas comparações/deslocamentos**: Pode ser custoso;
- **Não escalável**: Performance decai rapidamente com o aumento de n;

### 4.5 Quando Escolher 
- **Arrays pequenos** (n < 20)
- **Arrays quase ordenados** 
- **Implementação educacional**
- **Quando a estabilidade é importante**
- **Ordenação online** de dados recebidos sequencialmente
- **Como parte de algoritmos híbridos** como Timsort

### 4.6 Comparação das Versões

| Característica | Versão com Trocas | Versão Otimizada |
|----------------|-------------------|------------------|
| **Número de operações** | Mais trocas | Menos atribuições |
| **Complexidade** | O(n²) | O(n²) |
| **Eficiência** | Menos eficiente | Mais eficiente |
| **Uso de memória** | O(1) | O(1) |

A versão otimizada é geralmente preferida pois reduz o número de operações de escrita na memória, movendo elementos apenas uma vez em vez de fazer múltiplas trocas.

