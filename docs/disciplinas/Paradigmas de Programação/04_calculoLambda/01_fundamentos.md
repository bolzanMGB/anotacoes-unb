# Fundamentos de Cálculo Lambda

## 1. Termos-$\lambda$ básicos

### 1.1 Variáveis:

Iniciam com letras minúscula. Exemplo: x,y,z

**1. Variáveis atadas:** São precedida por $\lambda$.

**2. Variável Livre:** Caso contrário.

**Exemplo**

$$\mathbf{\lambda x.xy}$$

- x é atada.
- y é livre.



### 1.2 Expressões

- Iniciam com letra maiúscula.
- Exemplo: M, N, P

### 1.3 Aplicações

Uma aplicação é aplicar uma expressão em outra. Uma aplicação pode ser uma variável, termo lambda etc. Ela é associativa a esquerda.

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

$\lambda x.(\lambda y.y)x$
- Função que recebe x e retorna o resultador de aplicar o x como argumento numa função que recebe y e retorna y.

## 2. Axiomas de Redução e Substituição

## 2.1 Substituição

$$\mathbf{M[x:=N]}$$

Se lê "Substituir x por N dentro de M", onde:
- M = expressão onde a substituição será feita.
- x = variável a ser procurada.
- N = expressão que vai entrar no lugar de x.

**Exemplo:**

$$\mathbf{xz[x:=y]}$$
$$\mathbf{yz}$$

## 2.2 Conversão Alfa

$$\mathbf{\lambda x.M \equiv_{\alpha} \lambda y.(M[x:=y])}$$

Muda o nome de uma variável ligada sem mudar o significado da função.

**Exemplo:**

$$\mathbf{\lambda x.xy \equiv_{\alpha} \lambda z.(M[x:=x])}$$

$$\mathbf{\lambda z.zy}$$

## 2.3 Redução Beta

Executa a função substituindo o argumento x por N em M

$$\mathbf{(\lambda x.M)N \equiv_{\beta} M[x:=N]}$$

**Exemplo:**


$$\mathbf{(λx.x)y \equiv_{\beta} x[x:=y]}$$
$$\mathbf{y}$$

## 2.4 Conversão Eta
Remove funções que apenas repassam argumentos. A variável do parâmetro não pode aparecer livre em M.

$$\mathbf{(\lambda x.Mx) \equiv_{\eta} M}$$


## 3. Combinadores e Igualdade Extensional

**Combinador:** É qualquer expressão em que todas variáveis são atadas

**Igualdade Extensional:** Quando dois combinadores produzem o mesmo resultado ao receberem o mesmo argumento. Exemplo:

$$\mathbf{\lambda x.xx \, = \, \lambda y.yy}$$

$$\mathbf{ou}$$

$$\mathbf{\lambda x.(Fx) \, = \, F}$$