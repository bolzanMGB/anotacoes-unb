# Filas (Queues)

---
## Tipos Abstratos de Dados (TAD)

 uma maneira de organizar e estruturar dados, fornecendo uma interface clara para interagir com eles enquanto esconde os detalhes da implementação. As principais estruturas de dados são:

1. Filas;
2. Pilhas;
3. Árvores;

---

## 1. Conceitos Gerais

Uma **Fila** é uma estrutura de dados linear que segue o princípio **FIFO** (First In, First Out) - o primeiro elemento a entrar é o primeiro a sair. É análoga a uma fila de pessoas esperando em um banco ou supermercado.

**Princípio fundamental**: "Inserções no fim, remoções no início" - novos elementos são adicionados no final da fila e elementos são removidos apenas do início.

---

## 2. Implementações de Filas

### 2.1 Fila Estática Circular

```cpp title="Implementação de fila estática circular:"
#define N 7
int fila[N];
int p, u;  // p: índice do primeiro elemento, u: índice do próximo espaço vazio

void criar_fila() {
    p = u = 0;
}

int vazia() {
    return p == u;
}

int cheia() {
    return (u + 1) % N == p;  // Deixa uma posição vazia para distinguir cheia de vazia
}

// Adição no fim da fila
void enfileira(int y) {
    if (cheia()) {
        printf("Fila cheia!\n");
        return;
    }
    fila[u] = y;
    u = (u + 1) % N;  // Avança circularmente
}

// Remoção no início da fila 
int desenfileira() {
    if (vazia()) {
        printf("Fila vazia!\n");
        return -1;
    }
    int x = fila[p];
    p = (p + 1) % N;  // Avança circularmente
    return x;
}
```

### 2.2 Fila Dinâmica com Array

```cpp title="Implementação de fila dinâmica:"
typedef int Item;

typedef struct {
    Item *item;       // Ponteiro para o array de itens
    int capacidade;   // Capacidade máxima da fila
    int primeiro;     // Índice do primeiro elemento
    int ultimo;       // Índice do próximo espaço vazio
    int tamanho;      // Número atual de elementos
} Fila;

Fila *criar(int capacidade) {
    Fila *f = malloc(sizeof(Fila));
    f->item = malloc(capacidade * sizeof(Item));
    f->capacidade = capacidade;
    f->primeiro = f->ultimo = f->tamanho = 0;
    return f;
}

int vazia(Fila *f) {
    return f->tamanho == 0;
}

int cheia(Fila *f) {
    return f->tamanho == f->capacidade;
}

void enfileira(Fila *f, Item y) {
    if (cheia(f)) {
        printf("Fila cheia!\n");
        return;
    }
    f->item[f->ultimo] = y;
    f->ultimo = (f->ultimo + 1) % f->capacidade;
    f->tamanho++;
}

Item desenfileira(Fila *f) {
    if (vazia(f)) {
        printf("Fila vazia!\n");
        return -1;
    }
    Item x = f->item[f->primeiro];
    f->primeiro = (f->primeiro + 1) % f->capacidade;
    f->tamanho--;
    return x;
}

void destruir(Fila *f) {
    free(f->item);
    free(f);
}
```

### 2.3 Fila com Lista Encadeada

```cpp title="Implementação com lista encadeada:"
typedef int Item;

typedef struct no {
    Item info;
    struct no *prox;
} No;

typedef struct {
    No *inicio;    // Ponteiro para o primeiro elemento
    No *fim;       // Ponteiro para o último elemento
    int tamanho;   // Número de elementos na fila
} Fila;

Fila *criar() {
    Fila *f = malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    f->tamanho = 0;
    return f;
}

int vazia(Fila *f) {
    return f->inicio == NULL;
}

void enfileira(Fila *f, Item x) {
    No *novo = malloc(sizeof(No));
    novo->info = x;
    novo->prox = NULL;
    
    if (vazia(f)) {
        f->inicio = f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
    f->tamanho++;
}

Item desenfileira(Fila *f) {
    if (vazia(f)) {
        printf("Fila vazia!\n");
        return -1;
    }
    
    No *remover = f->inicio;
    Item x = remover->info;
    
    f->inicio = remover->prox;
    if (f->inicio == NULL) {  // Fila ficou vazia
        f->fim = NULL;
    }
    
    free(remover);
    f->tamanho--;
    return x;
}

void destruir(Fila *f) {
    while (!vazia(f)) {
        desenfileira(f);
    }
    free(f);
}
```

---

## 3. Funcionamento Passo a Passo

### 3.1 Exemplo com Fila Estática Circular

