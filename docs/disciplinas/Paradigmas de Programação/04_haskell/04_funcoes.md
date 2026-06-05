# Funções em Haskell

## 1. Sintaxe e Definição

**1. Sintaxe**
Não utiliza parêntesis para delimitar parâmetros.

`nome_da_funcao param1 param2 ... paramN`

Parâmetros só são utilizados para resolver ambiguidades.

`compare (sqrt 5) (sqrt 3)`

**2. Definição de função:**

```bash
ghci> dobro x = x * 2
ghci> dobro 5
10
```

**3. Definição de função anônima**

```bash
ghci> (\x -> x + 10) 5
15
```
**3. Assinatura de Tipo**

É uma boa prática em haskell. Ela diz os tipos que a função recebe e retorna. Sem ela o haskell usa o Type Inference: advinha os tipos, funciona bem em funções simples.

```bash
ghci> somar :: Int -> Int -> Int
ghci> somar a b = a + b
ghci> somar 5 10
15
```

## 2. Funções para Listas 

Lembrando que:

- Strings são listas de caracteres.
- Tuplas com o mesmo tipo e mesmo número de argumentos também podem ser usadas.

### 2.1 Funções de Modificação

**1. reverse [a, b, c]**

```bash
ghci> reverse [1, 2, 3]
[3, 2, 1]
ghci> reverse "gama"
"amag"
```

**2. init [a, b ,c] e tail [a, b, c]**

```bash
ghci> init [1, 2, 3, 4]
[1, 2, 3]

ghci> tail "palavra"
"alavra"
```

**3. [a, b] ++ [c, d]**

```bash
ghci> [1,2] ++ [2,3]
[1,2,2,3]

ghci> "Gama" ++ "Brasilia"
"GamaBrasilia"
```

**4. [a, b] \\ [c, d]**

```bash
ghci> import Data.List
ghci> [1,2,4] \\ [1]
[2,4]

ghci> "Gama eh DF" \\ "Gama"
" eh DF"
```

**5. take x [a,bc] e drop x [a,b,c]**

```bash
ghci> take 5 [1..10]
[1,2,3,4,5]
ghci> take 2 "Gama"
"Ga"

ghci> drop 5 [1..10]
[6,7,8,9,10]

```

### 2.3 Funções de Busca


**1. head [a, b, c] e last [a, b, c]**

```bash
ghci> head [1,2,3,4]
1
ghci> last "Gama"
'a'
```

**2. a `elem` [a, b, c]**

```bash
ghci> 1 `elem` [1,2,3]
True

ghci> 'G' `elem` "Gama"
True
ghci> 'Ga' `elem` "Gama"
error
```

**3. maximum [a,b,c] e minimum [a,b,c]**

```bash
ghci> maximum [4, 9, 2, 7]
9

ghci> minimum "unb"
'b'
```

**4. null [a,b,c]**

Retorna verdadeiro se a lista está vazia e falso, caso contrário

### 2.4 Funções de Alta Ordem

Funções que recebem outra função como parâmetro para processar a lista.

**1. map (\entrada -> saida) [a, b, c]**

Aplica a função em cada um dos elementos e retorna uma nova lista com os resultados

```bash
ghci> map (\x -> x * 2) [1, 2, 3]
[2, 4, 6]
```

**2. filter (\entrada -> saida) [a, b, c]**

Filtra a lista, mantendo apenas os elementos que satisfazem a condição da função (retornam True).

```bash
ghci> filter (\x -> x > 3) [1, 2, 3, 4, 5, 6]
[4, 5, 6]
```

### 2.4 Funções Matemáticas em Listas

**1. sum [x,y,z]**

```bash
ghci> sum [1,2,3]
6
ghci> sum [1..5]
15
```

**2. product [x,y,z]**

```bash
ghci> product [1,2]
2
ghci> product [1..3]
6
```

### 2.5 Funções de Junção e Separação de Lista

**1. zip [a,b,c] [x,y,z]**

Pega duas listas e as combina em uma lista de tuplas. Se uma lista for maior que a outra, o Haskell corta os elementos excedentes de forma segura.

```bash
ghci> zip [1,2,3] ['a','b','c']
[(1,'a'),(2,'b'),(3,'c')]
ghci> zip ["gama"] [1,2,3]
[("gama",1)]
```

**2. unzip [(a,b,c) (x,y,z)]**

Faz o processo inverso. Pega uma lista de tuplas de dois elementos e a transforma em um par de duas listas distintas. A lista deve ter exatamente duas tuplas e o tipo dos pares (1° item da 1° e 2° tuplas e 2° item da 1° e 2° tupla) devem ser do mesmo tipo

```bash
ghci> unzip [("mae",1), ("pai",2)]
(["mae","pai"],[1,2])

ghci> unzip [(1,'a'), (2)]
error


ghci> unzip [(1,'a'), (2,3)]
error
```

## 3. Funções para Strings/Caracteres

### 3.1 Funções de Conversão

Usam `import Data.Char`

**1. toUpper 'a' e toLower 'b'**

```bash
ghci> toUpper 'a'
'A'
ghci> map toLower "GaMA esTA NO df"
"gama esta no df"
```

### 3.2 Funções de Verificação

Usam `import Data.Char`

**1. isUpper 'a' e isLower 'b'**

```bash
ghci> isUpper 'a'
False
ghci> filter isLower "GaMA esTA NO df"
"aesdf"
```

**2. isAlpha [a] e isDigit [b]**

```bash
ghci> isAlpha 'a'
True

ghci> isDigit 'a'
False

ghci> filter isAlpha "Gama2026DF2025"
"GamaDF"
```

**3. isSpace 'a'**

Retorna True se um espaço, False se não for.

### 3.3 Funções de Formatação de Texto

**1. words "abcd" e unwords "abcd"**

```bash
ghci> words "gama df"
["gama","df"]

ghci> unwords ["Gama", "esta", "no", "DF", "2026"]
"Gama esta no DF 2026"
```

**2. lines "Linha 1\nLinha 2" e unlines ["linha 1", "linha 2"]**

```bash
ghci> lines "Linha 1\nLinha 2"
["Linha 1","Linha 2"]
ghci> unlines ["Linha 1", "Linha 2"]
"Linha 1\nLinha 2\n"
```