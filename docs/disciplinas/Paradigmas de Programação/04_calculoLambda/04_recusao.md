# Recursão

## 1. Teorema do Ponto Fixo

Para qualquer termo $G$, existe um termo $X$ tal que:

$$\mathbf{GX \equiv X}$$


## 2. Combinador Y

Para qualquer termo $G$, $YG$ é um ponto fixo de $G$, o que implica na equivalência: 

$$\mathbf{YG \equiv G(YG)}$$

## 3. Recursão

## 3.1 Estrutura Geral

$$
\gamma(x) =
\begin{cases}
g(x), & \text{se } P(x) \\
h(x,\gamma), & \text{caso contrário}
\end{cases}
$$

Onde:
* **$P(x)$**: é o predicado de teste do caso base.
* **$g(x)$**: é a função que dita a resposta do caso base (quando $P(x)$ for verdadeiro).
* **$h(x, \gamma)$**: é o passo recursivo (quando $P(x)$ for falso), que depende do parâmetro $x$ e da própria função $\gamma$.

**Exemplo: Fatorial**

$$
fat(n) =
\begin{cases}
1, & \text{se } n = 0 \\
n \cdot fat(n-1), & \text{se } n > 0
\end{cases}
$$

## 3.2 Em Cálculo Lambda

$$\Gamma\equiv \lambda \gamma x.(Px)(gx)(h)$$

Onde:

- 𝛾 é a chamada recursiva.
- x é o argumento

Assim:

```bash
if P(x)
   então g(x)
   senão h(x,γ)
```

**Exemplo: Fatorial**

$$\Gamma \equiv \lambda fx.(Zx)1(\times x(f(Px)))$$

Onde:
- f = função recursiva (equivalente ao nome fat)
- n = argumento da função
- Zn = testa se n é zero
- 1 = valor do caso base
- f(Pn) = chamada recursiva em n−1
- ×n(f(Pn)) = n×f(n−1)
