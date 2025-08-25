# Grafos Dirigidos (Dígrafos) e Grafos Ponderados

---
## 1. Grafos Dirigidos (Dígrafos)

### 1.1 Conceitos Básicos

Um **grafo dirigido** (dígrafo) é uma estrutura onde:
- **Vértices**: Conjunto de nós
- **Arestas direcionadas**: Conexões com direção específica (v → w)

**Propriedades fundamentais**:
- Assimetria: A → B não implica B → A
- Caminhos direcionais: Sequências de vértices conectados por arestas direcionadas
- Alcançabilidade: v é alcançável de u se existe caminho direcionado de u para v

### 1.2 Tipos de Grafos Dirigidos

**Grafo Dirigido Acícilico (DAG):** Grafo dirigido sem ciclos. Se vc sair de um vértice, vc não consegue voltar para ele;

**Grago Dirigido Fortemente Conexo:** Quando todos os vértices são alcançaveis a partir de todos os vértices;  

**Grafo conexo:** Cada um de seus vértices estpa ao alcanse de cada um dos demais;

**Grafos não conexo:** Há mais de um componente conexo;

### 1.2 Implementação de Dígrafos

```c title="Estruturas para Dígrafos:"
#define MAXV 1000

// Estrutura da aresta direcionada
typedef struct {
    int v;        // Vértice origem
    int w;        // Vértice destino
    float weight; // Peso (opcional)
} Edge;

// Dígrafo com matriz de adjacência
typedef struct {
    int V;
    int E;
    int **adj;      // Matriz de adjacência
    float **weight; // Matriz de pesos
} DigraphM;

// Dígrafo com lista de adjacência
typedef struct node {
    int w;
    float weight;
    struct node *next;
} Node;

typedef struct {
    int V;
    int E;
    Node **adj;     // Listas de adjacência (apenas arestas de saída)
} DigraphL;
```

### 1.3 Operações Básicas

```c title="Implementação de operações para dígrafos:"
// Inicialização de dígrafo com matriz
DigraphM* DIGRAPHinitM(int V) {
    DigraphM *G = malloc(sizeof(DigraphM));
    G->V = V;
    G->E = 0;
    G->adj = malloc(V * sizeof(int*));
    
    for (int i = 0; i < V; i++) {
        G->adj[i] = malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            G->adj[i][j] = 0;
        }
    }
    return G;
}

// Inserção de aresta direcionada
void DIGRAPHinsertM(DigraphM *G, Edge e) {
    if (G->adj[e.v][e.w] == 0) G->E++;
    G->adj[e.v][e.w] = 1;
    // Não insere a recíproca (diferente de grafo não-direcionado)
}

// Inversão de dígrafo
DigraphM* DIGRAPHreverseM(DigraphM *G) {
    DigraphM *R = DIGRAPHinitM(G->V);
    
    for (int v = 0; v < G->V; v++) {
        for (int w = 0; w < G->V; w++) {
            if (G->adj[v][w] == 1) {
                DIGRAPHinsertM(R, EDGE(w, v)); // Inverte direção
            }
        }
    }
    return R;
}
```

### 1.4 Algoritmo de Floyd-Warshall


**Usos:**

- Calcular o fecho transitivo de um grafo G;
- Encontrar distâncias mínimas entre todos os pares;
- Roteamento em redes;

**Complexidade:** O(V^3);

**Funcionamento:** Copia o grafo G e faz os vértices serem alcançaveis a si mesmos;

```c title="Fecho transitivo com Floyd-Warshall:"
void DIGRAPHtc(DigraphM *G) {
    // Aloca matriz do fecho transitivo
    int **tc = malloc(G->V * sizeof(int*));
    for (int i = 0; i < G->V; i++) {
        tc[i] = malloc(G->V * sizeof(int));
        for (int j = 0; j < G->V; j++) {
            tc[i][j] = G->adj[i][j]; // Cópia inicial
        }
    }
    
    // Todo vértice é alcançável de si mesmo
    for (int i = 0; i < G->V; i++) {
        tc[i][i] = 1;
    }
    
    // Algoritmo de Floyd-Warshall
    for (int k = 0; k < G->V; k++) {
        for (int i = 0; i < G->V; i++) {
            if (tc[i][k] == 1) {
                for (int j = 0; j < G->V; j++) {
                    if (tc[k][j] == 1) {
                        tc[i][j] = 1;
                    }
                }
            }
        }
    }
    
    // Atualiza a matriz do grafo
    for (int i = 0; i < G->V; i++) {
        free(G->adj[i]);
    }
    free(G->adj);
    G->adj = tc;
}

// Verificação de alcançabilidade
int DIGRAPHreach(DigraphM *G, int s, int t) {
    return G->adj[s][t];
}
```

