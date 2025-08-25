# Algoritmos para Caminhos Mínimos

---

## 1. Algoritmo de Bellman-Ford

### 1.1 Conceitos e Características

O **algoritmo de Bellman-Ford** é utilizado para encontrar caminhos mínimos em grafos com pesos que podem ser negativos, além de detectar ciclos negativos.

**Principais características**:
- Funciona com pesos negativos
- Detecta ciclos negativos
- Complexidade: O(V × E) - quadrática
- Menos eficiente que Dijkstra para grafos sem pesos negativos

### 1.2 Implementação

```c title="Implementação do Bellman-Ford:"
bool GRAPHcptBF(Graph G, int s, int *pa, int *dist) {
    bool onqueue[1000];

    for (int v = 0; v < G->V; v++)
        pa[v] = -1, dist[v] = INT_MAX, onqueue[v] = false;

    pa[s] = s;
    dist[s] = 0;

    QueueInit(G->E);
    QueuePut(s);
    onqueue[s] = true;

    QueuePut(G->V);
    int k = 0;

    while (1) {
        int v = QueueGet();
        if (v < G->V) {
            for (link a = G->adj[v]; a != NULL; a = a->next) {
                if (dist[v] + a->c < dist[a->w]) {
                    dist[a->w] = dist[v] + a->c;
                    pa[a->w] = v;

                    if (onqueue[a->w] == false) {
                        QueuePut(a->w);
                        onqueue[a->w] = true;
                    }
                }
            }
        } else {
            if (QueueEmpty()) return true;
            if (++k >= G->V) return false;

            QueuePut(G->V);
            for (int t = 0; t < G->V; t++)
                onqueue[t] = false;
        }
    }
}
```

### 1.3 Exemplo de Execução

```c title="Exemplo de uso do Bellman-Ford:"
int main() {
    // Cria grafo de exemplo
    Graph *G = malloc(sizeof(Graph));
    G->V = 4;
    G->E = 5;
    G->adj = malloc(G->V * sizeof(Node*));
    for (int i = 0; i < G->V; i++) G->adj[i] = NULL;
    
    // Insere arestas (incluindo peso negativo)
    // 0 → 1: -1
    // 0 → 2: 4
    // 1 → 2: 3
    // 1 → 3: 2
    // 3 → 1: -6 (ciclo negativo potencial)
    
    // Executa Bellman-Ford
    int *dist = malloc(G->V * sizeof(int));
    int *parent = malloc(G->V * sizeof(int));
    
    bool has_negative_cycle = !GRAPHcptBF(G, 0, parent, dist);
    
    if (has_negative_cycle) {
        printf("O grafo contém ciclo negativo!\n");
    } else {
        printf("Distâncias mínimas a partir do vértice 0:\n");
        for (int i = 0; i < G->V; i++) {
            if (dist[i] == INT_MAX) {
                printf("Vértice %d: Inalcançável\n", i);
            } else {
                printf("Vértice %d: %d\n", i, dist[i]);
            }
        }
    }
    
    free(dist);
    free(parent);
    return 0;
}
```

### 1.4 Aplicações do Bellman-Ford

- **Arbitragem em mercados financeiros**: Detecção de oportunidades onde sequências de transações resultam em lucro garantido
- **Redes de computadores**: Roteamento com métricas complexas
- **Sistemas de transporte**: Otimização considerando custos que podem ser negativos (subsídios)

---

## 2. Algoritmo de Dijkstra

### 2.1 Conceitos e Características

O **algoritmo de Dijkstra** encontra caminhos mínimos em grafos com pesos não-negativos usando uma abordagem gulosa.

**Principais características**:
- Muito eficiente para grafos com pesos não-negativos
- Não funciona com pesos negativos
- Não detecta ciclos negativos
- Complexidade: O(V²) na versão simples, O(E + V log V) com fila de prioridade

### 2.2 Implementação

