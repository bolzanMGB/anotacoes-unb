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

> $a(x) \mid_x b(x)$

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

**1. Combinador Identidade (I):**

Apenas devolve o argumento

> Ix = x

**2. Combinador Constância (K):**

Ele ignora o segundo argumento

> Kxy = x


**3. Combinador Intercâmbio (T):**

Ele troca a ordem dos argumentos

> T fxy = fyx

**4. Combinador Composição (Z):**

Ele aplica uma função ao resultado de outra função

> Z f(x) = f(g(x))

**5. Combinador Fusão (S):**

Ele aplica o arugmentos em duas funções ao mesmo tempo

> S fgx = f(x) g(x)