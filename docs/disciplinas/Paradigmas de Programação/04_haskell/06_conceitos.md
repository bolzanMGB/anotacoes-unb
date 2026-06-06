# Conceitos

## 1. Currying

- Todas as funções em Haskell só recebem um único parâmetro.
- O funcionamento de um função com três parâmetros é:
    - Recebe primeiro parâmetro e devolve uma nova função.
    - Essa nova função recebe o segundo parâmetros e devolve outra função.
    - Essa terceira função recebe o último parâmetro e devolve o resultado.

Ao passar apenas alguns parâmetros e salvar essa função em uma variável, essa nova função agora só precisa dos parâmetros restantes. Exemplo

```bash
ghci> take 3 [1,2,3,4,5]
[1,2,3]
ghci> take3 take 3
ghci> take3 [1,2,3,4,5]
[1,2,3]
```

## 2. Composição de funções

É possível criar uma nova função combando outras funções através do `.`. Exemplo

```bash
ghci> capCount = length . filter (isUpper . head) . words
ghci> capCount "Paradigmas de Programação" 
2
```

## 3. Operador de Aplicação de função

o `$` tem a menor precedência possível em haskell. Ele é utilizado para não precisar usar parenteses. Exemplo:

```bash
main = print (sqrt (abs (-25)))
main = print $ sqrt $ abs (-25)
```