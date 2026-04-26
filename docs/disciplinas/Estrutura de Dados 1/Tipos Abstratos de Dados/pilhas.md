# Pilhas (Stacks)

---

## 1. Conceitos Gerais

Uma **Pilha** é uma estrutura de dados linear que segue o princípio **LIFO** (Last In, First Out) - o último elemento a entrar é o primeiro a sair. É análoga a uma pilha de pratos ou livros.

**Princípio fundamental**: "Inserções e remoções ocorrem apenas no topo" - novos elementos são adicionados no topo da pilha e elementos são removidos apenas do topo.

---

## 2. Implementações de Pilhas

### 2.1 Pilha Estática com Array

```cpp title="Implementação de pilha estática:"
#define MAX 100

typedef int Item;

typedef struct {
    Item itens[MAX];
    int topo;
} Pilha;

void criar_pilha(Pilha *p) {
    p->topo = 0;
}

int vazia(Pilha *p) {
    return p->topo == 0;
}

int cheia(Pilha *p) {
    return p->topo == MAX;
}

void empilhar(Pilha *p, Item item) {
    if (cheia(p)) {
        printf("Pilha cheia!\n");
        return;
    }
    p->itens[p->topo++] = item;
}

Item desempilhar(Pilha *p) {
    if (vazia(p)) {
        printf("Pilha vazia!\n");
        return -1;
    }
    return p->itens[--p->topo];
}

Item topo(Pilha *p) {
    if (vazia(p)) {
        printf("Pilha vazia!\n");
        return -1;
    }
    return p->itens[p->topo - 1];
}
```

### 2.2 Pilha Dinâmica com Array

```cpp title="Implementação de pilha dinâmica:"
typedef int Item;

typedef struct {
    Item *itens;      // Ponteiro para o array de itens
    int capacidade;   // Capacidade máxima da pilha
    int topo;         // Índice do próximo espaço vazio
} Pilha;

Pilha *criar(int capacidade) {
    Pilha *p = malloc(sizeof(Pilha));
    p->itens = malloc(capacidade * sizeof(Item));
    p->capacidade = capacidade;
    p->topo = 0;
    return p;
}

int vazia(Pilha *p) {
    return p->topo == 0;
}

int cheia(Pilha *p) {
    return p->topo == p->capacidade;
}

void empilhar(Pilha *p, Item item) {
    if (cheia(p)) {
        printf("Pilha cheia!\n");
        return;
    }
    p->itens[p->topo++] = item;
}

Item desempilhar(Pilha *p) {
    if (vazia(p)) {
        printf("Pilha vazia!\n");
        return -1;
    }
    return p->itens[--p->topo];
}

Item topo(Pilha *p) {
    if (vazia(p)) {
        printf("Pilha vazia!\n");
        return -1;
    }
    return p->itens[p->topo - 1];
}

void destruir(Pilha *p) {
    free(p->itens);
    free(p);
}
```

### 2.3 Pilha com Lista Encadeada

```cpp title="Implementação com lista encadeada:"
typedef int Item;

typedef struct no {
    Item info;
    struct no *prox;
} No;

typedef struct {
    No *topo;      // Ponteiro para o topo da pilha
    int tamanho;   // Número de elementos na pilha
} Pilha;

Pilha *criar() {
    Pilha *p = malloc(sizeof(Pilha));
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

int vazia(Pilha *p) {
    return p->topo == NULL;
}

void empilhar(Pilha *p, Item x) {
    No *novo = malloc(sizeof(No));
    novo->info = x;
    novo->prox = p->topo;  // Novo nó aponta para o antigo topo
    p->topo = novo;        // Topo agora é o novo nó
    p->tamanho++;
}

Item desempilhar(Pilha *p) {
    if (vazia(p)) {
        printf("Pilha vazia!\n");
        return -1;
    }
    
    No *remover = p->topo;
    Item x = remover->info;
    
    p->topo = remover->prox;  // Topo agora é o próximo elemento
    free(remover);
    p->tamanho--;
    
    return x;
}

Item topo(Pilha *p) {
    if (vazia(p)) {
        printf("Pilha vazia!\n");
        return -1;
    }
    return p->topo->info;
}

void destruir(Pilha *p) {
    while (!vazia(p)) {
        desempilhar(p);
    }
    free(p);
}
```

---

## 3. Funcionamento Passo a Passo

### 3.1 Exemplo com Pilha Estática

```cpp title="Operações em uma pilha:"
criar_pilha() → topo=0, pilha: [ ] [ ] [ ] [ ] [ ]

empilhar(10) → topo=1, pilha: [10] [ ] [ ] [ ] [ ]
empilhar(20) → topo=2, pilha: [10] [20] [ ] [ ] [ ]
empilhar(30) → topo=3, pilha: [10] [20] [30] [ ] [ ]

desempilhar() → retorna 30, topo=2, pilha: [10] [20] [30] [ ] [ ]
desempilhar() → retorna 20, topo=1, pilha: [10] [20] [30] [ ] [ ]

empilhar(40) → topo=2, pilha: [10] [40] [30] [ ] [ ]
empilhar(50) → topo=3, pilha: [10] [40] [50] [ ] [ ]

topo() → retorna 50, topo=3, pilha: [10] [40] [50] [ ] [ ]
```

