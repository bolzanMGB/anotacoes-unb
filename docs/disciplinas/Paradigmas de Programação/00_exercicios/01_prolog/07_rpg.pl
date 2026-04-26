% Você foi contratado para programar o núcleo de cálculo de danos de um jogo de RPG em Prolog. No jogo, o dano causado por um ataque depende da arma equipada, e cada arma tem uma fórmula matemática diferente baseada em dois atributos do personagem.

% Regras das Armas (Crie essas regras):

% - espada(Forca, Destreza, Dano): O dano é o dobro da Força somado com a Destreza.
% - arco(Forca, Destreza, Dano): O dano é o triplo da Destreza somado com a divisão inteira (//) da Força por 2.
% - cajado(Inteligencia, Mana, Dano): O dano é a Inteligência multiplicada pelo resto da divisão (mod) da Mana por 10.

% A Ação Principal (O Meta-predicado):
% Você deve criar um predicado atacar(Arma, Atrib1, Atrib2) que recebe o nome da regra da arma (a função) e os dois atributos do jogador.

% Tarefa:

% - Declare atacar como um meta-predicado (ele vai invocar a arma passada por parâmetro).
% - intro de atacar/3, use o predicado call para calcular o Dano da arma.
% - Use a estrutura condicional ( If -> Then ; Else ) para avaliar o resultado:
%     - Se o Dano calculado for maior ou igual a (>=) 50, escreva na tela: 'Ataque CRITICO! Dano: ' seguido do valor.
%     - Caso contrário, escreva: 'Ataque normal. Dano: ' seguido do valor.:- use_module(library(arithmetic)).

% Exemplo de uso esperado no terminal:

% ?- atacar(espada, 20, 15).
% Ataque CRITICO! Dano: 55
% true.

% ?- atacar(arco, 15, 10).
% Ataque normal. Dano: 37
% true.

% ?- atacar(cajado, 8, 25).
% Ataque normal. Dano: 40
% true.

% Começa Aqui

% :- arithmetic_function(dano_espada/2).
% :- arithmetic_function(dano_arco/2).
% :- arithmetic_function(dano_cajado/2).

arma(espada).
arma(cajado).
arma(arco).

dano_espada(Forca, Destreza, Dano) :- Dano is (2 * Forca) + Destreza.

dano_arco(Forca, Destreza, Dano) :- Dano is 3 * Destreza + (Forca // 2).

dano_cajado(Inteligencia, Mana, Dano) :- Dano is Inteligencia * mod(Mana,10).

% :- meta_predicate atacar(2, *, *).

espada(F, DE) :-
    dano_espada(F, DE, DA),
    
    (
        DA >= 50 ->
            write('Ataque CRITICO! '),
            write('Dano: '),
            write(DA)
        ;
            write('Ataque normal! '),
            write('Dano: '),
            write(DA)
            
    ).

arco(F, DE) :-
    dano_arco(F, DE, DA),
    
    (
        DA >= 50 ->
            write('Ataque CRITICO! '),
            write('Dano: '),
            write(DA)
        ;
            write('Ataque normal! '),
            write('Dano: '),
            write(DA)
            
    ).

cajado(F, DE) :-
    dano_cajado(F, DE, DA),
    
    (
        DA >= 50 ->
            write('Ataque CRITICO! '),
            write('Dano: '),
            write(DA)
        ;
            write('Ataque normal! '),
            write('Dano: '),
            write(DA)
            
    ).

atacar(Arma, Atrib1, Atrib2) :-
    arma(Arma),
    call(Arma, Atrib1, Atrib2).
   