---

## 2. Ordenação Topológica
É uma ordenação linear dos vértices de um DAG tal que para toda aresta u → v, u aparece antes de v na ordenação.

```c title="Implementação:"
static int inT[maxV];

void DAGts(Graph G, int ts[]) {
    for (int v = 0; v < G->V; v++) {
        inT[v] = 0;
        ts[v] = -1;
    }

    for (int v = 0; v < G->V; v++) {
        for (link t = G->adj[v]; t != NULL; t = t->next) {
            inT[t->w]++;
        }
    }

    QUEUEinit(G->V);

    for (int v = 0; v < G->V; v++) {
        if (inT[v] == 0) QUEUEput(v);
    }

    int i = 0, v;

    while (!QUEUEempty()) {
        ts[i++] = (v = QUEUEget());

        for (link t = G->adj[v]; t != NULL; t = t->next) {
            if (--inT[t->w] == 0) QUEUEput(t->w);
        }
    }
}

```

---

## 3. Grafos Ponderados
É aquele em que as arestas possuem pesos, como distâncias entre cidades, custos de rotas ou tempos de viagem. 

O **caminho mínimo** é o trajeto entre dois vértices com a menor soma de pesos. 

Um **vértice maduro** é aquele cujos vizinhos já foram totalmente explorados. 

Os pesos podem ser representados em:

- Matriz de adjacência, substituindo 0 e 1 pelos valores das arestas;

- Lista de adjacência, onde cada vértice armazena seus vizinhos e os respectivos pesos;

```c title="Implementações:"
// Grafo ponderado com matriz de adjacência
typedef struct {
    int V;
    int E;
    float **weight; // Matriz de pesos
} WGraphM;

// Grafo ponderado com lista de adjacência
typedef struct wnode {
    int w;
    float weight;
    struct wnode *next;
} WNode;

typedef struct {
    int V;
    int E;
    WNode **adj;
} WGraphL;

// Inicialização de grafo ponderado
WGraphM* WGRAPHinitM(int V) {
    WGraphM *G = malloc(sizeof(WGraphM));
    G->V = V;
    G->E = 0;
    G->weight = malloc(V * sizeof(float*));
    
    for (int i = 0; i < V; i++) {
        G->weight[i] = malloc(V * sizeof(float));
        for (int j = 0; j < V; j++) {
            G->weight[i][j] = INFINITY; // Valor que representa ausência de aresta
        }
    }
    return G;
}

// Inserção de aresta ponderada
void WGRAPHinsertM(WGraphM *G, Edge e) {
    if (G->weight[e.v][e.w] == INFINITY) G->E++;
    G->weight[e.v][e.w] = e.weight;
    G->weight[e.w][e.v] = e.weight; // Para grafo não-direcionado
}
```

---

## 4. Considerações Finais

### 4.1 Aplicações dos Dígrafos
- **Sistemas de dependência**: Compiladores, gerenciadores de pacotes
- **Redes de fluxo**: Sistemas de transporte, redes elétricas
- **Processos de negócio**: Workflows, cadeias de suprimentos
- **Redes sociais**: Seguidores, influências

### 4.2 Aplicações dos Grafos Ponderados
- **Sistemas de navegação**: Rotas mais curtas/rapidas
- **Projeto de redes**: Conexões de custo mínimo
- **Alocação de recursos**: Otimização de custos
- **Análise de redes**: Centralidade, importância

### 4.3 Complexidade dos Algoritmos

| Algoritmo | Complexidade | Aplicação |
|-----------|--------------|-----------|
| **Floyd-Warshall** | O(V³) | Fecho transitivo |
| **Ordenação Topológica** | O(V + E) | Ordenação em DAGs |

### 5.4 Escolha da Estrutura

**Matriz de Adjacência**:
- Grafos densos
- Consultas frequentes
- Operações matriciais

**Lista de Adjacência**:
- Grafos esparsos
- Iteração sobre vizinhos
- Memória limitada
