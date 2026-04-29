% Tarefa: Crie uma regra recomendacao(Nome, Categoria) que sugira um filme se:
% Ele for da Categoria solicitada OU se ele for um "Clássico" (lançado antes de 2005, independente da categoria

filme(oppenheimer, drama, 2023).
filme(barbie, comedia, 2023).
filme(shrek, animacao, 2001).
filme(matrix, ficcao, 1999).
filme(parasita, drama, 2019).


recomendacao(Nome,Categoria) :-
    filme(Nome, X, Y),
    (X = Categoria; x < 2005).