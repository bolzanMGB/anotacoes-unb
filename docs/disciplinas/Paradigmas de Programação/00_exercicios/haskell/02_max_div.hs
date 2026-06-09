aux n m = 
        if n `mod` m == 0 then m
        else aux n (m - 1)

max_div x = aux x (x - 1)

main =  print $ max_div 100


A func¸ao˜ max_div :: Int -> Int recebe
como parametro um inteiro ˆ x positivo e retorna o
maior divisor positivo de x menor do que x.
