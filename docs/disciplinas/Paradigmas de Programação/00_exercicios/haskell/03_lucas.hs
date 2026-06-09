in_lucas x = x `elem` [2,1,3,4,7,11,18,29,47,76]

count_lucas x = length (filter in_lucas x)

main =  print $ count_lucas [1..20]


A func¸ao˜ count_lucas :: [Int] -> Int
recebe uma lista de inteiros xs, cujos elementos pertencem ao intervalo [1, 100], e retorna quantos, dentre os elementos de xs, sao n ˜ umeros de Lucas. ´
Os numeros de Lucas ´ Ln sao tais que ˜ L0 = 2,
L1 = 1 e Ln = Ln−1 + Ln−2, se n ≥ 2.
Exemplos de chamada (o retorno se encontra no
comentario correspondente): ´
1 count_lucas [1, 2, 1, 2] -- 4
2 count_lucas [6, 8, 10] -- 0
3 count_lucas [1..20] -- 7
