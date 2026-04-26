:- dynamic item/1.

item(arroz).
item(feijao).

adicionar(X) :-
    assertz(item(X)).

remover(X):-
    retract(item(X)).

listar :-
    write('Item: '), item(X), write(X), nl,
    write('Item: '),
    fail.



