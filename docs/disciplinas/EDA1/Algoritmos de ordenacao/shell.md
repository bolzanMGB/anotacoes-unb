# Shell Sort

---

## 1. Conceitos Gerais

O **Shell Sort** é um algoritmo de ordenação que generaliza o Insertion Sort, permitindo a troca de elementos que estão distantes uns dos outros. Desenvolvido por Donald Shell em 1959, é uma melhoria significativa sobre algoritmos de ordenação simples.

**Princípio fundamental**: "Ordenação por incrementos decrescentes" - o algoritmo realiza várias passadas pelo array com intervalos (gaps) cada vez menores, até que o intervalo seja 1 (equivalente ao Insertion Sort).

---

## 2. Implementação do Shell Sort

```cpp title="Implementação:"
void shell_sort(int v[], int l, int r) {
    int h = 1; // h - distância (gap)

    // Calcular o maior gap possível usando a sequência 3x+1
    while (h < (r - l + 1) / 3) {
        h = 3 * h + 1;
    }

    // Reduzir gradualmente o gap até 1
    while (h >= 1) {
        // Aplicar insertion sort para cada subarray com gap h
        for (int i = l + h; i <= r; i++) {
            // Ordenar por inserção com gap h
            for (int j = i; j >= l + h && v[j] < v[j - h]; j -= h) {
                exch(v[j], v[j - h]);
            }
        }
        h = h / 3; // Reduzir o gap
    }
}
```

---

## 3. Funcionamento Passo a Passo

### 3.1 Exemplo com Array Pequeno

```cpp title="Exemplo:"
Array inicial: [64, 34, 25, 12, 22, 11, 90, 8]

Passo 1: Calcular h máximo
- h inicial: 1
- h = 4 (sequência: 1, 4, 13... mas 13 > 8/3, então h=4)

Passo 2: h = 4
Subarrays com gap 4: 
- [64, 22, 90] → ordenado: [22, 64, 90]
- [34, 11, 8] → ordenado: [8, 11, 34]  
- [25, 12] → ordenado: [12, 25]
Array após h=4: [22, 8, 12, 11, 64, 34, 90, 25]

Passo 3: h = 1
Aplicar insertion sort normal:
Array final ordenado: [8, 11, 12, 22, 25, 34, 64, 90]
```

### 3.2 Visualização Gráfica

```cpp title="Implementação:"
Array inicial: [64, 34, 25, 12, 22, 11, 90, 8]

h=4: 
- Subarray 1: [64, 22, 90] → [22, 64, 90]
- Subarray 2: [34, 11, 8] → [8, 11, 34]
- Subarray 3: [25, 12] → [12, 25]
Resultado: [22, 8, 12, 11, 64, 34, 90, 25]

h=1: Insertion Sort completo
Resultado final: [8, 11, 12, 22, 25, 34, 64, 90]
```

---

## 4. Análise do Algoritmo

### 4.1 Características
| Aspecto | Quick Sort |
|---------|------------|
| **Estabilidade** | Sim |
| **Adaptabilidade** | Não |
| **In-Place** | Sim |
| **Lista Encadeada** | Não |

### 4.2 Complexidade
| Caso | Complexidade | Descrição |
|------|-------------|-----------|
| **Melhor caso** | O(n log n) | Sempre divide ao meio |
| **Caso médio** | O(n^3/2) | Ordem aleatória |
| **Pior caso** | O(n²) | Ordem inversa ou qualquer |
| **Complexidade de espaço** | O(n) | Vetor auxiliar |

### 4.3 Vantagens
- **Melhoria significativa** sobre Insertion Sort para arrays grandes;
- **Eficiente para arrays médios** (n ≈ 1000-10000);
- **Ordenação in-place**: Baixo uso de memória adicional;
- **Fácil de implementar**;
- **Bom desempenho prático** apesar da complexidade teórica;

### 4.4 Desvantagens
- **Complexidade difícil de analisar** matematicamente;
- **Não estável**: Pode alterar ordem relativa de elementos iguais;
- **Performance varia** com a sequência de gaps escolhida;
- **Não é ótimo**: Existem algoritmos O(n log n) mais eficientes;

### 4.5 Quando Escolher 
- **Arrays de tamanho médio** (100-10000 elementos);
- **Quando memória é limitada**;
- **Implementações educacionais**;
- **Como pré-processamento** para outros algoritmos;

