# Tabela Hash - Implementação e Análise

---
## 1. Conceitos Gerais

Uma **Tabela Hash** é uma estrutura de dados que mapeia chaves a valores usando uma função hash, permitindo acesso rápido aos dados com complexidade média O(1).

**Princípio fundamental**: 
- **Função hash**: Transforma uma chave em um índice da tabela
- **Colisões**: Quando duas chaves diferentes produzem o mesmo índice
- **Tratamento de colisões**: Estratégias para resolver conflitos (encadeamento, endereçamento aberto)

---

## 2. Estrutura de Dados

### 2.1 Definições e Macros

```c title="Definições básicas para Tabela Hash:"
typedef int Key;  // Tipo da chave

// Estrutura do item (chave + dados)
typedef struct {
    Key k;        // Chave
    // data d;    // Dados associados (pode ser expandido)
} Item;

#define NULL_ITEM {0}      // Item nulo
#define NULL_KEY 0         // Chave nula

// Macros para manipulação de itens
#define key(A) ((A).k)
#define less(A, B) (key(A) < key(B))
#define eq(A, B) (key(A) == key(B))

// Constantes
#define MAX_COL 10         // Máximo de colisões permitidas
#define LOAD_FACTOR 0.75   // Fator de carga para redimensionamento
```

### 2.2 Estruturas para Diferentes Implementações

```c title="Estrutura para Encadeamento Separado:"
typedef struct ListNode *link;

struct ListNode {
    Item item;
    link next;
};

typedef struct {
    link *heads;    // Vetor de listas encadeadas
    int M;          // Tamanho da tabela
    int N;          // Número de elementos
} HashTableChaining;

link z;  // Nó sentinela
```

```c title="Estrutura para Endereçamento Aberto:"
typedef struct {
    Item *table;    // Vetor de itens
    int M;          // Tamanho da tabela
    int N;          // Número de elementos
} HashTableOpen;

// Estados dos slots
#define EMPTY 0
#define OCCUPIED 1
#define DELETED 2
```

---

## 3. Implementação das Operações

### 3.1 Funções Hash

```c title="Diversas funções hash:"
// Hash modular para inteiros
int hash_int(Key k, int M) {
    return k % M;
}

// Hash para strings (método de Horner)
int hash_string(char *v, int M) {
    int h = 0, a = 127;
    for (; *v != '\0'; v++)
        h = (a * h + *v) % M;
    return h;
}

// Hash universal para inteiros
int hash_universal(Key k, int M) {
    // Coeficientes aleatórios (exemplo)
    static int a = 12345, b = 67890, p = 999983;
    return ((a * k + b) % p) % M;
}

// Função hash principal
int hash(Key k, int M) {
    return hash_int(k, M);
}
```

### 3.2 Encadeamento Separado

```c title="Implementação com listas encadeadas:"
// Inicialização
void HT_init_chaining(HashTableChaining *ht, int size) {
    ht->M = size;
    ht->N = 0;
    ht->heads = malloc(size * sizeof(link));
    z = malloc(sizeof(struct ListNode));
    z->next = z;
    
    for (int i = 0; i < size; i++) {
        ht->heads[i] = malloc(sizeof(struct ListNode));
        ht->heads[i]->next = z;
        ht->heads[i]->item = NULL_ITEM;
    }
}

// Inserção
void HT_insert_chaining(HashTableChaining *ht, Item item) {
    int h = hash(key(item), ht->M);
    link current = ht->heads[h]->next;
    link prev = ht->heads[h];
    
    // Verifica se já existe
    while (current != z) {
        if (eq(key(current->item), key(item))) {
            current->item = item;  // Atualiza
            return;
        }
        prev = current;
        current = current->next;
    }
    
    // Insere novo nó
    link new_node = malloc(sizeof(struct ListNode));
    new_node->item = item;
    new_node->next = z;
    prev->next = new_node;
    ht->N++;
}

// Busca
Item HT_search_chaining(HashTableChaining *ht, Key k) {
    int h = hash(k, ht->M);
    link current = ht->heads[h]->next;
    
    while (current != z) {
        if (eq(key(current->item), k))
            return current->item;
        current = current->next;
    }
    
    return NULL_ITEM;
}

// Remoção
void HT_remove_chaining(HashTableChaining *ht, Key k) {
    int h = hash(k, ht->M);
    link current = ht->heads[h]->next;
    link prev = ht->heads[h];
    
    while (current != z) {
        if (eq(key(current->item), k)) {
            prev->next = current->next;
            free(current);
            ht->N--;
            return;
        }
        prev = current;
        current = current->next;
    }
}
```

