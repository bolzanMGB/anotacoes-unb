# Grafos 

---
## 1. Conceitos Gerais

Um **grafo** é uma estrutura de dados composta por:
- **Vértices (V)**: Conjunto de nós (representados como pontos)
- **Arestas (E)**: Conexões entre os vértices (representadas como linhas)

**Princípio fundamental**: Representar relações entre objetos através de conexões, permitindo modelar problemas complexos de diversas áreas.

---

## 2. Tipos de Grafos

### 2.1 Classificação por Direção
- **Grafos Não-Direcionados**: Arestas não têm direção (conexão bidirecional)
- **Grafos Direcionados (Digrafos)**: Arestas têm direção (ex: A → B)

### 2.2 Classificação por Peso
- **Grafos Não-Ponderados**: Arestas sem pesos
- **Grafos Ponderados**: Arestas com pesos (custo, distância, etc.)

### 2.3 Classificação por Conectividade
- **Grafo Conexo**: Existe caminho entre todos os pares de vértices
- **Grafo Desconexo**: Possui dois ou mais componentes conexos

### 2.4 Classificação por Ciclos
- **Grafo Acíclico**: Não contém ciclos
- **Grafo Cíclico**: Contém pelo menos um ciclo
- **Árvore**: Grafo conexo e acíclico

### 2.5 Outras Classificações
- **Grafo Simples**: Sem laços ou arestas múltiplas
- **Grafo Completo**: Todos os vértices conectados entre si

---

## 3. Estrutura de Dados

### 3.1 Definições e Macros

```c title="Definições básicas para Grafos:"
#define MAXV 1000        // Número máximo de vértices
#define NULL_EDGE {-1, -1}  // Aresta nula

// Estrutura da aresta
typedef struct {
    int v;        // Vértice de origem
    int w;        // Vértice de destino
    float weight; // Peso (opcional)
} Edge;

// Macro para criar arestas
#define EDGE(v, w) {v, w, 1.0}
#define EDGE_W(v, w, weight) {v, w, weight}

// Macros para comparação
#define eq(A, B) ((A.v == B.v && A.w == B.w) || (A.v == B.w && A.w == B.v))
```

### 3.2 Matriz de Adjacência

```c title="Implementação com Matriz de Adjacência:"
typedef struct {
    int V;           // Número de vértices
    int E;           // Número de arestas
    int **adj;       // Matriz de adjacência
    float **weight;  // Matriz de pesos (opcional)
} GraphM;

// Inicialização
GraphM* GRAPHinitM(int V) {
    GraphM *G = malloc(sizeof(GraphM));
    G->V = V;
    G->E = 0;
    
    // Aloca matriz de adjacência
    G->adj = malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        G->adj[i] = malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            G->adj[i][j] = 0;
        }
    }
    
    return G;
}

// Inserção de aresta
void GRAPHinsertM(GraphM *G, Edge e) {
    if (G->adj[e.v][e.w] == 0) G->E++;
    G->adj[e.v][e.w] = 1;
    G->adj[e.w][e.v] = 1;  // Para grafo não-direcionado
}

// Remoção de aresta
void GRAPHremoveM(GraphM *G, Edge e) {
    if (G->adj[e.v][e.w] == 1) G->E--;
    G->adj[e.v][e.w] = 0;
    G->adj[e.w][e.v] = 0;
}

// Consulta de aresta
int GRAPHedgeM(GraphM *G, int v, int w) {
    return G->adj[v][w];
}
```

### 3.3 Lista de Adjacência

