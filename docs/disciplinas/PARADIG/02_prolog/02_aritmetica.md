
## 8. Aritmética 

Operadores são predicados que suportam, além da pré-fixada padrão, as notações infixada ou pós-fixada.

### 8.1 Operadores Customizados

Operadores são predicados que suportam, além da pré-fixada padrão, as notações infixada ou pós-fixada.

Há operadores padrões em prolog, porém podemos nos mesmos declarar operadores através da sintaxe:

> :- op(Precedencia, Tipo, Nome).

Além disso, podemos citar todos os operados com

> current_op(P, T, O).

e pagar um operador definindo a precedência dele como 0:

> :- op(0, xfx, nome_do_operador).

#### 8.1.1 Precedência: 
Define a ordem de importância. Varia de 0 a 1200, quanto menor, maior a força.

- Exemplo: A multiplicação (*) tem precedência 400 e a soma (+) tem 500. Por isso, em 2 + 3 * 4, o Prolog resolve primeiro o *.

#### 8.1.2 Tipo

Usa de letras para representar o operador (f) e os argumentos (x e y).

**1. Posição** 
F representa onde o nome do predicado aparece. Exemplos:

```prolog
Prefixado: fx, fy.
:- op(200, fx, nota).
?- nota 10.

Infixado: xfx, xfy, yfx.
:- op(200, xfx, ganha_de). 
?- pedra ganha_de tesoura.

Pós-fixado: xf, yf.
:- op(200, xf, eh_bonito). 
?- joao eh_bonito.
```
**2. Associatividade**

X é rígido, Y é flexível

**2.1 Infixo Rígido (xfx):** Não pode repetir o operador na mesma frase.

```prolog
:- op(500, xfx, mae_de).

ana mae_de bia.
true.

ana mae_de bia mae_de caio.
ERRO
```

**2.2 Infixo Associativo à Direita(xfy):** O y está na direita, então ele permite que o operador se repita "empilhando" para a direita.

Exemplo: se temos um operador "e" que é xfy, então "sol e chuva e vento" é lido como e(sol, e(chuva, vento)).

Exemplo: Se temo um operador "+" que é yfx, então "1 + 2 + 3" é lido como: +(+(3,2),1).
**2.2 Infixo Associativo à Esquerda(yfx):** O y está na esquerda, então ele "empilha" para a esquerda.

Exemplo: se temos um operador "e" que é xfy, então "sol e chuva e vento" é lido como e(e(sol,chuva), vento).

Exemplo: Se temo um operador "+" que é yfx, então "1 + 2 + 3" é lido como: +(+(1, 2), 3).


#### 8.1.2 Exemplos


**Jokenpô**

```prolog
% Precedência 700 (comum para comparações)
% Tipo xfx (Infixado, não permite 'pedra ganha_de tesoura ganha_de papel')

:- op(700, xfx, ganha_de).

pedra ganha_de tesoura.
tesoura ganha_de papel.
papel ganha_de pedra.


venceu(Jogador1, Jogador2) :-
    Escolha1 ganha_de Escolha2,
    escreve_resultado(Jogador1, Escolha1, Jogador2, Escolha2).
```

### 8.2 Operadores de Igualdade e Unificação

| Operador | Nome | O que faz? | Exemplo |
| :--- | :--- | :--- | :--- |
| `=` | xfx | Tenta unificar de acordo com a aridade | **Unificação**: Tenta tornar os termos iguais (vincula variáveis). |
| `==` | xfx | Verifica a igualdade literal | **Identidade**: Verdadeiro se os termos são exatamente iguais (sem vincular). |
| `=:=` | xfx | Verifica igualdade matematica. Não funciona com variáveis | **Igualdade Aritmética**: Os valores numéricos são iguais? |


#### 8.2.1 Operador de Unificação (=)
Ele tenta unificar os dois lados. É um processo de tentativa de tornar os dois termos idênticos, inclusive atribuindo valores a variáveis se necessário.

```prolog
?- X = Y.
X = Y.

?- 2 + 2 = 2 + 2.
true.

?- 2 + 2 = 4.
false.

?- 2 + X = Y + a.
X = a,
Y = 2.

?- X = 2 + 2.
X = 2+2.



```

