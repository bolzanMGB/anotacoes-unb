# Aritmética de Church

É uma forma de representar números naturais e operações matemáticas usando apenas funções. 

## 1. Definição

Os Numerais de Church representam quantas vezes uma função `s`é aplicada sobre um argumento/valor inicial `z`.

$$\mathbf{n = \lambda sz.s^n(z)}$$

## 2. Números

**Definição de 0:** Aplica `s` 0 vezes.

$$\mathbf{0 = \lambda sz.z}$$

**Definição de 1:** Aplica `s` 1 vezes.

$$\mathbf{1 = \lambda sz.s(z)}$$

**Definição de 2:** Aplica `s` 2 vezes.

$$\mathbf{2 = \lambda sz.s(s(z))}$$

## 3. Pares

Pares são guardados através da expressão:

$$\mathbf{(a,b) \equiv \lambda z.zab}$$

E podem ser extraidos Usando T ou F:

$$\mathbf{\lambda (z.zab)T \equiv} Tab \equiv a$$

$$\mathbf{\lambda (z.zab)F \equiv} Fab \equiv b$$

## 4. Função Z

Ela verifica se um número de church é 0.

$$\mathbf{Zx \equiv \lambda x.x FT}$$

**Exemplo: x = 0**

$$\mathbf{0FT \equiv (\lambda sz.z)FT \equiv T}$$

## 5. Função Sucessor (S)

Função que aplica `n + 1`vezes `s` em `z`.

$$\mathbf{Sw = \lambda wyx.y(w(yx))}$$

$$\mathbf{sendo: \, w = n, \, y=s, \, x=z}$$

$$\mathbf{Sn = \lambda nsz.s(n(sz))}$$

**Exemplo: Sucessor de zero**

$$\mathbf{S0 = (\lambda nsz.s(n(sz)))\equiv_{\beta} n[\lambda sz.z]}$$

$$\mathbf{\lambda sz.s((\lambda sz.z)(sz))}$$

$$\mathbf{\lambda sz.s(z) \equiv 1}$$


## 6. Função Antecessor (P)

$$\mathbf{Pn \equiv (\lambda n.)}$$

É uma função que recebe um número natural `n` e aplica nele dois argumentos: 

- O combinador $\Phi$: uma função que recebe um par ordenado (X, Y) e retorna (Y, Y + 1)
- Uma função que recebe um booleano e um par ordenado. 

e em cima de tudo isso aplica um False.


**Exemplo**

$$\mathbf{P3 \equiv ((\lambda n.n\Phi(\lambda z.z00)F)3)}$$
$$\mathbf{\equiv (3 \Phi(\lambda z.z00))F}$$
$$\mathbf{\equiv (\lambda sz.s(s(s(z))))(\Phi(\lambda z.z00)F)}$$
$$\mathbf{\equiv (Φ(Φ(Φ(λz.z00))))F}$$
$$\mathbf{\equiv (Φ(Φ(λz.z10)))F}$$
$$\mathbf{\equiv (Φ(λz.z21))F}$$
$$\mathbf{\equiv (λz.z32)F}$$
$$\mathbf{\equiv 2}$$

## 7. Comparações

### 7.1 Desigualdade (G)

$$\mathbf{G \equiv \lambda xy.Z(xPy)}$$

### 7.1 Igualdade (E)

$$\mathbf{E \equiv \lambda xy.\wedge(Z(xP y))(Z(yP x))}$$

## 8. Operações

### 8.1 Adição (+)

$$\mathbf{(+) \equiv \lambda xy.xSy}$$

### 8.2 Multiplicação (X)

$$\mathbf{(X)\equiv \lambda xyz.x(yz)}$$