```c title="Implementação do Dijkstra com Fila de Prioridade:"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Estrutura para elementos da fila de prioridade
typedef struct {
    int vertex;
    int distance;
} HeapNode;

// Estrutura do min-heap
typedef struct {
    HeapNode *nodes;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap *heap = malloc(sizeof(MinHeap));
    heap->nodes = malloc(capacity * sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    
    if (left < heap->size && heap->nodes[left].distance < heap->nodes[smallest].distance)
        smallest = left;
    
    if (right < heap->size && heap->nodes[right].distance < heap->nodes[smallest].distance)
        smallest = right;
    
    if (smallest != idx) {
        swap(&heap->nodes[idx], &heap->nodes[smallest]);
        minHeapify(heap, smallest);
    }
}

void insertMinHeap(MinHeap *heap, HeapNode node) {
    if (heap->size == heap->capacity) return;
    
    heap->size++;
    int i = heap->size - 1;
    heap->nodes[i] = node;
    
    while (i != 0 && heap->nodes[(i-1)/2].distance > heap->nodes[i].distance) {
        swap(&heap->nodes[i], &heap->nodes[(i-1)/2]);
        i = (i-1)/2;
    }
}

HeapNode extractMin(MinHeap *heap) {
    if (heap->size <= 0) return (HeapNode){-1, INT_MAX};
    
    HeapNode root = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size-1];
    heap->size--;
    minHeapify(heap, 0);
    
    return root;
}

void dijkstra(Graph *G, int src, int *dist, int *parent) {
    MinHeap *heap = createMinHeap(G->V);
    int *visited = calloc(G->V, sizeof(int));
    
    // Inicialização
    for (int i = 0; i < G->V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[src] = 0;
    
    insertMinHeap(heap, (HeapNode){src, 0});
    
    while (heap->size > 0) {
        HeapNode minNode = extractMin(heap);
        int u = minNode.vertex;
        
        if (visited[u]) continue;
        visited[u] = 1;
        
        Node *current = G->adj[u];
        while (current != NULL) {
            int v = current->w;
            int weight = current->weight;
            
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                insertMinHeap(heap, (HeapNode){v, dist[v]});
            }
            current = current->next;
        }
    }
    
    free(heap->nodes);
    free(heap);
    free(visited);
}
```

### 2.3 Exemplo de Execução

```c title="Exemplo de uso do Dijkstra:"
int main() {
    // Cria grafo com pesos não-negativos
    Graph *G = malloc(sizeof(Graph));
    G->V = 5;
    G->E = 7;
    G->adj = malloc(G->V * sizeof(Node*));
    for (int i = 0; i < G->V; i++) G->adj[i] = NULL;
    
    // Insere arestas (0→1:4, 0→2:1, 1→3:1, 2→1:2, 2→3:5, 3→4:3)
    
    int *dist = malloc(G->V * sizeof(int));
    int *parent = malloc(G->V * sizeof(int));
    
    printf("Executando Dijkstra a partir do vértice 0:\n");
    dijkstra(G, 0, dist, parent);
    
    printf("Distâncias mínimas:\n");
    for (int i = 0; i < G->V; i++) {
        if (dist[i] == INT_MAX) {
            printf("Vértice %d: Inalcançável\n", i);
        } else {
            printf("Vértice %d: %d\n", i, dist[i]);
        }
    }
    
    free(dist);
    free(parent);
    return 0;
}
```

### 2.4 Aplicações do Dijkstra

- **Sistemas de navegação**: GPS, aplicativos de rotas (Waze, Google Maps)
- **Redes de computadores**: Roteamento OSPF, IS-IS
- **Logística**: Otimização de rotas de entrega
- **Jogos**: Pathfinding em games para encontrar caminhos mais curtos
- **Robótica**: Planejamento de trajetória para robôs móveis

---

## 3. Comparação entre os Algoritmos

### 3.1 Tabela Comparativa

| Característica | Bellman-Ford | Dijkstra |
|----------------|--------------|-----------|
| **Pesos negativos** |  Suporta |  Não suporta |
| **Ciclos negativos** | Detecta |  Não detecta |
| **Complexidade** | O(V×E) | O(V²) ou O(E + V log V) |
| **Abordagem** | Programação dinâmica | Algoritmo guloso |
| **Uso de memória** | Moderado | Baixo a moderado |
| **Aplicações típicas** | Arbitragem, redes | Navegação, roteamento |

### 3.2 Escolha do Algoritmo

**Use Bellman-Ford quando**:
- O grafo contém pesos negativos
- Precisa detectar ciclos negativos
- O grafo é pequeno ou moderado

**Use Dijkstra quando**:
- Todos os pesos são não-negativos
- Deseja máxima eficiência
- O grafo é grande

### 3.3 Considerações de Implementação

1. **Para grafos esparsos**: Dijkstra com fila de prioridade é mais eficiente
2. **Para grafos densos**: Dijkstra simples pode ser competitivo
3. **Para verificação rápida**: Bellman-Ford é mais versátil mas menos eficiente
4. **Para aplicações em tempo real**: Dijkstra é geralmente preferido