% Crie um predicado nota(X) que:
% Se a Nota for >= 5.0, escreva "Aprovado".
% Caso contrário, escreva "Reprovado".

nota(X) :-
    (X < 5) -> 
                write('Reprovado')
            ;
                write('Aprovado').