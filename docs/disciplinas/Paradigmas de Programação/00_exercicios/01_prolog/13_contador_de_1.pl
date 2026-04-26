% O predicado count1s/2 recebe como
% parametros uma lista ˆ L de inteiros e um variavel ´
% X (nesta ordem) e retorna verdadeiro, atando X ao
% numero de ocorr ´ encias do n ˆ umero 1 em ´ L

so1(X) :- X = 1.


count1s(L, X) :-
    include(so1, L, L2), 
    length(L2, X).
    