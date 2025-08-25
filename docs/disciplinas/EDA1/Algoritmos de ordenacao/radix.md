# Radix Sort

---

## 1. Conceitos Gerais

O **Radix Sort** (Ordenação por Raiz) é um algoritmo de ordenação **não comparativo** que decompõe as chaves em partes menores (dígitos, bytes ou caracteres) e ordena os elementos com base nessas partes. É particularmente eficiente para ordenar números inteiros grandes e strings.

**Princípio fundamental**: "Decompor, ordenar por partes e combinar" - decompõe a chave em dígitos/bytes, ordena de forma estável a partir do dígito menos ou mais significativo, e combina os resultados.

---

## 2. Implementação do Radix Sort

### 2.1 Radix Sort LSD (Least Significant Digit)

```cpp title="Radix Sort LSD para inteiros:"
#define bytesword 4  // Tamanho de um int (4 bytes)
#define bitsbyte 8   // Bits por byte
#define R (1 << bitsbyte)  // Tamanho do alfabeto (256)

// Macro para extrair o dígito/byte na posição D
#define digit(N, D) (((N) >> ((D) * bitsbyte)) & (R - 1))

void radix_sortLSD(int *v, int l, int r) {
    int i, w, k;
    int n = r - l + 1;
    int *aux = new int[n];
    int *count = new int[R + 1];

    // Processa cada byte (do menos significativo ao mais significativo)
    for (w = 0; w < bytesword; w++) {
        // Zera o array de contagem
        for (i = 0; i <= R; i++) count[i] = 0;

        // Fase 1: Contar frequências do byte atual
        for (i = l; i <= r; i++) count[digit(v[i], w) + 1]++;

        // Fase 2: Calcular posições acumuladas
        for (k = 1; k < R; k++) count[k] += count[k - 1];

        // Fase 3: Distribuir elementos no array auxiliar
        for (i = l; i <= r; i++) aux[count[digit(v[i], w)]++] = v[i];

        // Fase 4: Copiar de volta para o array original
        for (i = l; i <= r; i++) v[i] = aux[i - l];
    }

    delete[] aux;
    delete[] count;
}
```

### 2.2 Radix Sort MSD (Most Significant Digit)

```cpp title="Radix Sort MSD para strings:"
#define maxstring 100  // Tamanho máximo da string
#define R 256          // Tamanho do alfabeto ASCII

void radixMSD(char a[][maxstring], int l, int r, int d) {
    if (r <= l) return;

    int n = r - l + 1;
    char (*aux)[maxstring] = new char[n][maxstring];
    int *count = new int[R + 2]();  // +2 para segurança

    // Contar frequências do caractere na posição d
    for (int i = l; i <= r; i++) {
        int pos = (unsigned char)a[i][d] + 1;
        count[pos]++;
    }

    // Calcular posições acumuladas
    for (int i = 1; i <= R + 1; i++) {
        count[i] += count[i - 1];
    }

    // Distribuir strings no array auxiliar
    for (int i = l; i <= r; i++) {
        int pos = (unsigned char)a[i][d];
        strcpy(aux[count[pos]++], a[i]);
    }

    // Copiar de volta para o array original
    for (int i = l; i <= r; i++) {
        strcpy(a[i], aux[i - l]);
    }

    // Recursão para cada subgrupo (exceto grupo de strings terminadas)
    for (int i = 1; i < R; i++) {
        int start = l + count[i - 1];
        int end = l + count[i] - 1;
        if (start < end) {
            radixMSD(a, start, end, d + 1);
        }
    }

    delete[] aux;
    delete[] count;
}

// Função wrapper para MSD
void radix_sortMSD(char a[][maxstring], int l, int r) {
    radixMSD(a, l, r, 0);
}
```

---

## 3. Funcionamento Passo a Passo

### 3.1 Exemplo LSD com Números

```cpp title="Exemplo LSD: [170, 45, 75, 90, 802, 24, 2, 66]"
Array inicial: [170, 45, 75, 90, 802, 24, 2, 66]

Ordenação por unidade (dígito menos significativo):
802, 002, 024, 045, 066, 170, 075, 090

Ordenação por dezena:
002, 024, 045, 066, 075, 090, 170, 802

Ordenação por centena (dígito mais significativo):
002, 024, 045, 066, 075, 090, 170, 802

Resultado final: [2, 24, 45, 66, 75, 90, 170, 802]
```

### 3.2 Exemplo MSD com Strings

```cpp title="Exemplo MSD: ["aab", "bba", "aaa", "baaa"]"
Array inicial: ["aab", "bba", "aaa", "baaa"]

Primeira passagem (primeiro caractere):
Grupo 'a': ["aab", "aaa"]
Grupo 'b': ["bba", "baaa"]

Segunda passagem (segundo caractere):
Grupo 'a' → "aab", "aaa" → ordenado por segundo caractere
Grupo 'b' → "bba", "baaa" → ordenado por segundo caractere

Resultado final: ["aaa", "aab", "baaa", "bba"]
```

---

## 4. Análise do Algoritmo

### 4.1 Características
| Aspecto | LSD Radix Sort | MSD Radix Sort |
|---------|----------------|----------------|
| **Estabilidade** | Sim | Não |
| **Adaptabilidade** | Não | Parcialmente |
| **In-Place** | Não | Não |
| **Não Comparativo** | Sim | Sim |

### 4.2 Complexidade
| Caso | Complexidade | Descrição |
|------|-------------|-----------|
| **Melhor caso** | O(w × n) | w = tamanho da chave, n = número de elementos |
| **Caso médio** | O(w × n) | Performance consistente |
| **Pior caso** | O(w × n) | Garantido em todos os casos |
| **Complexidade de espaço** | O(n + R) | Array auxiliar + array de contagem |

### 4.3 Vantagens
- **Complexidade linear O(w × n)**: Muito rápido para chaves de tamanho fixo;
- **Não comparativo**: Não depende de comparações entre elementos;
- **Eficiente para grandes datasets**: Performance previsível;
- **Estável (LSD)**: Mantém ordem relativa de elementos iguais;

### 4.4 Desvantagens
- **Não in-place**: Requer memória adicional O(n + R);
- **Apenas para tipos específicos**: Limitado a chaves que podem ser decompostas;
- **Ineficiente para chaves longas**: Se w >> n, torna-se ineficiente;
- **Dependente da base**: Performance varia com o tamanho do alfabeto R;

### 4.5 Quando Escolher 
- **Para ordenar inteiros com tamanho fixo**;
- **Para ordenar strings com padrões específicos**;
- **Quando w é pequeno e conhecido**;
- **Em aplicações de processamento de dados** onde chaves são uniformes;

---


## 5. Aplicações Especiais
- **Ordenação de inteiros grandes**: CPFs, números de série, etc.;
- **Processamento de strings**: Dicionários, índices de texto;
- **Banco de dados**: Ordenação de chaves primárias;
- **Computação gráfica**: Ordenação de pixels/vertices;
- **Compressão de dados**: Ordenação para algoritmos de compressão;