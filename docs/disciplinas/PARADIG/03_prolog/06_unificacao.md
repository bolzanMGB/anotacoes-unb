# Processos de Unificação

## 1. Unificação de Termos

Retorna true se todos os argumentos unificarem.

```prolog
?- a = a.
true.

?- a = b.
false.

?- x(y, z(i, j)) = x(y, z(i, j)).
true.

?- x(y, z(i, j)) = x(y, z(j, i)).
false.

? 2 + 2 = 4.
false.
```

## 2. Unificação de Variáveis e Termos Primitivos

Ao unificar com um termo primitivo, a variável é atada ao seu valor.

```prolog
?- X = a.
X = a.

?- 2 = Y.
Y = 2.

?- f(x, y) = f(X, y).
X = x.

?- f(x, y) = f(X, z).
false.

?- f(x, y) = f(X, Y).
X = x.
Y = y.
```

## 3. Unificação entre Variáveis


Duas variáveis sempre unificam.

```prolog
?- A = B.
A = B.

?- f(X, y) = f(Z, y).
X = Z.

?- X = Y, Y = teste.
X = Y, Y = teste.

?- X = Y, a(Z) = a(Y), X = teste.
X = Y, Y = Z, Z = teste.

?- X = Y, Y = 2, write(X).
2
X = Y, Y = 2.
```

## 4. Unificação em Consultas Compostas
A variável anônima ‘_’ é um wildcard e não é atada a valor algum.

O predicado \=/2 retorna verdadeiro se os seus argumentos não unificam.

```prolog
?- f(X) \= f(x, y).
true.

?- f(x, y, z) = f(_, _, z).
true.
```
