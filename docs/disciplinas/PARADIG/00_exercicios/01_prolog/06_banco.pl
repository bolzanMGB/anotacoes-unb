analisa_credito(Idade, Salario, Emprestimo) :-
    (
        Idade =< 18 ->
            write('Negado'), fail
        ; 
            true
    ),

    (
        (Emprestimo / 2) =< (Salario * 0.3) ->
            write('aceito'), true
        ;
            write('negado'), fail
    ).