### 3.2 Visualização da Pilha Encadeada

```cpp title="Operações em pilha encadeada:"
criar() → topo=NULL, tamanho=0

empilhar(10):
topo → [10|•] → NULL

empilhar(20):
topo → [20|•] → [10|•] → NULL

empilhar(30):
topo → [30|•] → [20|•] → [10|•] → NULL

desempilhar() → remove 30:
topo → [20|•] → [10|•] → NULL

desempilhar() → remove 20:
topo → [10|•] → NULL

topo() → retorna 10
```

---

## 4. Análise da Estrutura

### 4.1 Características
| Aspecto | Pilha |
|---------|-------|
| **Organização** | Linear |
| **Acesso** | Restrito (apenas topo) |
| **Política** | LIFO (Last In, First Out) |
| **Flexibilidade** | Tamanho fixo ou dinâmico |

### 4.2 Complexidade
| Operação | Array Estático | Lista Encadeada |
|----------|---------------|-----------------|
| **Empilhar** | O(1) | O(1) |
| **Desempilhar** | O(1) | O(1) |
| **Consultar topo** | O(1) | O(1) |
| **Buscar elemento** | O(n) | O(n) |
| **Espaço** | O(n) | O(n) |

### 4.3 Vantagens
- **Eficiência**: Operações básicas em tempo constante;
- **Simplicidade**: Implementação direta e intuitiva;
- **Gerenciamento de memória**: Uso eficiente de recursos;
- **Versatilidade**: Múltiplas aplicações em computação;

### 4.4 Desvantagens
- **Acesso limitado**: Só é possível acessar o elemento do topo;
- **Busca ineficiente**: O(n) para encontrar elementos específicos;
- **Tamanho fixo**: Nas implementações com array estático;

### 4.5 Quando Utilizar
- **Gerenciamento de memória**: Pilha de execução em programas;
- **Algoritmos recursivos**: Substituição de recursão por iteração;
- **Navegação em sistemas**: Histórico de navegação em browsers;
- **Processamento de linguagens**: Análise sintática e balanceamento;
- **Backtracking**: Exploração sistemática de possibilidades;

---

## 5. Aplicações Práticas

### 5.1 Balanceamento de Parênteses

```cpp title="Verificador de expressões balanceadas:"
int balanceado(char *expressao) {
    Pilha *p = criar(strlen(expressao));
    
    for (int i = 0; expressao[i] != '\0'; i++) {
        if (expressao[i] == '(' || expressao[i] == '[' || expressao[i] == '{') {
            empilhar(p, expressao[i]);
        } else if (expressao[i] == ')' || expressao[i] == ']' || expressao[i] == '}') {
            if (vazia(p)) {
                destruir(p);
                return 0;
            }
            
            char topo_char = desempilhar(p);
            if ((expressao[i] == ')' && topo_char != '(') ||
                (expressao[i] == ']' && topo_char != '[') ||
                (expressao[i] == '}' && topo_char != '{')) {
                destruir(p);
                return 0;
            }
        }
    }
    
    int resultado = vazia(p);
    destruir(p);
    return resultado;
}
```

### 5.2 Conversão de Infixo para Pósfixo

```cpp title="Conversão de notação:"
char *infixo_para_posfixo(char *infixo) {
    Pilha *p = criar(strlen(infixo));
    char *posfixo = malloc((strlen(infixo) + 1) * sizeof(char));
    int j = 0;
    
    for (int i = 0; infixo[i] != '\0'; i++) {
        if (isdigit(infixo[i])) {
            posfixo[j++] = infixo[i];
        } else if (infixo[i] == '(') {
            empilhar(p, infixo[i]);
        } else if (infixo[i] == ')') {
            while (!vazia(p) && topo(p) != '(') {
                posfixo[j++] = desempilhar(p);
            }
            desempilhar(p); // Remove '('
        } else { // Operador
            while (!vazia(p) && precedencia(topo(p)) >= precedencia(infixo[i])) {
                posfixo[j++] = desempilhar(p);
            }
            empilhar(p, infixo[i]);
        }
    }
    
    while (!vazia(p)) {
        posfixo[j++] = desempilhar(p);
    }
    posfixo[j] = '\0';
    
    destruir(p);
    return posfixo;
}
```

### 5.3 Busca em Profundidade (DFS)

```cpp title="Implementação do DFS usando pilha:"
void dfs(Grafo *g, int inicio) {
    int *visitado = calloc(g->n, sizeof(int));
    Pilha *p = criar(g->n);
    
    visitado[inicio] = 1;
    empilhar(p, inicio);
    
    while (!vazia(p)) {
        int vertice = desempilhar(p);
        printf("Visitando vértice %d\n", vertice);
        
        for (int i = 0; i < g->n; i++) {
            if (g->adj[vertice][i] && !visitado[i]) {
                visitado[i] = 1;
                empilhar(p, i);
            }
        }
    }
    
    destruir(p);
    free(visitado);
}
```

### 5.4 Outras Aplicações Comuns
- **Sistema de undo/redo**: Em editores de texto e imagem;
- **Avaliação de expressões pósfixas**: Calculadoras;
- **Chamadas de função**: Pilha de execução em programas;
- **Navegador web**: Histórico de páginas visitadas;
- **Compiladores**: Análise sintática e geração de código;