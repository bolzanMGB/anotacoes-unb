
## 2. Listas em Prolog

Uma lista é um conjunto de termos ou de outras listas que é atada a um predicado.

**Sintaxe Básica:** Representada entre colchetes:

> [termo1, termo2, ..., termoN].

**Exemplo:**

```prolog
% Banco de Fatos

% Um fato onde o argumento é uma lista
precos([10, 20, 30, 40]).

% Um fato com dois argumentos, sendo um deles uma lista
estoque(frutas, [maca, banana, laranja]).
```

### 2.2 Notação Header/Tail

Embora tenha uma sintaxe especial, uma lista é, de fato, um predicado de dois argumentos: um head e um tail.

Head (H): É um termo, o primeiro elemento da lista.

Tail (T): É uma lista contendo todos os demais elementos.

**Exemplo:**

```prolog
?- [H|T] = [1,2,3,4,5].
H = 1,
T = [2, 3, 4, 5].

```

### 2.3. Predicados Matemáticos e de Manipulação

#### 2.3.1 length/2
Calcula o número de elemento da lista e insere em uma variável

**Exemplo:**

```prolog
?- length([a, b, c, d], Tamanho).
Tamanho = 4.
```

**Possível Implementação:**
```prolog
% Banco de Fatos
length_([_|T], X) :- length_(T, NewX), X is NewX + 1.
length_([], 0).

% Terminal
?- length_([a, b, c, d], Tamanho).
Tamanho = 4.

```

#### 2.3.1 member/2

Verifica se algo pertence à lista, chegando o Head e percorrendo recursivamente o Tail.

> member(elemento, lista).

**Exemplo:**
```prolog
?- member(b, [a, b, c]).
true .

?- member(X, [a, b, c]).
X = a ;
X = b ;
X = c.

?- member(_, [a, b, c]).
true .

?- member(1, [a, X, c]).
X = 1 .

```

**Possível Implementação:**
```prolog
% Banco de Fatos
member_(H, [H|_]).
member_(X, [_|T]) :- member_(X, T).

?- member_(b, [a, b, c]).
true .
```


#### 2.3.2 append/3

Anexa a segunda lista à primeira. Também é usado para decompor uma lista em todas as combinações possíveis de prefixos e sufixos.

> append [listaA, listaB, novaLista].

**Exemplo:**
```prolog
?- append([a, b ,c], [1, 2, 3], L).
L = [a, b, c, 1, 2, 3].

?- append([a], [1], a).
false.
% Nesse caso, o prolog tenta unificar [a, 1] com a

?- append([a, b ,X], [1, 2, 3], A).
A = [a, b, X, 1, 2, 3].

```

**Possível Implementação:**
```prolog
% Banco de Fatos
append([], X, X).
append([H|T1], X, [H, T2]) :-
    append(T1, X, T2).

```

**Exemplo de decomposição por meio do append:**

```prolog
?- append(X, Y, [1, 2, 3, 4]).
X = [],
Y = [1, 2, 3, 4] ;
X = [1],
Y = [2, 3, 4] ;
X = [1, 2],
Y = [3, 4] ;
X = [1, 2, 3],
Y = [4] ;
X = [1, 2, 3, 4],
Y = [] ;
false.
```

#### 2.3.3 findall/3

Usado para encontrar todos os valores que satisfazem um objetivo e agrupá-los em uma lista resultante. Primeiro argumento é o que você quer encontrar, o segundo a regra que de ve ser satisfeita e o terceiro a variável onde lista com resultados sera guardada.

> findall(N, regra(_,N), novaLista).

**Exemplo:**
```prolog
% Banco de Fatos

nota(joao, 7).
nota(maria, 5).
nota(cleber, 3).

% Terminal
?- findall (N, regra(_,N), X)
X = [7,5,3].
```

#### 2.3.4 asserta/1 e assertz/1
Permite que o programa aprenda novos fatos enquanto está rodando. Assim, É possível transformar uma lista de termos em fatos reais na memória. O "asserta" coloca no inicio e o "assertz" no final


> asserta(termo).
> assertz(termo).