#### 8.2.2 Operador de Identidade Literal (==)
Ele verifica a equivalência estrita. Ele não tenta mudar nada; ele apenas olha para os dois lados e pergunta: "Vocês são exatamente iguais agora?"

```prolog
?- X == Y.
false.

?- 2 + 2 == 2 + 2.
true.

?- 2 + 2 == 4.
false.

?- 2 + X == Y + a.
false

```

#### 8.2.3 Operador de Igualdade Aritmética (=:=)
É um operador de comparação. ELe não guarda os valores, apenas verifica se os dois cálculos chegam ao mesmo número.

```prolog
?- X =:= Y.
ERROR

?- 2 + 2 =:= 2 + 2.
true.

?- 2 + 2 =:= 4.
true.

?- 2 + X =:= Y + a.
false

```

### 8.3 Operador de Atribuição Aritmética (is)

Ele se comporta como uma unificação do "=" com o "=:=" e possui dois usos:

- Com uma variável na esquerda: ele olha para o lado direito, resolve o cálaculo e colocar o resultado na variável da esquerda.
- Com números na esquerda: ele vai checar se o resultado do lado direito é igual o da esquerda.

```prolog

?- X is 2 + 2.
X = 4.

?- 2 is 2.
true.

?- 4 is 2 + 2.
true.

?- 2 + 2 is 4.
false.

?- _ is 1 + 1.
true.

```

### 8.4 Operadores de Diferença e Não-Unificação

| Operador | Tipo | Precedência | Descrição |
| :--- | :--- | :--- | :--- |
| `\=` | xfx | 700 | **Não Unificável**: Verdadeiro se os termos não podem ser unificados. |
| `\==` | xfx | 700 | **Não Idêntico**: Verdadeiro se os termos não são estritamente iguais. |
| `=\=` | xfx | 700 | **Diferença Aritmética**: Os valores numéricos são diferentes? |

### 8.5 Operadores de Comparação Numérica

| Operador | Tipo | Precedência | Descrição |
| :--- | :--- | :--- | :--- |
| `>` | xfx | 700 | Maior que |
| `<` | xfx | 700 | Menor que |
| `>=` | xfx | 700 | Maior ou igual que |
| `=<` | xfx | 700 | Menor ou igual que |


### 8.3 Funções  Aritméticas

Ao invés de atar o resultado a uma variável, elas retornam o valor das suas operações. Para usá-los, é necessário:

1. Carregar a biblioteca de aritmética:

> se_module(library(arithmetic))

2. Definifir a função aritmética:

> :- arithmetic_function(nome_funcao/N).

3. Definir a variávela a ser retornada:

> :- arithmetic_function(nome_variavel/N).


**Exemplo:**

```prolog
:- use_module(library(arithmetic)).

% Declara os predicados como funções aritmética. Note que a aridade declarada
% é uma unidade menor do que a aridade usada na definição do predicado, e que a
% última variável conterá o valor de 'retorno'
:- arithmetic_function(number_of_lines/1).
:- arithmetic_function(juros_simples/3).

number_of_lines(N, Res) :- Res is 2^N.

juros_simples(M, J, T, Res) :-
    Res is M * (1 + J * T).

% Terminal
?- X is 1 + number_of_lines(4).
X = 17.
?- X is juros_simples(1000, 0.05, 60).
X = 4000.0.

```

### 8.4 Predicados com múltiplas semânticas

A bidirecionalidade é uma das características principais do prolog. Nele, não definimos funções, e sim relações que funcionam de acordo com os argumentos passados. Por exemplo:

```prolog

?- succ(2,S).
S = 3.

?- succ(S,2).
S = 1.

```

#### 8.4.1 Implementação

O predicado var/1 retornar verdadeiro se a varíavel é livre, e o predicado nonvar retorna verdadeiro se já foi atada previamente na consulta. Exemplo:

```prolog
celsius_fahrenheit(C, F) :-
    ((var(C), var(F)) -> 
        instantiation_error('Ao menos uma variável deve estar atada') 
    ; 
        true),
    (nonvar(C) -> 
        F is C*9/5 + 32 
    ; 
        C is (F - 32)*5/9).

% Exemplos de consultas
?- celsius_fahrenheit(40, F).
F = 104.
?- celsius_fahrenheit(C, 104).
C = 40.
?- celsius_fahrenheit(100, 100).
false.
?- celsius_fahrenheit(32, F).
F = 89.6.
```



