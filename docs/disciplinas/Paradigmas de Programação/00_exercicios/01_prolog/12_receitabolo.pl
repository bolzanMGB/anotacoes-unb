% João deseja fazer bolos para seus amigos, usando uma receita que indica que devem ser usadas 
% 2 xícaras de farinha de trigo, 3 ovos e 5 colheres de sopa de leite. 
% Em casa ele tem A xícaras de farinha de trigo, B ovos e C colheres de sopa de leite.

% João não tem muita prática com a cozinha, e portanto ele só se arriscará 
% a fazer medidas exatas da receita de bolo 
% (por exemplo, se ele tiver material suficiente para fazer mais do que 2 e menos do que 3 bolos, 
% ele fará somente 2 bolos). 
% Sabendo disto, ajude João escrevendo um programa que determine 
% qual a quantidade máxima de bolos que ele consegue fazer.

% Entrada 
% A entrada é dada em uma única linha, que contém três números inteiros A, B e C, indicando respectivamente o 
% número de xícaras de farinha de trigo, o número de ovos 
% e o número de colheres de sopa de leite que João tem em casa.

% Saída
% Seu programa deve imprimir uma única linha, contendo um único inteiro, 
% a quantidade máxima de bolos que João consegue fazer.

% Restrições
% 1 ≤ A ≤ 100
% 1 ≤ B ≤ 100
% 1 ≤ C ≤ 100


bolo(F, O, L) :-
    F =< 100, F >= 1,
    O =< 100, O >= 1,
    L =< 100, L >= 1,

    X is F // 2,
    Y is O // 3,
    Z is L // 5,

    Lista = [X, Y, Z],

    min_list(Lista,M),
    write(M).