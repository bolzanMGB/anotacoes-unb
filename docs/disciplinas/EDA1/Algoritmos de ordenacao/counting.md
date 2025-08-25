# Counting Sort

---

## 1. Conceitos Gerais

O **Counting Sort** (Ordenação por Contagem) é um algoritmo de ordenação **não comparativo** que funciona contando as ocorrências de cada elemento distinto no array de entrada. É particularmente eficiente para ordenar números inteiros em um intervalo conhecido e limitado.

**Princípio fundamental**: "Contar, acumular e distribuir" - conta as frequências de cada chave, calcula as posições finais através das frequências acumuladas, e distribui os elementos nas posições corretas.

---

## 2. Implementação do Counting Sort

### 2.1 Função Principal de Ordenação

```cpp title="Função principal do Counting Sort:"
#define MAX 10000
#define R 5

int aux[MAX];

void countingsort(int *v, int l, int r) {
    int i, count[R + 1];

    // Inicializa o array de contagem com zeros
    for (i = 0; i <= R; i++) count[i] = 0;

    // Fase 1: Contar as frequências de cada elemento
    for (i = l; i <= r; i++) count[v[i] + 1]++;

    // Fase 2: Calcular as posições finais (frequências acumuladas)
    for (i = 1; i <= R; i++) count[i] += count[i - 1];

    // Fase 3: Distribuir os elementos nas posições corretas
    for (i = l; i <= r; i++) aux[count[v[i]]++] = v[i];

    // Copiar o array ordenado de volta para o original
    for (i = l; i <= r; i++) v[i] = aux[i - l];
}
```

### 2.2 Passos do Algoritmo

**Fase 1 - Contagem de Frequências:**
- Encontrar o intervalo de valores (min e max);
- Criar um array de contagem com tamanho (max - min + 1);
- Contar quantas vezes cada elemento aparece no array original;

**Fase 2 - Cálculo de Posições:**
- Transformar as frequências em posições acumuladas;
- Cada elemento indica a posição onde o próximo elemento daquela chave deve ser colocado;

**Fase 3 - Distribuição:**
- Percorrer o array original e colocar cada elemento na posição correta do array auxiliar;
- Atualizar o contador de posições para cada chave;

---

## 3. Funcionamento Passo a Passo

### 3.1 Exemplo com Array Pequeno

```cpp title="Exemplo: v[5] = [2, 3, 3, 4, 1]"
Array inicial: [2, 3, 3, 4, 1]
Intervalo de valores: 1 a 4 (R = 4)

Fase 1 - Contagem de frequências:
count[0] = 0  // valor 0
count[1] = 1  // valor 1
count[2] = 1  // valor 2
count[3] = 2  // valor 3
count[4] = 1  // valor 4

Fase 2 - Cálculo de posições (acumulado):
count[0] = 0
count[1] = 0 + 1 = 1
count[2] = 1 + 1 = 2
count[3] = 2 + 2 = 4
count[4] = 4 + 1 = 5

Fase 3 - Distribuição:
Elemento 1: posição count[1] = 0 → aux[0] = 1
Elemento 2: posição count[2] = 1 → aux[1] = 2
Elemento 3: posição count[3] = 2 → aux[2] = 3
Elemento 3: posição count[3] = 3 → aux[3] = 3
Elemento 4: posição count[4] = 4 → aux[4] = 4

Array ordenado: [1, 2, 3, 3, 4]
```

### 3.2 Visualização das Fases

```cpp title="Processo detalhado:"
Array original: [2, 3, 3, 4, 1]

Fase 1 - Contagem:
Valor 1: aparece 1 vez → count[1] = 1
Valor 2: aparece 1 vez → count[2] = 1  
Valor 3: aparece 2 vezes → count[3] = 2
Valor 4: aparece 1 vez → count[4] = 1

Fase 2 - Acumulação:
count[1] = 1 (0 + 1)
count[2] = 2 (1 + 1)
count[3] = 4 (2 + 2)
count[4] = 5 (4 + 1)

Fase 3 - Distribuição:
Processa elemento 2: count[2] = 2 → aux[1] = 2, count[2] = 3
Processa elemento 3: count[3] = 4 → aux[3] = 3, count[3] = 5
Processa elemento 3: count[3] = 5 → aux[4] = 3, count[3] = 6
Processa elemento 4: count[4] = 5 → aux[4] = 4, count[4] = 6
Processa elemento 1: count[1] = 1 → aux[0] = 1, count[1] = 2

Resultado: aux = [1, 2, 3, 3, 4]
```

---

## 4. Análise do Algoritmo

### 4.1 Características
| Aspecto | Counting Sort |
|---------|---------------|
| **Estabilidade** | Sim |
| **Adaptabilidade** | Não |
| **In-Place** | Não |
| **Não Comparativo** | Sim |

### 4.2 Complexidade
| Caso | Complexidade | Descrição |
|------|-------------|-----------|
| **Melhor caso** | O(n + k) | n = número de elementos, k = intervalo |
| **Caso médio** | O(n + k) | Performance consistente |
| **Pior caso** | O(n + k) | Garantido em todos os casos |
| **Complexidade de espaço** | O(n + k) | Array auxiliar + array de contagem |

### 4.3 Vantagens
- **Complexidade linear O(n + k)**: Extremamente rápido para intervalos limitados;
- **Estável**: Mantém a ordem relativa de elementos iguais;
- **Não comparativo**: Não depende de comparações entre elementos;
- **Determinístico**: Sempre executa no mesmo tempo para mesma entrada;

### 4.4 Desvantagens
- **Não in-place**: Requer memória adicional O(n + k);
- **Apenas para inteiros**: Limitado a tipos de dados discretos;
- **Ineficiente para grandes intervalos**: Se k >> n, torna-se ineficiente;
- **Requer conhecimento do intervalo**: Precisa saber min e max antecipadamente;

### 4.5 Quando Escolher 
- **Para ordenar inteiros com intervalo limitado**;
- **Quando k = O(n)** (intervalo proporcional ao número de elementos);
- **Em aplicações onde estabilidade é importante**;
- **Como sub-rotina de algoritmos mais complexos** (ex: Radix Sort);

---


## 5. Aplicações Especiais
- **Radix Sort**: Como sub-rotina para ordenação por dígitos;
- **Bucket Sort**: Para distribuição em baldes;
- **Processamento de dados com chaves inteiras**;
- **Algoritmos de compressão e codificação**;
- **Processamento de imagens** (para histogramas e equalização);