# Fundamentos de Cálculo Lambda

## 1. Termos-$\lambda$ básicos

### 1.1 Variáveis:

Iniciam com letras minúscula. Exemplo: x,y,z

**Variáveis atadas:** São precedida por $\lambda$.

**Variável Livre:** Caso contrário.


### 1.2 Expressões

- Iniciam com letra maiúscula.
- Exemplo: M, N, P

### 1.3 Aplicações

Uma aplicação é aplicar uma expressão em outra. Ela é associativa a esquerda.

**Exemplo 1:**

- Se
    - M=λx.x
    - N=y
- Então
    - MN = (λx.x)(y)
    - Se lê: usar M como função e N como argumento.
    - Retorna y.

**Exemplo 2:**

- Se:
    - M = λx.x
    - N = λy.y
    - P = λz.z
- Então:
    - MNP = (MN)P = ((λx.x)(λy.y))(λz.z)
    - Se lê: N usado como argumento em M em P aplicado ao resultado disso.
- Passo a Passo:
    - R1 = (λx.x)(λy.y) = λy.y
    - R2 = (λy.y)(λz.z) = λz.z

### 1.4 Abstrações

Abstrações são os mecanismos para representar funções. Elas são associativas a direita.


$\lambda x.M$ 
- Função que recebe o argumento x e produz M.

$\lambda x.x$ 
- Função que recebe o argumento x e devolve x.

$\lambda x.\lambda y.xy$ = $\lambda x.(\lambda y.xy)$ 
- Função que recebe x e devolve uma função que recebe y e devolve uma função que recebe z que devolve uma função que recebe xyz.

## 2. Axiomas de Redução e Substituição

## 2.1 Substituição

$$\mathbf{M[x:=N]}$$

- M = expressão onde a substituição será feita.
- x = variável a ser procurada.
- N = expressão que vai entrar no lugar de x.