### 3.3 Endereçamento Aberto com Sondagem Linear

```c title="Implementação com endereçamento aberto:"
// Inicialização
void HT_init_open(HashTableOpen *ht, int size) {
    ht->M = size;
    ht->N = 0;
    ht->table = malloc(size * sizeof(Item));
    
    for (int i = 0; i < size; i++) {
        ht->table[i] = NULL_ITEM;
    }
}

// Inserção
int HT_insert_open(HashTableOpen *ht, Item item) {
    if (ht->N >= ht->M * LOAD_FACTOR) {
        HT_resize(ht, ht->M * 2);
    }
    
    int h = hash(key(item), ht->M);
    int c = MAX_COL;
    
    while (c > 0 && key(ht->table[h]) != NULL_KEY) {
        if (eq(key(ht->table[h]), key(item))) {
            ht->table[h] = item;  // Atualiza
            return 1;
        }
        h = (h + 1) % ht->M;
        c--;
    }
    
    if (c == 0) return 0;  // Muitas colisões
    
    ht->table[h] = item;
    ht->N++;
    return 1;
}

// Busca
Item HT_search_open(HashTableOpen *ht, Key k) {
    int h = hash(k, ht->M);
    int c = MAX_COL;
    
    while (c > 0 && key(ht->table[h]) != NULL_KEY) {
        if (eq(key(ht->table[h]), k))
            return ht->table[h];
        h = (h + 1) % ht->M;
        c--;
    }
    
    return NULL_ITEM;
}

// Remoção
void HT_remove_open(HashTableOpen *ht, Key k) {
    int h = hash(k, ht->M);
    int c = MAX_COL;
    
    while (c > 0 && key(ht->table[h]) != NULL_KEY) {
        if (eq(key(ht->table[h]), k)) {
            ht->table[h] = NULL_ITEM;
            ht->N--;
            return;
        }
        h = (h + 1) % ht->M;
        c--;
    }
}
```

### 3.4 Double Hashing

```c title="Implementação com double hashing:"
// Segunda função hash
int hash2(Key k) {
    return (k % 97) + 1;  // Nunca retorna 0
}

// Inserção com double hashing
int HT_insert_double(HashTableOpen *ht, Item item) {
    if (ht->N >= ht->M * LOAD_FACTOR) {
        HT_resize(ht, ht->M * 2);
    }
    
    int h1 = hash(key(item), ht->M);
    int h2 = hash2(key(item));
    int h = h1;
    int c = MAX_COL;
    
    while (c > 0 && key(ht->table[h]) != NULL_KEY) {
        if (eq(key(ht->table[h]), key(item))) {
            ht->table[h] = item;
            return 1;
        }
        h = (h + h2) % ht->M;
        c--;
    }
    
    if (c == 0) return 0;
    
    ht->table[h] = item;
    ht->N++;
    return 1;
}
```

### 3.5 Redimensionamento da Tabela

```c title="Redimensionamento:"
void HT_resize(HashTableOpen *ht, int new_size) {
    Item *old_table = ht->table;
    int old_M = ht->M;
    
    // Nova tabela
    ht->table = malloc(new_size * sizeof(Item));
    ht->M = new_size;
    ht->N = 0;
    
    // Inicializa nova tabela
    for (int i = 0; i < new_size; i++) {
        ht->table[i] = NULL_ITEM;
    }
    
    // Reinsere todos os elementos
    for (int i = 0; i < old_M; i++) {
        if (key(old_table[i]) != NULL_KEY) {
            HT_insert_open(ht, old_table[i]);
        }
    }
    
    free(old_table);
}
```

---

## 6. Considerações Finais

### 6.1 Quando Usar Tabela Hash
- **Acesso rápido**: Quando O(1) é crítico
- **Chaves únicas**: Dicionários, caches, bancos de dados
- **Dados dinâmicos**: Muitas inserções/remoções

### 6.2 Escolha da Implementação
- **Encadeamento**: Simplicidade, dados imprevisíveis
- **Sondagem Linear**: Memória limitada, dados conhecidos
- **Double Hashing**: Performance consistente, evitar clusterização

### 6.3 Boas Práticas
- **Tamanho primo**: Para distribuição uniforme
- **Monitorar fator de carga**: Redimensionar quando α > 0.75
- **Função hash robusta**: Minimizar colisões
- **Teste de performance**: Avaliar com dados reais

### 6.4 Aplicações Práticas
- **Bancos de dados**: Índices hash
- **Caches**: Memória cache, cache de DNS
- **Compiladores**: Tabelas de símbolos
- **Sistemas de arquivos**: Diretórios rápidos
- **Roteamento**: Tables de roteamento em redes
