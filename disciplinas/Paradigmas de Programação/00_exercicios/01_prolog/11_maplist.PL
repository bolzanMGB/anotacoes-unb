% Imagine que seu personagem deu um golpe de área e atingiu 
% vários monstros.
% monstros_vida([100, 80, 50, 30]).

% Tarefa: Crie um predicado 
% aplicar_dano(ListaVidas, Dano, NovasVidas).
% Se o Dano for 20, a lista [100, 80, 50, 30] 
% deve virar [80, 60, 30, 10].

aux(Dano, Vida, NovaVida) :- NovaVida is Vida - Dano.

aplicarDano(ListaVida, Dano, NovaVida) :-
    maplist(aux(Dano, ListaVida, NovaVida)).