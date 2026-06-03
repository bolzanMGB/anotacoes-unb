# Tipos de Dados em Haskell

## 1. Introdução

Em Haskell há interferência de tipos, você raramente precisa declarar os tipos.

A assinatura de um tipo ocorre pelo operador `::`

```bash
expression :: Type
```

Já a verificação de um tipo ocorre pelo comando `:type`

```bash
Prelude> :type 5
5 :: Num a => a
```

## 2. Tipos de dados

**1. Caractere:**
É um caractere delimitado por uma aspa simples

```bash
Prelude> 'a'
```

**2. String:**
É uma lista compostas por caracteres delimitada por aspas duplas.

```bash
Prelude> "Exemplo de String"

Prelude> "ABC" == ['A', 'B', 'C']
True
```
**3. Bool:**

Representa valores lógicos: `True` ou `False`.

**4. Int:**

Inteiros com tamanho limitado.

**5. Integer:**

Inteiros grades, sem limite prático.

**6. Float:**

Número quebrados com precisão simples.

**7. Double:**

Número quebrados com precisão dupla.

## 3. Listas

Agrupa valores de um mesmo tipo. São delimitadas por colchetes e seus elementos sao separados por vírgulas.

```bash
Prelude> "" == []
True

Prelude> "A1!" == ['A','1','!']
True

Prelude> "1..5" == ['1','2','3','4','5']

Prelude> "1..5" == ['1','2','3','4','5']
False
Prelude> "1..5" == ['1','.','.','5']
True

Prelude> [1..5]
[1,2,3,4,5]
Prelude> ['1'..'5']
"12345"

Prelude> ['a'..'z']
"abcdefghijklmnopqrstuvwxyz"
Prelude> ['A'..'Z']
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
```

## 3. Variáveis 

Variáveis começam com letra minúscula, enquanto tipos começam com letra maiúscula.

As variáveis em haskell são imutáveis, ou seja, valores não são guardados na memória para usar depois. Se no GHCi você redefinir uma variável "x" ele não vai dar erro ou modificar o "x" antigo, ele vai criar um novo "x" no escopo atual que esconde a definição anterior

```bash
ghci> x = 10
ghci> x
10
ghci> x = 12
ghci> x
12
ghci>  X = 10
```

## 5. Tuplas

Agrupa valores de tipos diferentes 