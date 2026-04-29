pai(ze, ana).
pai(ze, rui).
pai(rui, bia).
pai(rui, leo).

mulher(ana).
mulher(bia).

homem(ze).
homem(rui).
homem(leo).

avo(X,Y) :- 
    homem(X),
    pai(Z,Y),
    pai(X,Z).

irmao(X,Y) :-
    homem(X),
    pai(Z,X),
    pai(Z,Y).

tia(X,Y) :-
    mulher(X),
    pai(W,Z),
    pai(W,X),
    pai(Z,Y).