```c title="Implementação com Lista de Adjacência:"
// Estrutura do nó da lista
typedef struct node {
    int w;           // Vértice destino
    float weight;    // Peso da aresta
    struct node *next;
} Node;

typedef struct {
    int V;           // Número de vértices
    int E;           // Número de arestas
    Node **adj;      // Vetor de listas de adjacência
} GraphL;

// Inicialização
GraphL* GRAPHinitL(int V) {
    GraphL *G = malloc(sizeof(GraphL));
    G->V = V;
    G->E = 0;
    G->adj = malloc(V * sizeof(Node*));
    
    for (int i = 0; i < V; i++) {
        G->adj[i] = NULL;
    }
    
    return G;
}

// Cria novo nó
Node* NEW(int w, float weight, Node *next) {
    Node *x = malloc(sizeof(Node));
    x->w = w;
    x->weight = weight;
    x->next = next;
    return x;
}

// Inserção de aresta
void GRAPHinsertL(GraphL *G, Edge e) {
    G->adj[e.v] = NEW(e.w, e.weight, G->adj[e.v]);
    G->adj[e.w] = NEW(e.v, e.weight, G->adj[e.w]);  // Não-direcionado
    G->E++;
}

// Remoção de aresta
void GRAPHremoveL(GraphL *G, Edge e) {
    // Remove de v para w
    Node **t = &G->adj[e.v];
    while (*t != NULL) {
        if ((*t)->w == e.w) {
            Node *tmp = *t;
            *t = (*t)->next;
            free(tmp);
            break;
        }
        t = &(*t)->next;
    }
    
    // Remove de w para v (não-direcionado)
    t = &G->adj[e.w];
    while (*t != NULL) {
        if ((*t)->w == e.v) {
            Node *tmp = *t;
            *t = (*t)->next;
            free(tmp);
            G->E--;
            break;
        }
        t = &(*t)->next;
    }
}
```

---

## 4. Algoritmos de Busca

### 4.1 Busca em Profundidade (DFS)

```c title="DFS com Matriz de Adjacência:"
int pre[MAXV];  // Tempo de descoberta
int cnt;        // Contador

void dfsR(GraphM *G, Edge e) {
    int w = e.w;
    pre[w] = cnt++;
    
    for (int t = 0; t < G->V; t++) {
        if (G->adj[w][t] != 0 && pre[t] == -1) {
            dfsR(G, EDGE(w, t));
        }
    }
}

void GRAPHdfsM(GraphM *G) {
    cnt = 0;
    for (int v = 0; v < G->V; v++) pre[v] = -1;
    
    for (int v = 0; v < G->V; v++) {
        if (pre[v] == -1) {
            dfsR(G, EDGE(v, v));
        }
    }
}
```

```c title="DFS com Lista de Adjacência:"
void dfsR(GraphL *G, Edge e) {
    int w = e.w;
    pre[w] = cnt++;
    
    for (Node *t = G->adj[w]; t != NULL; t = t->next) {
        if (pre[t->w] == -1) {
            dfsR(G, EDGE(w, t->w));
        }
    }
}

void GRAPHdfsL(GraphL *G) {
    cnt = 0;
    for (int v = 0; v < G->V; v++) pre[v] = -1;
    
    for (int v = 0; v < G->V; v++) {
        if (pre[v] == -1) {
            dfsR(G, EDGE(v, v));
        }
    }
}
```

### 4.2 Busca em Largura (BFS)

```c title="BFS com Lista de Adjacência:"
// Estrutura de fila
typedef struct {
    Edge *items;
    int front, rear, size, capacity;
} Queue;

Queue* QUEUEinit(int capacity) {
    Queue *Q = malloc(sizeof(Queue));
    Q->items = malloc(capacity * sizeof(Edge));
    Q->front = 0;
    Q->rear = -1;
    Q->size = 0;
    Q->capacity = capacity;
    return Q;
}

void bfs(GraphL *G, Edge e) {
    Queue *Q = QUEUEinit(G->V);
    QUEUEput(Q, e);
    pre[e.w] = cnt++;
    
    while (Q->size > 0) {
        e = QUEUEget(Q);
        int w = e.w;
        
        for (Node *t = G->adj[w]; t != NULL; t = t->next) {
            if (pre[t->w] == -1) {
                QUEUEput(Q, EDGE(w, t->w));
                pre[t->w] = cnt++;
            }
        }
    }
    
    free(Q->items);
    free(Q);
}

void GRAPHbfsL(GraphL *G) {
    cnt = 0;
    for (int v = 0; v < G->V; v++) pre[v] = -1;
    
    for (int v = 0; v < G->V; v++) {
        if (pre[v] == -1) {
            bfs(G, EDGE(v, v));
        }
    }
}
```

