# Programação Funcional

## 1. O que é

A programação funcional é caracterizada pelo **Paradigma Declarativo**.
- **Paradigma Declarativo:** Os programadores devem declarar "o que" o programa deve fazer. Ele prioriza o fluxo de dados.
- **Paradigma Imperativo**: Os programadores devem declarar "como" o programa deve fazer. Ele prioriza o fluxo de controle.

**Exemplo de Código Imperativo (C/Java)**
```C
int soma = 0;
for (int i = 0; i < tamanho; i++) {
    soma += lista[i];
}
```

**Exemplo de Código Declarativo (Haskell)**
```C
soma = sum lista
```

## 2. Características

A programação funcional trata a comutação como a valoração de funções matemáticas e possui fundamento no **Cálculo Lambda**. As principais características que ancoram a linguagem incluem:

**1. Variáveis imutáveis:**

- Variáveis não podem ser modificadas após sua inicialização.
- Variáveis são amarradas a uma função.
- Não levam problemas de concorrência.

**2. Funções de primeira classe:**

- Funções são tratadas como tipos de dados:
    - Podem ser passada como argumento em outras funções.
    - Podem ser guardadas em estrutura de dados.

**3. Funções puras:**

- Uma função tem efeito colateral quando ela, além de computar o valor de retorno, modifica o estado do programa:
    - Altera variáveis globais.
    - Escrita ou leitura de periféricos.
- Funções em haskell são puras, ou seja, não possuem efeitos colaterais.

**4. Valoração não-estrita:**

- Expressões são calculadas apenas quando são requisitadas, não quando são atribuídas.

**5. Tipagem de Dados Forte e Estática:** 

- Regras são estritas e resolvidas em tempo de compilação.
- Se houver erros, eles são reconhecidos na hora da compilação, não na execução.

**6. Lazy-Evaluation:**
- No caso de um operador And, por exemplo, se a primeira expressão for False, Haskell não avalia a segunda expressão, pois o resultado final será obrigatoriamente False.

## 3. Mecanismos

**1. Currying**

- Todas as funções em Haskell só recebem um único parâmetro.
- O funcionamento de uma função com três parâmetros é:
    - Recebe primeiro parâmetro e devolve uma nova função.
    - Essa nova função recebe o segundo parâmetros e devolve outra função.
    - Essa terceira função recebe o último parâmetro e devolve o resultado.

Ao passar apenas alguns parâmetros e salvar essa função em uma variável, essa nova função agora só precisa dos parâmetros restantes. Exemplo:

```bash
ghci> take 3 [1,2,3,4,5]
[1,2,3]
ghci> take3 take 3
ghci> take3 [1,2,3,4,5]
[1,2,3]
```

**2. Composição de Funções**

Inspirado na matemática, o operador de ponto permite encadear funções. O resultado (retorno) da função à direita vira automaticamente o parâmetro de entrada da função à esquerda

```bash
ghci> capCount = length . filter (isUpper . head) . words
ghci> capCount "Paradigmas de Programação" 
2
```

**3. Operador de Aplicação:**

o `$` tem a menor precedência possível em haskell. Ele é utilizado para não precisar usar parenteses. Exemplo:

```bash
main = print (sqrt (abs (-25)))
main = print $ sqrt $ abs (-25)
```

**4. Pattern Matching**

Quando você define uma função usando Pattern Matching, o programa confronta a entrada com os padrões de cima para baixo, na sequência em que foram escritos. Ele para e executa a primeira linha que "casar" perfeitamente com o argumento recebido.  Um excelente exemplo é a função matemática de fatorial:  Haskell-- Padrão 1: Se a entrada for exatamente 0, retorne 1.

```bash
factorial 0 = 1

-- Padrão 2: Se a entrada for qualquer outro número 'n', aplique a recursão.
factorial n = n * factorial (n - 1)
```

## 4. Como usar

**1. Instalação:**

```bash
$ sudo apt install ghc
```


**2. Executar:**

```bash
$ ghci
prelude>
```

**3. Carregar Arquivo:**

```bash
prelude> :l nomeArquivo.hs
```

**4. Sair**

```bash
prelude> :q
```
