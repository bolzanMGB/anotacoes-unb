% Normal

fib(0,0).
fib(1,1).

fib(N,R) :-
    succ(N1, N),
    succ(N2, N1),
    fib(N1, R1),
    fib(N2, R2),
    R is R1 + R2.
    