```cpp title="Operações em uma fila circular de tamanho 5:"
criar_fila() → p=0, u=0, fila: [ ] [ ] [ ] [ ] [ ]

enfileira(10) → p=0, u=1, fila: [10] [ ] [ ] [ ] [ ]
enfileira(20) → p=0, u=2, fila: [10] [20] [ ] [ ] [ ]
enfileira(30) → p=0, u=3, fila: [10] [20] [30] [ ] [ ]
enfileira(40) → p=0, u=4, fila: [10] [20] [30] [40] [ ]

desenfileira() → retorna 10, p=1, u=4, fila: [10] [20] [30] [40] [ ]
desenfileira() → retorna 20, p=2, u=4, fila: [10] [20] [30] [40] [ ]

enfileira(50) → p=2, u=0, fila: [50] [20] [30] [40] [ ]
enfileira(60) → p=2, u=1, fila: [50] [60] [30] [40] [ ]

desenfileira() → retorna 30, p=3, u=1, fila: [50] [60] [30] [40] [ ]
```

### 3.2 Visualização da Fila Encadeada

```cpp title="Operações em fila encadeada:"
criar() → inicio=NULL, fim=NULL, tamanho=0

enfileira(10):
inicio → [10|•] → NULL
fim --------------↑

enfileira(20):
inicio → [10|•] → [20|•] → NULL
fim ----------------------↑

enfileira(30):
inicio → [10|•] → [20|•] → [30|•] → NULL
fim ------------------------------↑

desenfileira() → remove 10:
inicio → [20|•] → [30|•] → NULL
fim ----------------------↑

desenfileira() → remove 20:
inicio → [30|•] → NULL
fim ------------↑
```

---

## 4. Análise da Estrutura

### 4.1 Características
| Aspecto | Fila |
|---------|------|
| **Organização** | Linear |
| **Acesso** | Restrito (apenas extremidades) |
| **Política** | FIFO (First In, First Out) |
| **Flexibilidade** | Tamanho fixo ou dinâmico |

### 4.2 Complexidade
| Operação | Array Estático | Lista Encadeada |
|----------|---------------|-----------------|
| **Enfileirar** | O(1) | O(1) |
| **Desenfileirar** | O(1) | O(1) |
| **Acessar frente** | O(1) | O(1) |
| **Buscar elemento** | O(n) | O(n) |
| **Espaço** | O(n) | O(n) |

### 4.3 Vantagens
- **Eficiência**: Operações básicas em tempo constante;
- **Simplicidade**: Implementação direta e intuitiva;
- **Previsibilidade**: Comportamento determinístico;
- **Versatilidade**: Múltiplas implementações possíveis;

### 4.4 Desvantagens
- **Acesso limitado**: Só é possível acessar os extremos;
- **Busca ineficiente**: O(n) para encontrar elementos específicos;
- **Tamanho fixo**: Nas implementações com array estático;

### 4.5 Quando Utilizar
- **Processamento em ordem**: Quando a ordem de processamento deve ser a ordem de chegada;
- **Sistemas de buffer**: Para gerenciar tarefas ou requisições pendentes;
- **Algoritmos de busca**: Como em busca em largura (BFS);
- **Sincronização**: Em sistemas concorrentes para comunicação entre processos;

---

## 5. Aplicações Práticas

### 5.1 Sistema de Impressão

```cpp title="Simulação de fila de impressão:"
Fila *fila_impressao = criar(100);

// Adicionar documentos à fila
void adicionar_documento(char *doc) {
    enfileira(fila_impressao, doc);
    printf("Documento '%s' adicionado à fila\n", doc);
}

// Processar impressão
void processar_impressao() {
    while (!vazia(fila_impressao)) {
        char *doc = desenfileira(fila_impressao);
        printf("Imprimindo: %s\n", doc);
        // Simular tempo de impressão
        sleep(2);
    }
}
```

### 5.2 Busca em Largura (BFS)

```cpp title="Implementação do BFS usando fila:"
void bfs(Grafo *g, int inicio) {
    int *visitado = calloc(g->n, sizeof(int));
    Fila *f = criar(g->n);
    
    visitado[inicio] = 1;
    enfileira(f, inicio);
    
    while (!vazia(f)) {
        int vertice = desenfileira(f);
        printf("Visitando vértice %d\n", vertice);
        
        for (int i = 0; i < g->n; i++) {
            if (g->adj[vertice][i] && !visitado[i]) {
                visitado[i] = 1;
                enfileira(f, i);
            }
        }
    }
    
    destruir(f);
    free(visitado);
}
```

### 5.3 Outras Aplicações Comuns
- **Sistema de atendimento**: Banco, supermercado, call center;
- **Buffer de rede**: Pacotes são processados na ordem de chegada;
- **Escalonamento de processos**: Em sistemas operacionais;
- **Simulação de eventos**: Modelagem de sistemas do mundo real;
