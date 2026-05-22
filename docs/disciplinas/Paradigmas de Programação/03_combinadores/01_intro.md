# Introdução

## 1. Histórico da Lógica Booleana

### 1.1 Conectivos da Lógica Proposional Booleana

| Operação | Leitura | Definição |
| :---: | :---: | :--- |
| $\overline{a}$ | não a | Inverte o valor lógico de a |
| $a \lor b$ | a ou b | Falso apenas se a e b são ambos falsos |
| $a \land b$ | a e b | Verdadeiro apenas se a e b são ambos verdadeiros |
| $a \to b$ | se a, então b | Falso apenas se a é verdadeiro e b é falso |
| $a \sim b$ | a é equivalente a b | Verdadeiro se ambos têm o mesmo valor lógico |

### 1.2 Redução Tradicional (Linguagens de Programação)

> Usando os primitivos  $\overline{a}$,  & e $\lor$.

|    Operação    | Equivalência                                        |
| :------------: | :-------------------------------------------------- |
| $\overline{a}$ | $\overline{a}$                                        |
|   $a \lor b$   |  $a \lor b$                                         |
|   $a \land b$  | $a \land b$                                        |
|    $a \to b$   | $\overline{a} \lor b$                               |
|   $a \sim b$   | $(\overline{a} \lor b) \land (\overline{b} \lor a)$ |


### 1.3 Redução de Whitehead e Russel

> Usando os primitivos  $\overline{a}$ e $\lor$.

|    Operação    | Equivalência                                                                                     |
| :------------: | :----------------------------------------------------------------------------------------------- |
| $\overline{a}$ | $\overline{a}$                                                                                 |
|   $a \lor b$   | $a \lor b$                                                                     |
|   $a \land b$  | $\overline{(\overline{a} \lor \overline{b})}$                                                    |
|    $a \to b$   | $\overline{a} \lor b$                                                                            |
|   $a \sim b$   | $\overline{\left(\overline{(\overline{a} \lor b)} \lor \overline{(\overline{b} \lor a)}\right)}$ |


### 1.4 Redução de Scheffer

Usando os primitivos:

> - Negação Conjunta (↓): Verdadeiro somente quando ambas preposições são falsas.
> - Negação Disjunta (↑): Falsa somente quando ambas preposições são verdadeiras.

|    Operação    | Equivalência                                                                             |
| :------------: | :--------------------------------------------------------------------------------------- |
| $\overline{a}$ | $a \uparrow a$                                                                           |
|   $a \lor b$   | $(a \downarrow b) \downarrow (a \downarrow b)$                                           |
|   $a \land b$  | $(a \uparrow b) \uparrow (a \uparrow b)$                                                 |
|    $a \to b$   | $a \uparrow (b \uparrow b)$                                                              |
|   $a \sim b$   | $\left(a \uparrow (b \uparrow b)\right) \uparrow \left(b \uparrow (a \uparrow a)\right)$ |

## 2. Reduções de Schönfinkel


### 2.1 Reduções Lógicas

Schönfinkel eliminou a necessidade de vários conectivos, agora é necessário apenas um único operador.

**Conectivo de Incompatibilidade de Schönfinkel:**

> $$\mathbf{a(x) \mid_x b(x)}$$

Isso significa que para todo $x$, as propriedades $a(x)$ e $b(x)$ são incompatíveis: só vão ser verdadeiras se pelo menos uma delas for falsa

| $a$ | $b$ | $a \mid_x b$ |
| :---: | :---: | :---: | 
| V | V | Falso| 
| V | F | Verdadeiro | 
| F | V | Verdadeiro | 
| F | F | Verdadeiro | 

**Exemplos:**

| Operação | Equivalência Schönfinkel| Processo |
| :---: | :---: | :---: |
| $\overline{a}$ | $(a \mid_x a)$ | |
| $a \lor b$ | $(a \mid_x a) \mid_x (b \mid_x b)$ | $a \lor b = \overline{a} \mid_x \overline{b} = (a \mid_y a) \mid_x (b \mid_y b)$ |
| $a \land b$ | $(a \mid_x b) \mid_y (a \mid_x b)$ | $a \land b = \overline{(a \mid_x b)} = (a \mid_x b) \mid_y (a \mid_x b)$ |


### 2.2 Reduções de Funções

Schönfinkel eliminou a necessidade de funções com variáveis, provando que qualquer função complexa pode ser quebrada utilizando combinadores.

