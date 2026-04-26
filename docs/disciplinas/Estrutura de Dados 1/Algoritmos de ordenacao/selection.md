# Selection Sort

---

## 1. Conceitos Gerais

O **Selection Sort** (Ordenação por Seleção) é um algoritmo de ordenação simples que funciona selecionando repetidamente o menor (ou maior) elemento da parte não ordenada do array e movendo-o para a posição correta.

**Princípio fundamental**: "Selecionar e posicionar" - a cada iteração, encontra-se o menor elemento restante e coloca-o na posição correta.

---

## 2. Implementação do Selection Sort

```c title="Implementação:"
void selection_sort(int v[], int l, int r) {
    int menor;
    
    for (int i = l; i < r; i++) {         // Loop externo: O(n)
        menor = i;                         // Assume que o atual é o menor
        
        // Encontra o menor elemento na parte não ordenada
        for (int j = i + 1; j <= r; j++) { // Loop interno: O(n)
            if (v[j] < v[menor]) {         // Comparação
                menor = j;                 // Atualiza o índice do menor
            }
        }
        
        // Troca o menor elemento com o elemento na posição i
        if (i != menor) {
            int temp = v[i];               // Troca: O(1)
            v[i] = v[menor];
            v[menor] = temp;
        }
    }
}
```

---

## 3. Funcionamento Passo a Passo

### 3.1 Exemplo com Array Pequeno

```c title="Exemplo:"
Array inicial: [64, 25, 12, 22, 11]

Passo 1 (i=0):
- Encontrar menor: 11 (índice 4)
- Trocar v[0] (64) com v[4] (11)
- Array: [11, 25, 12, 22, 64]

Passo 2 (i=1):
- Encontrar menor: 12 (índice 2)  
- Trocar v[1] (25) com v[2] (12)
- Array: [11, 12, 25, 22, 64]

Passo 3 (i=2):
- Encontrar menor: 22 (índice 3)
- Trocar v[2] (25) com v[3] (22)
- Array: [11, 12, 22, 25, 64]

Passo 4 (i=3):
- Encontrar menor: 25 (índice 3)
- Sem troca necessária
- Array final ordenado: [11, 12, 22, 25, 64]
```

### 3.2 Visualização Gráfica

```c title="Implementação:"
Array inicial: [64, 25, 12, 22, 11]

Iteração 0: [64, 25, 12, 22, 11] → Menor: 11 → Troca: [11, 25, 12, 22, 64]
Iteração 1: [11, 25, 12, 22, 64] → Menor: 12 → Troca: [11, 12, 25, 22, 64]  
Iteração 2: [11, 12, 25, 22, 64] → Menor: 22 → Troca: [11, 12, 22, 25, 64]
Iteração 3: [11, 12, 22, 25, 64] → Menor: 25 → Sem troca

Array ordenado: [11, 12, 22, 25, 64]
```

---

## 4. Análise do Algoritmo

### 4.1 Características
### 4.1 Características
| Aspecto | Quick Sort |
|---------|------------|
| **Estabilidade** | Não |
| **Adaptabilidade** | Não |
| **In-Place** | Sim |
| **Lista Encadeada** | Não |

### 4.2 Complexidade
| Caso | Complexidade | Descrição |
|------|-------------|-----------|
| **Melhor caso** | O(n²) | Array já ordenado |
| **Caso médio** | O(n²) | Array em ordem aleatória |
| **Pior caso** | O(n²) | Array em ordem inversa |

### 4.3 Vantagens
- **Simplicidade**: Fácil de implementar e entender;
- **Baixo overhead**: Pouca memória adicional necessária;
- **Poucas trocas**: Apenas n-1 trocas no máximo;
- **Útil para** arrays pequenos ou quase ordenados;

### 4.4 Desvantagens
- **Complexidade quadrática**: Ineficiente para arrays grandes;
- **Não adaptativo**: Performance não melhora com arrays parcialmente ordenados;
- **Não estável**: Não mantém ordem relativa de elementos iguais;
- **Pouco eficiente**: Comparado a algoritmos O(n log n);

### 4.5 Quando Escolher 
- **Arrays muito pequenos** (n < 20)
- **Memória extremamente limitada** 
- **Implementação educacional**
- **Quando trocas são custosas** (em termos de hardware)

