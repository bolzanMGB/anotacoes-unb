# Condicionais e Laços

## 1. Condicionais

## 1.1 Usando if then, else if, else

**Sintaxe:**

```haskell
nomeDaFuncao param = if condicao1 then valor1
                      else if condicao2 then valor2
                      else valor3
```

Onde:

- `condicao`é um bool.
- valores tem o mesmo tipo.
- `else`é obrigatório.

**Exemplo:**

```haskell  
ghci> x = 6
ghci> resultado = if x >= 5 then "Aprovado" 
                  else "Reprovado

ghci> resultado
"Aprovado"
```
## 1.2 Usando case 

**Sintaxe:**

```haskell
nomeDaFuncao param = case param of
                     valorParam1 -> retorno1 
                     valorParam2 -> retorno2 
                     _           -> retorno3 
```

**Exemplo:**
```haskell
statusDoDia dia = case dia of
                    1 -> "Fim de semana (Domingo)"
                    7 -> "Fim de semana (Sábado)"
                    _ -> "Dia útil de semana"
```

## 1.3 Usando Guardas

**Sintaxe:**

```haskell
nomeDaFuncao parametros
    | condicao1 = resultado1
    | condicao2 = resultado2
    | otherwise = resultadoPadrao
```

**Exemplo:**
```haskell
statusDoDia numeroDia  
    | (numeroDia) || (numeroDia) = "Fim de Semana"
    | numeroDia == 2 = "Segunda aff"
    | otherwise = "Dia da Semana"
```

## 2. Laços

Não existe laços kkk é necessário utilizar de Recursão.

**1. Capitalizar as palavras de uma string**

```haskell
import Data.Char

lower [] = [] -
lower (x:xy) = toLower x : lower xy

cap [] = []
cap (x:xy) = toUpper x : lower xy

capitalizar [] = [] 
capitalizar (x:xy) = cap x : capitalizar xy

ghci> capitalizar ["GAMA","AnAa", "famA"]
["Gama","Anaa","Fama"]
ghci> 
```

**2. Listar array de alunos que tem nota maior que 5**

```haskell
type Nome = String
type Nota = Float

data Aluno = Aluno Nome Nota deriving (Show)

a1 = Aluno "Pedro" 4
a2 = Aluno "Julio" 5
a3 = Aluno "Joao" 6

alunos = [a1,a2,a3]


listarAprovados [] = []
listarAprovados (Aluno nome nota:xy)
	| nota >= 5 = Aluno nome nota : listarAprovados xy
	| otherwise = listarAprovados xy 

ghci> listarAprovados alunos
[Aluno "Julio" 5.0,Aluno "Joao" 6.0]
```

## 3. Reduções

Pegam uma lista de vários elementos e a reduz a um único valor final.

```haskell
foldx (operacao) valorInicial lista
```

Pode ser:

- `foldl`: faz a operações começando da esquerda.
- `foldr`: faz a operações começando da direita.

Exemplo:


```bash
ghci> foldr (+) 0 [1..4]
10
ghci> foldr (-) 0 [1..4]
-2
```