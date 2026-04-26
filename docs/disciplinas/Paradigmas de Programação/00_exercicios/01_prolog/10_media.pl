somar(X, T, NT) :- NT is T + X.

media(Lista, Media) :-
    foldl(somar, Lista, 0, T),
    length(Lista, X),
    Media is T / X.

