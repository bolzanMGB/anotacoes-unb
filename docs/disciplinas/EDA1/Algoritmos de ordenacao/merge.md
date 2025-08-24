# Merge Sort

---

## 1. Conceitos Gerais

O **Merge Sort** (Ordenação por Mistura) é um algoritmo de ordenação eficiente que segue a abordagem **"dividir para conquistar"**. Ele divide recursivamente o array em partes menores, ordena essas partes e depois as combina (merge) para produzir o array ordenado final.

**Princípio fundamental**: "Dividir, ordenar e combinar" - quebra o problema em subproblemas menores, resolve cada subproblema e combina as soluções.

---

## 2. Implementação do Merge Sort

### 2.1 Função Principal de Ordenação

```cpp title="Função principal do Merge Sort:"
void merge_sort(int *v, int l, int r) {
    if (l >= r) return; // Caso base: subarray de tamanho 0 ou 1
    
    int m = (r + l) / 2; // Ponto médio para divisão

    // Divisão recursiva
    merge_sort(v, l, m);     // Ordenar metade esquerda
    merge_sort(v, m + 1, r); // Ordenar metade direita
    
    // Combinação das partes ordenadas
    merge(v, l, m, r);      // Intercalar as duas metades
}
```

### 2.2 Função de Combinação (Merge)

```cpp title="Função de intercalação:"
void merge(int *v, int l, int m, int r) {
    int tam = r + 1 - l; // Tamanho do subarray
    int *aux = malloc(sizeof(int) * tam); // Vetor auxiliar

    int i = l;     // Índice do subvetor esquerdo
    int j = m + 1; // Índice do subvetor direito  
    int k = 0;     // Índice do vetor auxiliar

    // Intercalar enquanto ambos os subvetores têm elementos
    while (i <= m && j <= r) {
        if (v[i] <= v[j]) {
            aux[k++] = v[i++]; // Elemento da esquerda é menor
        } else {
            aux[k++] = v[j++]; // Elemento da direita é menor
        }
    }

    // Copiar elementos restantes do subvetor esquerdo
    while (i <= m) {
        aux[k++] = v[i++];
    }

    // Copiar elementos restantes do subvetor direito
    while (j <= r) {
        aux[k++] = v[j++];
    }

    // Copiar do vetor auxiliar de volta para o original
    for (k = 0, i = l; i <= r; i++, k++) {
        v[i] = aux[k];
    }

    free(aux); // Liberar memória alocada
}
```

---

## 3. Funcionamento Passo a Passo

### 3.1 Exemplo com Array Pequeno

```cpp title="Exemplo: [38, 27, 43, 3, 9, 82, 10]"
Divisão:
[38, 27, 43, 3, 9, 82, 10]
[38, 27, 43, 3] | [9, 82, 10]
[38, 27] | [43, 3] | [9, 82] | [10]
[38] | [27] | [43] | [3] | [9] | [82] | [10]

Combinação:
[27, 38] | [3, 43] | [9, 82] | [10]
[3, 27, 38, 43] | [9, 10, 82]
[3, 9, 10, 27, 38, 43, 82]
```

### 3.2 Visualização Gráfica

```cpp title="Exemplo:"
Array inicial: [38, 27, 43, 3, 9, 82, 10]

Divisão recursiva:
Nível 0: [38, 27, 43, 3, 9, 82, 10]
Nível 1: [38, 27, 43, 3] | [9, 82, 10]
Nível 2: [38, 27] | [43, 3] | [9, 82] | [10]
Nível 3: [38] | [27] | [43] | [3] | [9] | [82] | [10]

Combinação recursiva:
[27, 38] | [3, 43] | [9, 82] | [10]
[3, 27, 38, 43] | [9, 10, 82]
[3, 9, 10, 27, 38, 43, 82]
```

---

## 4. Análise do Algoritmo

### 4.1 Características
| Aspecto | Quick Sort |
|---------|------------|
| **Estabilidade** | Não |
| **Adaptabilidade** | Sim |
| **In-Place** | Não |
| **Lista Encadeada** | Sim |

### 4.2 Complexidade
| Caso | Complexidade | Descrição |
|------|-------------|-----------|
| **Melhor caso** | O(n log n) | Sempre divide ao meio |
| **Caso médio** | O(n log n) | Ordem aleatória |
| **Pior caso** | O(n log n) | Ordem inversa ou qualquer |
| **Complexidade de espaço** | O(n) | Vetor auxiliar |

### 4.3 Vantagens
- **Complexidade garantida**: Sempre O(n log n);
- **Estável**: Mantém ordem relativa de elementos iguais;
- **Previsível**: Performance consistente;
- **Bom para dados externos**: Funciona bem com arquivos grandes;
- **Paralelizável**: Fácil de implementar de forma paralela;

### 4.4 Desvantagens
- **Uso de memória**: Requer O(n) de espaço adicional;
- **Não in-place**: Precisa de vetor auxiliar;
- **Overhead de recursão**: Chamadas recursivas podem ser custosas;
- **Slower constant factors**: Mais lento que Quick Sort na prática;

### 4.5 Quando Escolher 
- **Quando estabilidade é importante**;
- **Para ordenar listas encadeadas**;
- **Quando performance consistente é necessária**;
- **Para dados externos ou arquivos grandes**;
- **Em implementações paralelas**;