**Exemplo:**
```prolog
% Banco de Fatos
:- dynamic animal/1.
animal(cachorro).
animal(gato).

% Terminal 1
?- assertz(animal(leao)).
true.

?- animal(X).
X = cachorro ;
X = gato ;
X = leao.

% Terminal 2
?- asserta(animal(leao)).
true.

?- animal(X).
X = leao;
X = cachorro ;
X = gato.
```

**Exemplo de declaração de fato com assertz:**

```prolog
list_to_facts([H|T]) :- 
    assertz(H),        % Transforma o item H em um fato real 
    list_to_facts(T).  % Continua para o resto da lista 
```

#### 2.3.4 maplist/N
É um predicado que atua como um iterador sincronizado sobre múltiplas listas. 

> maplist (funcao, lista1, ..., listaN).

- Ele recebe um predicado de N argumentos e N listas de mesmo comprimento X.
- Após isso, O Prolog percorre as listas simultaneamente, extraindo o elemento de cada posição e aplicando-os como argumentos ao predicado fornecido.
- Se todas as listas estiverem preenchidas, ele atua como um validador: retorna true se a relação for válida para todos os elementos.

**Exemplo:**

```prolog
% Banco de Fatos
soma(A, B, C, D) :- D is A + B + C.

% Terminal
?- maplist(soma, [1,2], [1,2], [1,2], [3,6]).
true.

% Explicação
soma (1,1,1,3) :- 3 is 1+1+1. 
true.
soma (2,2,2,6) :- 6 is 2+2+2. 
true.

true.
```

Porém, se pegarmos a última lista, que seria de resultado, e trocarmos por uma variável, conseguimos armazenar o resultado:

**Exemplo:**

```prolog
% Banco de Fatos
soma(A, B, C, D) :- D is A + B + C.

% Terminal
?- maplist(soma, [1,2], [1,2], [1,2], R).
R = [3,6].

% Explicação
soma (1,1,1,R) :- R is 1+1+1. 
R = 3.
soma (2,2,2,R) :- R is 2+2+2. 
R = 6.

R = [3,6].
```
#### 2.3.5 numList/3

Recebe dois número, N e M, e gera uma lista com todos os inteiros no intervalo de N a M. Sua sintaxe é:

> numList(N, M, lista).


**Exemplo:**

```prolog
% Terminal
numList(1,5,L).
L = [1, 2, 3, 4, 5].
```

#### 2.3.5 include/3

- Recebe uma regra, uma lista N e uma lista M.
- Vai aplicar a regra em cada elemento da lista N, caso  o objetivo der true o elemento fica na lista, caso der false ele sai.
- A lista N é comparada com a lista M, caso unificar dar true.
- Caso a lista M for uma variável, vai retornar a lista N filtrada somente com os elementos que passaram na regra.

> include(Goal, List, Filtered).

**Exemplo:**
```prolog
% Banco de Fatos
is_odd(X) :- mod 2 =/= 0.

odds(L, Odds) :- include(is_odd, L, Odds)

% Terminal
?- odds([1,2,3,4,5,6],L).
L = [1, 3, 5].


```


#### 2.3.6 exclude/3

- Mesma coisa do include, porém vai deixar sos elementos para os quais o objetivo falha.

> include(Goal, List, Filtered).

**Exemplo:**
```prolog
% Banco de Fatos
is_odd(X) :- mod 2 =/= 0.

odds(L, Odds) :- include(is_odd, L, Odds)
evens(L, Evens) :- exclude(is_odd, L, Evens).

% Terminal
?- evens([1,2,3,4,5,6],L).
L = [2, 4, 6].

```

#### 2.3.7 foldl/N

Ele vai aplicar o predicado ao primeiro item da lista, somá-lo ao valor inicial e colocá-lo no resultado, fazendo isso na lista inteira.

> foldl(funcao,[1,...,N],valorInicial,Resultado)

```prolog
% Banco de Fatos
soma(X, total, NovoTotal) :- NovoTotal is total + X.

% Terminal
?- foldl(soma,[1,2,3,4,5],0,R).
R = 15.
```

#### 2.3.8 scanl

Mesma coisa do foldl, porém registra os passos intermediários

```prolog
% Banco de Fatos
soma(X, total, NovoTotal) :- NovoTotal is total + X.

% Terminal
?- scanl(soma, [1, 2, 3], 0, Historico).
Historico = [0, 1, 3, 6].
```
