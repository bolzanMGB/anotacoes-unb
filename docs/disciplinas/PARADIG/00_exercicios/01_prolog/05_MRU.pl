mru(D, V, T) :-
    ( 
        ((var(D), var(V)) ; (var(V) , var(T)) ; (var(D) , var(T)))  ->
            write('erro: deve ter apenas 1 variavel'), fail
        ;
            true
    ),       

    (
        var(D) -> 
            D is V * T
        ;
        var(V) ->
            V is D / T
        ;
            T is D / V
    
    ).

