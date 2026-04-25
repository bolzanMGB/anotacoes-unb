% Normal

fib(0,0).
fib(1,1).

fib(N,R) :-
    N > 1,
    succ(N1, N),
    succ(N2, N1),
    fib(N1, R1),
    fib(N2, R2),
    R is R1 + R2.
    

    



% De calda

fib(N, R) :- fibAUX(N, 0, 1, R).

fib(0, Acc1,_, Acc1).

fibAUX(N,Acc1, Acc2,R) :-
    N > 0,
    succ(N1,N),
    Acc3 is Acc1 + Acc2,

    fibAUX(N1,Acc2, Acc3, R).

fib(5, 0, 1, R) Acc3=1
fib(4, 1, 1, R) Acc3=2
fib(3, 1, 2, R) Acc3=3
fib(2, 2, 3, R) Acc3=5
fib(1, 3, 5, R) Acc3=5
fib(1, 5, 5, R) Acc3=5
fib(0, 5, 5, 5) 

0 0
1 1
2 1
3 2
4 3
5 5


