# Árvore Binária de Busca (BST) - Implementação Avançada

---
## 1. Conceitos Gerais

Uma **Árvore Binária de Busca (BST)** é uma estrutura de dados que permite a busca binária a partir da raiz, mantendo os elementos organizados de forma hierárquica com base em suas chaves.

**Princípio fundamental**: Para qualquer nó:
- Todos os nós na subárvore esquerda têm chaves menores;
- Todos os nós na subárvore direita têm chaves maiores;

---

## 2. Estrutura de Dados

### 2.1 Definições e Macros

```c title="Definições básicas para BST:"
typedef int Key;  // Tipo da chave

// Estrutura do item (chave + dados)
typedef struct {
    Key k;        // Chave
    // data d;    // Dados associados (pode ser expandido)
} Item;

#define NULL_ITEM {0}  // Item nulo

// Macros para manipulação de itens
#define key(A) ((A).k)
#define less(A, B) (key(A) < key(B))
#define eq(A, B) (key(A) == key(B))
```

### 2.2 Estrutura do Nó

```c title="Estrutura do nó da BST:"
typedef struct STNode *link;

struct STNode {
    Item item;    // Item armazenado
    link l;       // Ponteiro para filho esquerdo
    link r;       // Ponteiro para filho direito
    int N;        // Tamanho da subárvore (nó atual + filhos)
};

// Variáveis globais
link h;  // Raiz da árvore
link z;  // Nó sentinela (representa folhas vazias/nulo)
```

---

## 3. Implementação das Operações

### 3.1 Inicialização e Utilidades

```c title="Inicialização e funções auxiliares:"
// Criar um novo nó
link NEW(Item item, link l, link r, int N) {
    link x = malloc(sizeof(struct STNode));
    x->item = item;
    x->l = l;
    x->r = r;
    x->N = N;
    return x;
}

// Inicializar a árvore
void ST_init() {
    z = NEW(NULL_ITEM, NULL, NULL, 0);  // Nó sentinela
    h = z;  // Raiz inicial aponta para sentinela
}

// Retorna o número de nós da árvore
int ST_count() {
    return h->N;
}

// Verifica se a árvore está vazia
int ST_empty() {
    return h == z;
}
```

### 3.2 Inserção

```c title="Inserção recursiva:"
// Função pública de inserção
void ST_insert(Item item) {
    h = insertR(h, item);
}

// Função recursiva de inserção
link insertR(link r, Item item) {
    if (r == z)  // Encontrou posição de inserção
        return NEW(item, z, z, 1);
    
    Key k = key(item);
    Key t = key(r->item);
    
    if (less(k, t)) {
        r->l = insertR(r->l, item);
    } else {
        r->r = insertR(r->r, item);
    }
    
    r->N++;  // Atualiza contador de nós
    return r;
}
```

### 3.3 Busca

```c title="Busca recursiva:"
// Função pública de busca
Item ST_search(Key k) {
    return searchR(h, k);
}

// Função recursiva de busca
Item searchR(link r, Key k) {
    if (r == z)  // Não encontrado
        return NULL_ITEM;
    
    Key t = key(r->item);
    
    if (eq(k, t))
        return r->item;
    else if (less(k, t))
        return searchR(r->l, k);
    else
        return searchR(r->r, k);
}
```

### 3.4 Travessia e Ordenação

```c title="Travessia in-order (ordenada):"
// Função de visita (pode ser personalizada)
void visit(Item i) {
    printf("%d ", key(i));  // Exemplo: imprime a chave
}

// Travessia in-order recursiva
void sortR(link r, void (*visit)(Item)) {
    if (r == z) return;
    
    sortR(r->l, visit);  // Visita subárvore esquerda
    visit(r->item);      // Visita nó atual
    sortR(r->r, visit);  // Visita subárvore direita
}

// Função pública para ordenação
void ST_sort(void (*visit)(Item)) {
    sortR(h, visit);
}
```

### 3.5 Exemplo de Uso

```c title="Exemplo de uso da BST:"
int main() {
    ST_init();  // Inicializa árvore
    
    // Insere alguns itens
    Item items[] = {{5}, {3}, {7}, {2}, {4}, {6}, {8}};
    for (int i = 0; i < 7; i++) {
        ST_insert(items[i]);
    }
    
    printf("Número de nós: %d\n", ST_count());
    printf("Elementos em ordem: ");
    ST_sort(visit);  // Imprime: 2 3 4 5 6 7 8
    
    // Busca por uma chave
    Key busca = 4;
    Item resultado = ST_search(busca);
    if (key(resultado) != 0) {
        printf("\nEncontrado: %d\n", key(resultado));
    } else {
        printf("\nNão encontrado: %d\n", busca);
    }
    
    return 0;
}
```

---

## 4. Análise de Performance

### 4.1 Complexidade das Operações

| Operação | Melhor Caso | Caso Médio | Pior Caso |
|----------|------------|------------|-----------|
| **Busca** | O(1) | O(log n) | O(n) |
| **Inserção** | O(1) | O(log n) | O(n) |
| **Remoção** | O(1) | O(log n) | O(n) |
| **Travessia** | O(n) | O(n) | O(n) |

### 4.2 Propriedades Estatísticas

- **Busca bem-sucedida**: ≈1.39 log₂N comparações em média;
- **Busca mal-sucedida**: ≈1.39 log₂N comparações em média;
- **Altura média**: ≈1.39 log₂N para árvores aleatórias;

### 4.3 Problemas e Limitações

- **Desbalanceamento**: Inserções ordenadas criam árvores degeneradas (lista encadeada);
- **Performance no pior caso**: Operações tornam-se O(n);
- **Memória**: Overhead de ponteiros e contadores;

---


## 5. Considerações Finais

### 5.1 Quando Usar BST
- **Dados dinâmicos**: Inserções e remoções frequentes;
- **Busca ordenada**: Necessidade de percurso ordenado;
- **Memória disponível**: Overhead aceitável de ponteiros;

### 5.2 Alternativas
- **Hash Tables**: Melhor para busca exata (O(1) average);
- **Arrays ordenados**: Melhor para dados estáticos;
- **Árvores balanceadas**: AVL, Red-Black, B-Trees para grandes datasets;
