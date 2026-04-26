# Busca Sequencial

---

## 1. Conceitos Gerais

A **busca sequencial** é um algoritmo simples que percorre cada elemento de uma estrutura de dados (lista, array, etc.) até encontrar o elemento desejado ou percorrer toda a estrutura.

**Características principais:**

- Algoritmo mais básico para busca;
- Não requer que os dados estejam ordenados;
- Implementação simples e intuitiva;
- Pode ser aplicada em qualquer estrutura sequencial;

---

## 2. Complexidade 

| Caso | Complexidade | Descrição |
|------|-------------|-----------|
| **Melhor caso** | O(1) | Elemento encontrado na primeira posição |
| **Caso médio** | O(n) = (n + 1)/2 | Em média, verifica metade dos registros |
| **Pior caso** | O(n) | Elemento na última posição ou ausente |

---

## 3. Implementação

### 3.1 Em Arrays Não Ordenados
```c title="Implementação:"
int busca_sequencial_array(int vetor[], int tamanho, int chave) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == chave) {
            return i; // Retorna o índice onde encontrou
        }
    }
    return -1; // Retorna -1 se não encontrou
}
```
### 3.2 Em Arrays Ordenados
```c title="Implementação:"
int busca_sequencial_ordenada(int vetor[], int tamanho, int chave) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == chave) {
            return i; // Elemento encontrado
        }
        if (vetor[i] > chave) {
            return -1; // Para antecipadamente - elemento não existe
        }
    }
    return -1; // Elemento não encontrado
}
```
### 3.3 Em Listas Simplesmente Encadeadas
```c title="Implementação:"
no *busca_sequencial_lista(no *inicio, int chave) {
    no *atual = inicio;
    
    while (atual != NULL) {
        if (atual->info == chave) {
            return atual; // Retorna o nó encontrado
        }
        atual = atual->prox;
    }
    
    return NULL; // Retorna NULL se não encontrou
}
```

---

## 4. Análise Comparativa

### 4.1 Comparação entre Estruturas

| Estrutura | Busca | Inserção | Remoção | Melhor Uso |
|-----------|-------|----------|---------|------------|
| **Lista Encadeada** | O(n) | O(1) no início/fim | O(1) no início, O(n) no meio/fim | Inserções/remoções frequentes no início |
| **Array Não-Ordenado** | O(n) | O(1) no fim (com espaço) | O(n) | Dados não ordenados, acesso aleatório |
| **Array Ordenado** | O(n) | O(n) | O(n) | Dados que precisam estar ordenados |

### 4.2 Vantagens da Busca Sequencial
- Implementação simples
- Não requer dados ordenados
- Funciona com qualquer estrutura sequencial
- Não requer conhecimento prévio da estrutura

### 4.3 Desvantagens da Busca Sequencial
- Ineficiente para grandes conjuntos de dados
- Complexidade linear pode ser limitante
- Não aproveita ordenação quando existe

---

## 5. Quando Usar Busca Sequencial

### 5.1 Cenários Adequados
- Conjuntos de dados pequenos
- Dados não ordenados
- Buscas esporádicas
- Implementações simples
- Quando a ordenação tem custo proibitivo

### 5.2 Cenários Não Adequados
- Conjuntos de dados muito grandes
- Buscas frequentes
- Dados ordenados (use busca binária)
- Aplicações que requerem alto desempenho

