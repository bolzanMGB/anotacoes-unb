# Operadores em Haskell

## 1. Operadores Aritméticos

### 1. Funcionamento:

Podem ser escritos de forma fixada ou na forma infixada

```bash
Prelude> 1 + 2
3
Prelude> (+) 1 2
3
```

### 2. Operadores Básicos:

```bash
# Soma
Prelude> 5 + 3
8

# Subtração
Prelude> 5 - 3
2

# Multiplicação
Prelude> 3 * 4
12
```

### 3. Operadores de Divisão:

```bash
# Divisão fracionária
Prelude> 5 / 2
2.5

# Divisão inteira
Prelude> 5 `div`2
2

# Resto de divisão
Prelude> 5 `mod` 2
1
```
### 4. Operadores de Exponenciação

```bash
# ^ (Expoente inteiro positivo)
Prelude> 2 ^ 3
8
Prelude> 2.5 ^ 3
15.625
Prelude> 2.5 ^ (-3)
error
Prelude> 2 ^ 1.5
error

# ^^ (Expoente inteiro positivo/negativo)
Prelude> 2 ^^3
8.0
Prelude> 2.5 ^^ 3
15.625
Prelude> 2.5 ^^ (-3)
6.4e-2
Prelude> 2 ^^1.5
error

# ** (Expoente inteiro/fracionário positivo/negativo)
Prelude> 2 ** 3
8.0
Prelude> 2.5 ** 3
15.625
Prelude> 2.5 ** (-3)
6.4e-2
Prelude> 2.5 ** 1.5
3.952847075210474

```

## 2. Operadores Lógicos

```bash
# And
Prelude> True && True
True

# Or
Prelude> (1 < 0) || (1 == 1)
True

# Not
Prelude> not True
False
```

## 3. Operadores Relacionais

| Operação          | Operador | Exemplo no GHCi | Resultado |
|-------------------|----------|-----------------|-----------|
| Igual a           | `==`     | `5 == 5`        | `True`    |
| Diferente de      | `/=`     | `5 /= 3`        | `True`    |
| Menor que         | `<`      | `10 < 2`        | `False`   |
| Menor ou igual a  | `<=`     | `4 <= 4`        | `True`    |
| Maior que         | `>`      | `3 > 7`         | `False`   |
| Maior ou igual a  | `>=`     | `8 >= 5`        | `True`    |

Os operadores relacionais não são associativos, é necessário combinar operadores lógicos para encadeá-los.

```bash
ghci> 3 < 4 < 5
error

ghci> (3 < 4) && (4 < 5)
True
```

Também há como fazer comparação entre Caracteres e Strings

```bash
ghci> 'a' > 'b'
False
ghci> "AB" > "AC"
False
ghci> "AB" > "A"
True
```

## 4. Operadores de Igualdade

**1. Igualdade de Valores (== e /=)**

Servem para comparar se os valores de duas expressões são iguTais ou diferentes.

```bash
ghci> 'a' /= 'b'
True
ghci> "1" = '1'
error

ghci> 2 == 2
True
```

**2. Atribuição e Definição (=)**

Não é um operador de comparação, é usado para definir funções.

```bash
ghci> x = 10 + 2
ghci> x
12

```

**3. Definição de Tipos**

Funciona como uma igualdade de tipo

```bash
# arquivo.hs
banana :: String

# lê-se a variável vazia é do tipo String
```