**1. Combinador Identidade / Identity Bird (I):**

Apenas devolve o argumento

> $$\mathbf{Ix = x}$$

**2. Combinador Constância / Kestrel Bird (K):**

Ele ignora o segundo argumento

> $$\mathbf{K \ x \ y = x}$$


**3. Combinador Intercâmbio (T ou C):**

Ele troca a ordem dos argumentos

> $$\mathbf{C \ x \ y \ z = x z y}$$

**4. Combinador Composição / Bluebird (Z ou B):**

Ele aplica uma função ao resultado de outra função

> $$\mathbf{B \ x \ y \ z = x(yz)}$$

**5. Combinador Fusão / Starling (S):**

Ele aplica o arugmentos em duas funções ao mesmo tempo

> $$\mathbf{S \ x \ y \ z = x z (y z)}$$


### 2.3 Cálculo SK

Schönfinkel demonstrou que toda computação poderia ser representada utilizando apenas funções de um argumento e combinadores.

Posteriormente, observou-se que todos os combinadores poderiam ser reduzidos apenas aos combinadores S e K, formando o chamado cálculo SK.

O cálculo SK é um sistema computacional minimalista onde:

- Todos os objetos são funções unárias;
- Existem apenas duas primitivas: S e K;
- A computação ocorre por aplicação sucessiva de funções;
- Os parênteses apenas controlam a ordem de avaliação.

**Combinador K:** Ignora o segundo argumento e retorna o primeiro.
> $$\mathbf{K \ x \ y = x}$$

**Combinador S:**

Aplica o mesmo argumento em duas funções diferentes.

> $$\mathbf{S \ x \ y \ z = x z (y z)}$$

### 2.4 Redução Beta

No cálculo SK, a avaliação das expressões ocorre da esquerda para a direita, aplicando funções somente quando há argumentos suficientes. Esse processo é chamado de redução beta.


**Exemplo:**

> $$\mathbf{K \ A \ B = A}$$

O combinador K recebe dois argumentos e retorna apenas o primeiro, descartando o segundo.

**Outro exemplo:**

> $$\mathbf{S \ f \ g \ x = f(x)(g(x))}$$

Primeiro o argumento $x$ é aplicado em $f$ e $g$, depois os resultados são combinados.

## 3. Cálculo Lambda ($\lambda$)

Enquanto Schönfinkel baseava-se em combinadores, Alonzo Church propôs, na década de 1930, o cálculo $\lambda$ para formalizar a noção de computabilidade. É considerado a menor linguagem de programação do mundo, focada em regras de transformação e no esquema de definição de funções. Qualquer função computável em uma máquina de Turing pode ser expressa no cálculo $\lambda$.  

### 3.1 Termos Lambda
O conjunto das expressões, denotado por $\Lambda$, possui apenas três regras fundamentais baseadas em variáveis (pertencentes a um conjunto $V$): 

1. **Variável:** $x \in V \Rightarrow x \in \Lambda$ (expressão atômica).  

2. **Aplicação:** $M, N \in \Lambda \Rightarrow M N \in \Lambda$ (equivale à avaliação de $M(N)$).  

3. **Abstração:** $M \in \Lambda, x \in V \Rightarrow \lambda x.M$ (equivale à definição de uma função $f(x) = M$).  

### 3.2 Variáveis Livres e Atadas

1. **Atada (Bound):** A abstração $\lambda x.M$ "ata" a variável $x$ ao termo $M$.  

2. **Livre (Free):** Uma variável que não é precedida por um símbolo $\lambda$ que a una à expressão. Em $\lambda x.xy$, $x$ é atada e $y$ é livre.

### 3.3 Axiomas de Redução e Conversão

O cálculo possui regras estritas para processar computações:

1. **Conversão-$\alpha$:** Permite renomear uma variável atada para evitar colisões de nome. 
> $$\mathbf{\lambda x.M \equiv_\alpha \lambda y.(M[x:=y])}$$

2. **Redução-$\beta$:** Estabelece a aplicação da função através da substituição. O termo aplicado substitui as variáveis livres correspondentes. 
> $$\mathbf{(\lambda x.M)N \equiv_\beta M[x:=N]}$$

3. **Conversão-$\eta$:** Elimina redundâncias quando o propósito é apenas repassar um argumento. Se $x$ não é livre em $M$.
> $$\mathbf{\lambda x.Mx \equiv_\eta M }$$
   