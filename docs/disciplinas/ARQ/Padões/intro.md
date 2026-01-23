# Padrões de Projetos

---

## 1. O que são?

- Um padrão é uma solução boa, testada e aprovada apra um problema recorrente.
- Padrçoes de projeto são princípios e soluções usados durante a criação de software.
- Eles são codificados em um formato estruturado descrevendo o problema e a respectiva solução adotada.
- Servem como um vocabulário comum para desenvolvedores, facilitando a comunicação sobre soluções de design.

---

## 2. O que são Padrões GRASP?

- GRASP é o acrônimo para General Responsibility Assignment Software Patterns.
- São princípios orientadores que ajudam a tomar decisões sobre como atribuir responsailidades a classes e objetos em um design orientado a objetos.
- São os padrões fundamentais de design de software, sendo a base para a maioria dos padrões mais complexos, como os da Gang of Four.

    - GoFs Criacionais.
    - GoFs Estruturais.
    - GoFs Comportamentais.

## 3. Principais Padrões GRASP

### 3.1 GRASP Criador (Creator)

**Propósito:** determinar qual classe é responsável por criar instâncias de uma determinada classe.

**Regras:** a classe B deve ter a responsabilidade de criar instâncias da classe A se:

- B contém A ou é um composição de A (relação todo-parte).
- B registra A.
- B usa A de mandeira muito próxima.
- B tem dados iniciais de A, que serão passadoa para A quando este for criado.

**Composição:**

- As parte só existem se o todo existir.
- Nesse caso, a responsabilidade de criação da instância PARTE é atribuida à entidade TODO.
- Exemplo: No jogo de tabuleiro, a classe Board (TODO) é a responsável por criar instância de Square (PARTE), pois o tabuleiro contẽm os quadrados.

### 3.2 GRASP Especialista (Information Expert)

**Propósito:** atribuir uma responsabilidade (como cálculo, ordenação, ou cadastro) à classe que possui a informação necessária para cumpri-la. É o padrão que se preocupa em atribuir responsabilidades para a entidade mais especialista em um dado aspecto.

**Princípio Chave:** a informação necessária para executar uma operação deve residir na classe que armazena ou gerencia esses dados

**Relação com Criador:** O padrão Criador é, na verdade, um caso especial do Especialista: O CRIADOR É UM ESPECIALISTA EM CRIAÇÃO DE INSTÂNCIAS.

**Exemplo:**

- Em um sistema de vendas, a classe Sale é o TODO, e SalesLineItem é a PARTE (composição). 
- Portanto, Sale é a especialista na criação de SalesLineItem (aplicando o Criador/Especialista).
- Para calcular o total de uma venda, a responsabilidade é distribuída: a Sale pode solicitar o total de cada SalesLineItem, e o SalesLineItem pode usar a ProductDescription para obter o preço. A classe com os dados mais próximos do cálculo deve fazê-lo.

## 4. Exemplo Completo (Sistema de Vendas)

### 4.1 Classes Base

| Classe      | Propósito                                         | Atributos Chave                  |
|-------------|----------------------------------------------------|----------------------------------|
| Produto     | Descreve o item vendido (preço fixo).             | nome, preco                      |
| ItemVenda   | Representa uma linha em uma venda (item e qtde).  | produto, quantidade              |
| Venda       | Representa a transação completa.                  | itensDaVenda (lista de ItemVenda)|


### 4.2 Padrão GRASP Criador

- O Criador define quem deve criar uma instância de ItemVenda.

- A classe Venda é o TODO (Todo) e ItemVenda é a PARTE. Pela regra do Criador, a classe Venda deve criar suas próprias ItemVenda.

```java title="Exemplo Criador"
// Venda é a classe TODO, responsável por criar a PARTE (ItemVenda)
class Venda {
    private List<ItemVenda> itensDaVenda;
    
    constructor() {
        this.itensDaVenda = new List<ItemVenda>();
    }

    // <-- APLICAÇÃO DO CRIADOR -->
    // Venda tem a responsabilidade de criar ItemVenda e adicioná-lo à sua lista.
    public void criarItemVenda(Produto produto, int quantidade) {
        // A classe Venda cria a instância de ItemVenda.
        ItemVenda novoItem = new ItemVenda(produto, quantidade); [cite: 75]
        this.itensDaVenda.add(novoItem);
    }
}

```

### 4.3 Padrão GRASP Especialista

- O Especialista define onde o método calcularTotal() deve residir.
- A responsabilidade de cálculo deve ser distribuída para as classes que são especialistas em cada parte da informação.

```java title="Exemplo Especialista"
// Venda é a classe TODO, responsável por criar a PARTE (ItemVenda)
class Produto {
    public string nome;
    public decimal preco; // Especialista em saber o preço

    constructor(nome, preco) {
        this.nome = nome;
        this.preco = preco;
    }
}

class ItemVenda {
    private Produto produto;
    private int quantidade; // Especialista em saber a quantidade

    constructor(produto, quantidade) {
        this.produto = produto;
        this.quantidade = quantidade;
    }

    // <-- APLICAÇÃO DO ESPECIALISTA (1) -->
    // ItemVenda é o especialista em saber seu próprio subtotal,
    // pois detém a 'quantidade' e tem acesso ao 'preço'.
    public decimal calcularSubTotal() {
        // Pede o preço ao objeto Produto e multiplica pela sua própria quantidade.
        return this.produto.preco * this.quantidade; 
    }
}

class Venda {
    // ... código do Criador (omissão) ...

    // <-- APLICAÇÃO DO ESPECIALISTA (2) -->
    // Venda é o especialista em calcular o total geral,
    // pois detém a coleção 'itensDaVenda'.
    public decimal calcularTotal() {
        decimal total = 0;
        
        // Venda itera sobre sua coleção e pede o subtotal a cada ItemVenda (o especialista).
        foreach (ItemVenda item in this.itensDaVenda) {
            total += item.calcularSubTotal();
        }
        return total;
    }
}

```