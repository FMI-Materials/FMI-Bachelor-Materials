% Maze

connected(1,2).
connected(3,4).
connected(5,6).
connected(7,8).
connected(9,10).
connected(12,13).
connected(13,14).
connected(15,16).
connected(17,18).
connected(19,20).
connected(4,1).
connected(6,3).
connected(4,7).
connected(6,11).
connected(14,9).
connected(11,15).
connected(16,12).
connected(14,17).
connected(16,19).

path(X, Y) :- path(X, Y, []).
path(X, Y, _) :- connected(X,Y).
path(X, Y, L) :- connected(X, Z), not(member(Z, L)), path(Z, Y, [X, Z | L]).

plus(X, Y, R) :- append(X, Y, R).

times([], _, []).
times([x| Number1], Number2, Result) :- times(Number1, Number2, Result2),
    append(Result2, Number2, Result).

element_at([Head|_],1,Head).
element_at([_|List],Index,Result) :- NewIndex is Index - 1,
    element_at(List, NewIndex, Result).

/* Animal  database */

animal(alligator). 
animal(tortue) .
animal(caribou).
animal(ours) .
animal(cheval) .
animal(vache) .
animal(lapin) .

mutation(X) :- animal(Y), animal(Z), Y\==Z,
    name(Y, Ny), name(Z, Nz),
    append(Y1, Y2, Ny), Y1\==[],
    append(Y2, _, Nz), Y2\==[],
    append(Y1, Nz, LX), name(X, LX).