---

## 5. Comparação de Implementações

### 5.1 Complexidade das Operações

| Operação | Matriz de Adjacência | Lista de Adjacência |
|----------|----------------------|---------------------|
| **Espaço** | O(V²) | O(V + E) |
| **Inserção** | O(1) | O(1) |
| **Remoção** | O(1) | O(grau(v)) |
| **Consulta** | O(1) | O(grau(v)) |
| **DFS/BFS** | O(V²) | O(V + E) |

### 5.2 Quando Usar Cada Implementação

**Matriz de Adjacência:**
- Grafos densos (E ≈ V²)
- Consultas frequentes de existência de arestas
- Operações matriciais
- Memória não é limitante

**Lista de Adjacência:**
- Grafos esparsos (E << V²)
- Iteração frequente sobre vizinhos
- Grafos que mudam frequentemente
- Memória limitada

### 5.3 Aplicações Práticas

**Matriz de Adjacência:**
- Redes altamente conectadas
- Algoritmos de caminho mínimo (Floyd-Warshall)
- Processamento de imagens

**Lista de Adjacência:**
- Redes sociais
- Sistemas de navegação
- Compiladores (grafos de fluxo)
- Jogos com mundos abertos

---

## 6. Exemplo de Uso

```c title="Exemplo completo de uso de grafos:"
int main() {
    // Cria grafo com 5 vértices
    GraphL *G = GRAPHinitL(5);
    
    // Insere arestas
    GRAPHinsertL(G, EDGE(0, 1));
    GRAPHinsertL(G, EDGE(0, 2));
    GRAPHinsertL(G, EDGE(1, 3));
    GRAPHinsertL(G, EDGE(2, 4));
    GRAPHinsertL(G, EDGE(3, 4));
    
    printf("Grafo criado com %d vértices e %d arestas\n", G->V, G->E);
    
    // Executa DFS
    printf("Ordem DFS: ");
    GRAPHdfsL(G);
    for (int i = 0; i < G->V; i++) {
        printf("%d(%d) ", i, pre[i]);
    }
    printf("\n");
    
    // Executa BFS
    printf("Ordem BFS: ");
    GRAPHbfsL(G);
    for (int i = 0; i < G->V; i++) {
        printf("%d(%d) ", i, pre[i]);
    }
    printf("\n");
    
    // Remove aresta
    GRAPHremoveL(G, EDGE(0, 2));
    printf("Após remoção: %d arestas\n", G->E);
    
    return 0;
}
```

---

## 7. Considerações Finais

### 7.1 Vantagens dos Grafos
- **Modelagem flexível**: Representam diversos tipos de relações
- **Algoritmos eficientes**: Muitos problemas bem estudados
- **Escalabilidade**: Boa performance com estruturas adequadas

### 7.2 Desafios
- **Complexidade de implementação**: Especialmente para algoritmos avançados
- **Uso de memória**: Pode ser intensivo para grafos grandes
- **Escolha da estrutura**: Impacto significativo na performance

### 7.3 Aplicações Comuns
- **Redes sociais**: Amizades, seguidores
- **Sistemas de navegação**: Rotas e mapas
- **Compiladores**: Análise de código
- **Bioinformática**: Redes de proteínas
- **Recomendação**: Sistemas de recomendação

### 7.4 Extensões Comuns
- **Grafos ponderados**: Arestas com pesos
- **Grafos direcionados**: Relações assimétricas
- **Multigrafos**: Múltiplas arestas entre vértices
- **Hipergrafos**: Arestas conectando múltiplos vértices

Os grafos representam uma das estruturas de dados mais versáteis e poderosas na ciência da computação, permitindo a modelagem e solução eficiente de problemas complexos em diversas áreas do conhecimento.