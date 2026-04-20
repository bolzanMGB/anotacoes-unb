# Algoritmos de Navegação para Micromouse


## 1. Wall Follower (Seguidor de Parede)

### Funcionamento
Baseia-se na regra da "mão direita" ou "mão esquerda". O robô mantém contato constante com uma das paredes laterais e segue o contorno do labirinto até encontrar a saída ou o objetivo. É um algoritmo puramente reativo (sem memória).

* **Complexidade:** Muito Baixa.
* **Armazenamento:** Não requer mapa ou histórico de posições.
* **Performance:** Baixa eficiência de tempo, pois percorre perímetros desnecessários.
* **Ponto Cego:** Pode entrar em loops infinitos se o objetivo estiver em uma "ilha" (paredes centrais não conectadas ao perímetro externo).

**Quando usar:** Ideal para testes iniciais de hardware e sensores em labirintos simples (ex: 4x4) ou como lógica de segurança ("fail-safe").



## 2. Backtracking (Busca em Profundidade - DFS)

### Funcionamento
O robô explora um caminho até encontrar um beco sem saída ou uma célula já visitada. Ao encontrar um obstáculo intransponível, ele "retrocede" (backtrack) até a última bifurcação com caminhos não explorados para tentar uma nova rota.

* **Complexidade:** Média.
* **Armazenamento:** Requer uma pilha (stack) ou marcação de células visitadas no mapa.
* **Performance:** Garante a descoberta do objetivo em qualquer labirinto conexo, mas não garante o caminho mais curto na primeira tentativa.
* **Vantagem:** Exploração sistemática e completa do ambiente.

**Quando usar:** Recomendado para a fase de mapeamento inicial de labirintos desconhecidos, garantindo que o centro (sala retangular) seja encontrado.


## 3. Flood Fill

### Funcionamento
Atribui um "valor de potencial" ou "distância" para cada célula do labirinto. O destino (centro) recebe valor 0, e as células adjacentes recebem valores crescentes (1, 2, 3...). O robô sempre se move para a célula vizinha que possui o menor valor numérico. Sempre que uma nova parede é detectada, os valores de distância são recalculados (inundação).

* **Complexidade:** Alta.
* **Armazenamento:** Requer uma matriz representativa do labirinto (mapa de distâncias).
* **Performance:** Altamente eficiente. Minimiza a exploração de áreas inúteis e foca na convergência para o alvo.
* **Diferencial:** É o algoritmo padrão para competições de alto nível devido ao seu equilíbrio entre exploração e velocidade.

**Quando usar:** Mais indicado para o desafio completo, especialmente nos labirintos de 8x8 e 16x16, onde a eficiência de passos é crucial.

## 4. Dijkstra

### Funcionamento
Trata o labirinto como um grafo, onde cada célula é um nó e as passagens são arestas com peso (custo de movimento). Ele calcula o caminho de menor custo total entre o ponto atual e o destino, analisando todas as possibilidades de forma exaustiva.

* **Complexidade:** Muito Alta.
* **Armazenamento:** Requer estrutura de grafos e lista de prioridades.
* **Performance:** Máxima na busca pelo caminho mais curto ("Shortest Path"). Garante matematicamente a rota mais rápida após o mapeamento.
* **Custo Computacional:** Exige mais processamento para recalcular a rota em tempo real a cada nova parede descoberta.

**Quando usar:** Indicado para a "corrida final" (speed run) em labirintos de 16x16, após o robô já ter mapeado as paredes e precisar apenas executar a trajetória mais veloz possível.



## 5. Comparativo de Performance

| Critério | Wall Follower | Backtracking | Flood Fill | Dijkstra |
| :--- | :--- | :--- | :--- | :--- |
| **Garante Saída?** | Não (se houver ilhas) | Sim | Sim | Sim |
| **Caminho Otimizado?** | Não | Não | Sim | Sim (Absoluto) |
| **Uso de Memória** | Mínimo | Médio | Alto | Muito Alto |
| **Processamento** | Irrelevante | Baixo | Moderado | Elevado |
| **Melhor Cenário** | Labirinto 4x4 | Exploração Inicial | Competições/Geral | Recorde de Velocidade |

