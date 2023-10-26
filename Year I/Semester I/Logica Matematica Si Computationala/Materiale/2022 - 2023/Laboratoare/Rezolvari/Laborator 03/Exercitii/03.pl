atimes(_, [], 0).
atimes(N, [N|T], X):- 
    atimes(N, T, Y), X is Y + 1.
atimes(N, [H|T], X):- 
    atimes(N, T, X), N \== H.