# Recursão em Prolog

## 1. Definição
O Prolog resolve problemas quebrando-os em instâncias menores de si mesmos até chegar a um fato conhecido. Cada vez que o Prolog faz uma chamada recursiva, ele coloca essa "pergunta" em uma pilha de execução para resolvê-la depois.

**Caso Base:** É o fato que interrompe a recursão. Sem ele, o programa entra em "loop infinito" (até estourar a memória).

**Caso Recursivo:** É a regra que contém uma chamada para si mesma, geralmente aproximando o problema do caso base.

## 1. Implementação Recursiva Normal
Nesse tipo a chamada recursiva não é a última coisa que a regra faz. O prolog precisa "voltar" para terminar o cálculo após a recursão retornar um valor.

```prolog
fact(N, F) :-
    N > 0,
    succ(NewN, N),
    fact(NewN, F1), % Chamada recursiva
    F is F1*N.  % O Prolog AINDA precisa multiplicar após a volta


fact(0, F) :- F is 1. % Caso Base
```
## 2. Implementação Recursiva de Calda
Aqui, a chamada recursiva é a última operação da regra. O Prolog pode descartar o estado da chamada anterior da memória, pois não há nada "sobrando" para fazer depois.

**O Acumulador:** Para transformar uma recursão normal em cauda, usamos uma variável extra (o acumulador) para levar o resultado parcial "adiante".

```prolog

factorial(N, F) :- factTR(N, 1, F). % Chama a função auxiliar

factTR(0, Acc, F) :- F is Acc.% Caso base: devolve o que acumulou

factTR(N, Acc, F) :-
    N > 0,
    succ(NewN, N),
    NewAcc is Acc * N,
    factTR(NewN, NewAcc, F).
```
## 3. Características da Recursão

- Cada nível de recursão tem seu próprio conjunto de variáveis
- A unificação entre o objetivo e o padrão de uma regra recursiva definem as relações entre as variáveis de diferentes níveis
- Em uma regra recursiva, é preciso garantir que os parâmetros não caracterizem uma dentre as cláusulas-base
- Sem esse cuidado, um retorno pela porta redo em alguma das subconsultas da regra pode fazer com que, eventualmente, um conjunto de valores que caracteriza uma cláusula-base avance na regra recursiva, causando erros de execução como laços infinitos

## 4. Estrutura de Dados em Prolog
Diferente de linguagens imperativas, em Prolog as estruturas são formas de agrupar informações relacionadas. Sua declaração e sintaxe é idêntica a um fato:

> array(arg1, arg2, ..., argN) 

### 4.1 Consultas

Para detalhar os pontos, vamos considerar que a nossa base de dados é composta pelo seguinte fato:

> car(ford, azul, 2023).

**Ordem dos Argumentos:** Ela influencia no resultado. O prolog compara a posição exata de cada termo.

```prolog
% Consulta correta
?- car(ford, azul, 2023).
true.

% Consulta incorreta
?- car(azul, ford, 2023).
false.
```

**Variável Anônima (_):** É usada para ignorar campos que não interessam na consultas.

```prolog
% Cenário: Você quer saber se existe algum carro da cor azul, mas não se importa com a marca ou ano.
?- car(_, azul, _).
```

**Aninhamento (Nesting):** Estruturas podem ser aninhadas, ou seja, colocadas uma dentro da outra.

```prolog
% Em vez de termos uma estrutura simples, como:
car(honda, civic, 2022, manual, 4).

% Podemos organizar em uma estrutura aninhada:
car(honda, model(civic, 2022), specs(manual, doors(4))).
```

