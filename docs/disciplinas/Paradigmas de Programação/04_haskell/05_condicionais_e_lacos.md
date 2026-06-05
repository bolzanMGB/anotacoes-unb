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