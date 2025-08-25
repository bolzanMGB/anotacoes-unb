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

```c title="Implementação:"
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

### 1.4 Aplicações do Bellman-Ford

- **Arbitragem em mercados financeiros**: Detecção de oportunidades onde sequências de transações resultam em lucro garantido
- **Redes de computadores**: Roteamento com métricas complexas
- **Sistemas de transporte**: Otimização considerando custos que podem ser negativos (subsídios)

---

## 2. Algoritmo de Dijkstra

O **algoritmo de Dijkstra** encontra caminhos mínimos em grafos com pesos não-negativos usando uma abordagem gulosa.

**Principais características**:
- Muito eficiente para grafos com pesos não-negativos
- Não funciona com pesos negativos
- Não detecta ciclos negativos
- Complexidade: O(V²) na versão simples, O(E + V log V) com fila de prioridade

```c title="Implementação::"
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
    if (heap->size <= 0) return (HeapNode){-1, INF};
    
    HeapNode root = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size-1];
    heap->size--;
    minHeapify(heap, 0);
    
    return root;
}

DijkstraResult* dijkstraOptimized(Graph *G, int src) {
    DijkstraResult *result = malloc(sizeof(DijkstraResult));
    result->dist = malloc(G->V * sizeof(int));
    result->parent = malloc(G->V * sizeof(int));
    
    MinHeap *heap = createMinHeap(G->V);
    
    // Inicialização
    for (int i = 0; i < G->V; i++) {
        result->dist[i] = INF;
        result->parent[i] = -1;
    }
    result->dist[src] = 0;
    
    insertMinHeap(heap, (HeapNode){src, 0});
    
    while (heap->size > 0) {
        HeapNode minNode = extractMin(heap);
        int u = minNode.vertex;
        
        Node *current = G->adj[u];
        while (current != NULL) {
            int v = current->w;
            int weight = current->weight;
            
            if (result->dist[u] != INF && result->dist[u] + weight < result->dist[v]) {
                result->dist[v] = result->dist[u] + weight;
                result->parent[v] = u;
                insertMinHeap(heap, (HeapNode){v, result->dist[v]});
            }
            current = current->next;
        }
    }
    
    free(heap->nodes);
    free(heap);
    return result;
}
```
