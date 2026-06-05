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

## 7. Variáveis 

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

Agrupa valores de tipos diferentes. É delimitada por parenteses e os elementos são separados por vírgulas.

```bash
ghci> aluno = ("Joao", 18, 1.80, True)
ghci> aluno
("Joao",18,1.8,True)
```

## 6. Definir Novos Tipos de Dados (Classes)


### 6.1 Sintaxes

**Sintaxe 1**

```haskell
data NomeDoTipo =  ConstrutorDeValor TipoDoAtributo1 TipoDoatributo2 ... TipoDoAtributoN
```

Exemplo:

```haskell
data StudentInfo = createStudent String Int Double deriving show
s1 = createStudent "Joao" 20 1.80
```
**Sintaxe 2**

```haskell
data NomeDoTipo = ConstrutorDeValor{
    nomeDoAtributo1 :: TipoDoAtributo1,
    nomeDoAtributo2 :: TipoDoAtributo2,
    ...
    nomeDoAtributoN :: TipoDoAtributoN
}
```

Exemplo:

```haskell
data Estudante = criarEstudante {
    nome :: "Joao",
    idade :: 20,
    altura :: 1.80
}
```

## 6.2 Sacadas

### 6.2.1 Sinônimos

```haskell
type Nome = String
type Idade = Int
type Altura = float

data Aluno = Aluno Nome Idade Altura
```

### 6.2.2 Mais de um Construtor


```haskell
data Forma = Circulo Float
           | Quadrado Float Float
           | Null
c1 = Circulo 5
q1 = Quadrado 5 5
```


### 6.2.3 Null e Maybe

Em Haskell não existe Null. Então para resolver isso é utilizado um construtor sem atributos, dessa forma podemos criar dados sem nada ou retornar nada. Na documentação do Haskell se usa essa sintaxe aqui.

```haskell
ghci> data Maybe a = Just a | Nothing deriving (Show)
ghci> n1 = Just 1
ghci> n1
Just 1
ghci> n2 = Just "A"
ghci> n2
Just "A"
ghci> n3 = Nothing
ghci> n3
Nothing
``` 

### 6.2.4 Variáveis como coringas

- Variáveis podem ser usadas como tipo de atributo coringa.
- Por padrão se usa o `a`.
- Ele pode receber qualquer formato,

**Sintaxe:**

```haskell
data NomeDoTipo a = Construtor a 
```

**Exemplo 1:**

```haskell
ghci> data Pessoa a = Const a
ghci> data Pessoa a = Const a deriving (Show)
ghci> p1 = Const 2
ghci> p1
Const 2
ghci> p1 = Const "Letra"
ghci> p1
"Letra"
```

**Exemplo 2:**

```haskell
ghci> data Node a = Const a (Node a) | Null deriving (Show)
ghci> n1 = Const 12 Null
ghci> n1
Const 12 Null
ghci> n2 = Const 20 n1
ghci> n2
Const 20 (Const 12 Null)
ghci> n3 = Const "String" n2
error
```

Aqui deu Erro pq a estrutura virou uma lista e em listas os elementos devem seguir o mesmo formato.