/*
bnon(0, 1). 
bnon(1, 0).
bsi(1, 1, 1).
bsi(_, _, 0).
bsau(0, 0, 0).
bsau(_, _, 1).
bimp(1, 0, 0).
bimp(_, _, 1).
*/

bnon(X, R):-
    R is 1 - X.
bimp(X, Y, 1):-
    X =< Y.
bimp(X, Y, 0):-
    X > Y.
bsi(X, Y, R):- 
    bnon(Y, NY), bimp(X, NY, IXY), bnon(IXY, R).
bsau(X, Y, R):-
    bnon(X, NX), bimp(NX, Y, R).