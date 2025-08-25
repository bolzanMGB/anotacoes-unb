# Árvores Geradoras Mínimas (MST) - Implementação e Análise

---


## 1 Árvores Geradoras de um Grafo Não-dirigido
É um subconjunto das arestas de um grafo conectado e não dirigido;

- Contem todos os vertices de G;
- É conexo e sem ciclos;
- Se o GND tem V vértices, a AG tem V - 1 arestas;

``` c title = "Exemplo"
// grafo
    A
   / \
  B---C
  |   |
  D---E

// possivel arvore geradora
    A
   / \
  B   C
  |
  D
   \
    E

```

## 2. Árvore Geradora Mínima

Uma **Árvore Geradora Mínima (MST - Minimum Spanning Tree)** de um grafo não-dirigido e conexo é uma árvore geradora que:

- Conecta todos os vértices
- Não forma ciclos
- Tem a soma mínima possível dos pesos das arestas

**Propriedades importantes**:
- Se o grafo tem V vértices, a MST tem exatamente V-1 arestas
- Pode existir mais de uma MST para o mesmo grafo
- Só existe MST se o grafo for conexo

---
## 3 Algorítmos de MST

### 3.1 Algoritmo de Prim

#### 3.1.1 Implementação do Prim

```c title="Algoritmo de Prim para MST:"
#define UGraph Graph
/* Recebe um grafo não-dirigido conexo G com custos arbitrários nas arestas e calcula uma MST de G.  A função trata a MST como uma árvore radicada com raiz 0 e armazena a árvore no vetor de pais pa[].  (A função implementa o algoritmo de Prim. O grafo G e os custos são representados por listas de adjacência. O código abaixo foi inspirado no Programa 21.1 de Sedgewick.) */
void UGRAPHmstP2( UGraph G, vertex *pa)
{ 
   bool tree[1000];
   int preco[1000];
   // inicialização:
   for (vertex v = 1; v < G->V; ++v) 
      pa[v] = -1, tree[v] = false, preco[v] = INFINITY; 
   pa[0] = 0, tree[0] = true;
   for (link a = G->adj[0]; a != NULL; a = a->next) 
      pa[a->w] = 0, preco[a->w] = a->c; 

   PQinit( G->V); 
   for (vertex v = 1; v < G->V; ++v)
      PQinsert( v, preco);

   while (!PQempty( )) {
      vertex y = PQdelmin( preco);
      if (preco[y] == INFINITY) break;
      tree[y] = true;
      // atualização dos preços e ganchos:
      for (link a = G->adj[y]; a != NULL; a = a->next) 
         if (!tree[a->w] && a->c < preco[a->w]) { 
            preco[a->w] = a->c;
            PQdec( a->w, preco); 
            pa[a->w] = y; 
         }
   }
   PQfree( );
}
```

---

## 4. Algoritmo de Kruskal
**Características:**

- Seleciona arestas de menor peso, sem formar ciclos, até ligar todos os vértices;

**Ideia central:**

- Ordena as  arestas por peso crescente;
- Inicializa com a aresta de menor peso;
- Cada iteração vai adicionando uma aresta;
- Se a proxima aresta possui uma aresta que ja esta esta conectada indiretamente pela floresta atual, é pulada;

**Bom quando:**


- Grafos esparsos (poucas arestas);
- Grafos nao dirigidos;
- Tem uma lista das arestas
### 4.1 Implementação do Kruskal

```c title="Algoritmo de Kruskal para MST:"
MST-Kruskal (G, n, m, p)
arestas := Sort-Edges (G, m, p)
X := { }
Initialize ()
para i := 1 até m
    uv := arestas[i]
    r := Find (u)
    s := Find (v)
    se r ≠ s
	     X := X ∪ { uv }
       Union (r, s)
devolva (V(G), X)


1. Ordene as arestas por peso crescente.
2. Inicialize F como floresta vazia (sem arestas).
3. Para cada aresta uv na ordem:
    - Se u e v estão em componentes diferentes (não formam ciclo):
        - Adicione uv à floresta F.
        - Una as componentes de u e v.
4. Quando F tiver (n - 1) arestas, pare.
```

---

