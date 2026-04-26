
% Tarefa: Crie um predicado itens_caros(ListaItens, ListaFiltrada) 
% que recebe uma lista de nomes de itens e retorna 
% apenas aqueles que custam mais de 30.

item(espada, 50).
item(escudo, 30).
item(pocao, 10).
item(cajado, 45).

aux(Nome) :-
    item(Nome, Preco), Preco > 30.


eh_caro(Lista, ListaFiltrada) :-
include(aux, Lista, ListaFiltrada).