# Bubble Sort

---

## 1. Conceitos Gerais

O **Bubble Sort** (Ordenação por Bolha) é um algoritmo de ordenação simples que funciona repetidamente percorrendo o array, comparando elementos adjacentes e trocando-os se estiverem na ordem errada.

**Princípio fundamental**: "Flutuação" - os elementos maiores "borbulham" para o final do array a cada passagem completa.

---

## 2. Implementação do Bubble Sort

```cpp title="Implementação:"
void bubble_sort(int v[], int l, int r) {
    int swap = 1;
    
    while (r > l && swap) {          // Loop externo: O(n)
        swap = 0;
        
        // Percorre o array comparando elementos adjacentes
        for (int j = l; j < r; j++) { // Loop interno: O(n)
            if (v[j] > v[j + 1]) {    // Comparação
                // Troca os elementos se estiverem na ordem errada
                exch(v[j], v[j + 1]); // Troca: O(1)
                swap = 1;
            }
        }
        r--;  // Reduz o limite, pois o último elemento já está na posição correta
    }
}
```

---

## 3. Funcionamento Passo a Passo

### 3.1 Exemplo com Array Pequeno

```cpp title="Exemplo:"
Array inicial: [64, 34, 25, 12, 22, 11, 90]

Primeira passagem (r=6):
- [34, 64, 25, 12, 22, 11, 90] (troca 64-34)
- [34, 25, 64, 12, 22, 11, 90] (troca 64-25)
- [34, 25, 12, 64, 22, 11, 90] (troca 64-12)
- [34, 25, 12, 22, 64, 11, 90] (troca 64-22)
- [34, 25, 12, 22, 11, 64, 90] (troca 64-11)
- [34, 25, 12, 22, 11, 64, 90] (sem troca 64-90)
- Array após 1ª passagem: [34, 25, 12, 22, 11, 64, 90]

Segunda passagem (r=5):
- [25, 34, 12, 22, 11, 64, 90] (troca 34-25)
- [25, 12, 34, 22, 11, 64, 90] (troca 34-12)
- [25, 12, 22, 34, 11, 64, 90] (troca 34-22)
- [25, 12, 22, 11, 34, 64, 90] (troca 34-11)
- Array após 2ª passagem: [25, 12, 22, 11, 34, 64, 90]

Terceira passagem (r=4):
- [12, 25, 22, 11, 34, 64, 90] (troca 25-12)
- [12, 22, 25, 11, 34, 64, 90] (troca 25-22)
- [12, 22, 11, 25, 34, 64, 90] (troca 25-11)
- Array após 3ª passagem: [12, 22, 11, 25, 34, 64, 90]

Quarta passagem (r=3):
- [12, 22, 11, 25, 34, 64, 90] (sem troca 12-22)
- [12, 11, 22, 25, 34, 64, 90] (troca 22-11)
- Array após 4ª passagem: [12, 11, 22, 25, 34, 64, 90]

Quinta passagem (r=2):
- [11, 12, 22, 25, 34, 64, 90] (troca 12-11)
- Array final ordenado: [11, 12, 22, 25, 34, 64, 90]
```

### 3.2 Visualização Gráfica

```cpp title="Implementação:"
Array inicial: [64, 34, 25, 12, 22, 11, 90]

Passagem 1: [34, 25, 12, 22, 11, 64, 90] (5 trocas)
Passagem 2: [25, 12, 22, 11, 34, 64, 90] (4 trocas)  
Passagem 3: [12, 22, 11, 25, 34, 64, 90] (3 trocas)
Passagem 4: [12, 11, 22, 25, 34, 64, 90] (1 troca)
Passagem 5: [11, 12, 22, 25, 34, 64, 90] (1 troca)

Array ordenado: [11, 12, 22, 25, 34, 64, 90]
```

---

## 4. Análise do Algoritmo

### 4.1 Características
### 4.1 Características
| Aspecto | Quick Sort |
|---------|------------|
| **Estabilidade** | Sim |
| **Adaptabilidade** | Sim |
| **In-Place** | Sim |
| **Lista Encadeada** | Não |

### 4.2 Complexidade
| Caso | Complexidade | Descrição |
|------|-------------|-----------|
| **Melhor caso** | O(n) | Array já ordenado (versão otimizada) |
| **Caso médio** | O(n²) | Array em ordem aleatória |
| **Pior caso** | O(n²) | Array em ordem inversa |

### 4.3 Vantagens
- **Simplicidade**: Fácil de implementar e entender;
- **Adaptabilidade**: Versão otimizada detecta arrays já ordenados;
- **Estabilidade**: Mantém a ordem relativa de elementos iguais;
- **Baixo overhead**: Pouca memória adicional necessária;
- **Útil para** arrays pequenos ou quase ordenados;

### 4.4 Desvantagens
- **Complexidade quadrática**: Ineficiente para arrays grandes;
- **Muitas trocas**: Pode realizar até O(n²) trocas;
- **Pouco eficiente**: Comparado a algoritmos O(n log n);
- **Performance ruim**: Em arrays grandes ou desordenados;

### 4.5 Quando Escolher 
- **Arrays muito pequenos** (n < 20)
- **Arrays quase ordenados** (poucas trocas necessárias)
- **Implementação educacional**
- **Quando a estabilidade é importante**
- **Memória extremamente limitada**


