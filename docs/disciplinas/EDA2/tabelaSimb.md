# Tabelas de Símbolos (Symbol Tables - ST)

---
## 1. Conceitos Gerais

Uma **Tabela de Símbolos (ST)** é uma estrutura de dados fundamental que armazena pares chave-valor, onde a chave é usada para identificar unicamente um item e o valor contém informações associadas a esse item.

**Princípio fundamental**: Fornecer operações eficientes para inserção, busca e remoção de itens baseados em suas chaves.

---

## 2. Interface Básica

### 2.1 Definições e Macros

```c title="Definições básicas para Tabela de Símbolos:"
#define key int
#define less(A, B) ((A) < (B))
#define eq(A, B) ((A) == (B))

typedef struct {
    key k;    // Chave (identificador único)
    data d;   // Dados associados à chave
} Item;

#define key(A) (A.k)  // Macro para acessar a chave de um item
```

### 2.2 Operações Básicas

```c title="Interface da Tabela de Símbolos:"
// Inicializa a tabela
void ST_init();

// Insere um item na tabela
void ST_insert(Item ni);

// Remove um item pela chave
void ST_remove(key r);

// Busca um item pela chave
Item ST_search(key k);

// Verifica se a tabela está vazia
int ST_empty();

// Retorna o número de itens na tabela
int ST_count();
```

---

## 3. Implementações de Tabelas de Símbolos

### 3.1 Implementação com Vetor Linear

#### 3.1.1 Características
- Usa um vetor para armazenar itens sequencialmente;
- `st_last` indica o número de itens e a próxima posição livre;
- Ideal para operações simples, mas com desempenho linear para busca e remoção;

#### 3.1.2 Implementação

```c title="Implementação com vetor linear:"
#define MAX_ITENS 1000000

int st_last;    // Número de itens e próxima posição livre
Item *st;       // Vetor de itens

// Inicializa a tabela
int ST_init() {
    st = malloc(sizeof(Item) * MAX_ITENS);
    if (st == NULL) return 0;  // Falha na alocação
    st_last = 0;
    return 1;  // Sucesso
}

// Insere um item no final do vetor
void ST_insert(Item ni) {
    if (st_last < MAX_ITENS) {
        st[st_last++] = ni;
    }
}

// Verifica se a tabela está vazia
int ST_empty() {
    return st_last == 0;
}

// Retorna o número de itens
int ST_count() {
    return st_last;
}

// Busca linear por uma chave
int ST_search_index(key k) {
    for (int i = 0; i < st_last; i++) {
        if (eq(k, key(st[i]))) {
            return i;  // Retorna o índice do item encontrado
        }
    }
    return -1;  // Não encontrado
}

// Busca e retorna o item
Item ST_search(key k) {
    int index = ST_search_index(k);
    if (index != -1) {
        return st[index];
    }
    // Retorna um item vazio ou trata o erro
    Item empty_item = {0};
    return empty_item;
}

// Remove um item pela chave
void ST_remove(key r) {
    int to_remove = ST_search_index(r);
    if (to_remove != -1) {
        // Move o último item para a posição a ser removida
        st[to_remove] = st[st_last - 1];
        st_last--;
    }
}

// Destrói a tabela liberando a memória
void ST_destroy() {
    free(st);
    st_last = 0;
}
```

#### 3.1.3 Análise de Complexidade
| Operação | Complexidade | Descrição |
|----------|-------------|-----------|
| **ST_insert** | O(1) | Inserção no final do vetor |
| **ST_search** | O(n) | Busca linear no vetor |
| **ST_remove** | O(n) | Busca + movimentação de elementos |
| **ST_count** | O(1) | Acesso direto ao contador |

### 3.2 Implementação com Lista Encadeada

#### 3.2.1 Características
- Cada nó contém um item e um ponteiro para o próximo nó;
- Inserções são feitas no início da lista (mais eficiente);
- Flexível quanto ao tamanho (crescimento dinâmico);

#### 3.2.2 Implementação

```c title="Implementação com lista encadeada:"
// Estrutura do nó da lista
typedef struct ST_node {
    Item item;
    struct ST_node *next;
} ST_node;

ST_node *st_head;  // Cabeça da lista
int st_count;      // Contador de elementos

// Inicializa a tabela
void ST_init() {
    st_head = NULL;
    st_count = 0;
}

// Insere um item no início da lista
void ST_insert(Item ni) {
    ST_node *new_node = malloc(sizeof(ST_node));
    if (new_node == NULL) return;  // Falha na alocação
    
    new_node->item = ni;
    new_node->next = st_head;
    st_head = new_node;
    st_count++;
}

// Verifica se a tabela está vazia
int ST_empty() {
    return st_head == NULL;
}

// Retorna o número de itens
int ST_count() {
    return st_count;
}

// Busca por uma chave na lista
Item ST_search(key k) {
    ST_node *current = st_head;
    
    while (current != NULL) {
        if (eq(k, key(current->item))) {
            return current->item;  // Item encontrado
        }
        current = current->next;
    }
    
    // Item não encontrado
    Item empty_item = {0};
    return empty_item;
}

// Remove um item pela chave
void ST_remove(key r) {
    ST_node *current = st_head;
    ST_node *prev = NULL;
    
    while (current != NULL) {
        if (eq(r, key(current->item))) {
            // Item encontrado, remover da lista
            if (prev == NULL) {
                // Remover o primeiro elemento
                st_head = current->next;
            } else {
                prev->next = current->next;
            }
            
            free(current);
            st_count--;
            return;
        }
        
        prev = current;
        current = current->next;
    }
}

// Destrói a tabela liberando toda a memória
void ST_destroy() {
    ST_node *current = st_head;
    ST_node *next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    st_head = NULL;
    st_count = 0;
}
```

#### 3.2.3 Análise de Complexidade
| Operação | Complexidade | Descrição |
|----------|-------------|-----------|
| **ST_insert** | O(1) | Inserção no início da lista |
| **ST_search** | O(n) | Busca linear na lista |
| **ST_remove** | O(n) | Busca + remoção do nó |
| **ST_count** | O(1) | Acesso direto ao contador |

---

### 4. Comparação das Implementações

| Aspecto | Vetor Linear | Lista Encadeada |
|---------|-------------|-----------------|
| **Inserção** | O(1) | O(1) |
| **Busca** | O(n) | O(n) |
| **Remoção** | O(n) | O(n) |
| **Espaço** | O(n) | O(n) |
| **Crescimento** | Tamanho fixo | Dinâmico |
| **Localidade** | Boa (cache) | Ruim |
| **Simplicidade** | Alta | Média |




