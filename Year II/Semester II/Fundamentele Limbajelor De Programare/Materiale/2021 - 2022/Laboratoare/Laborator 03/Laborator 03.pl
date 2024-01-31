squareAux(N,N,N,C) :- write(C).
squareAux(I,N,N,C) :- write(C), nl, Aux is I+1, squareAux(Aux, 1, N, C).
squareAux(I,J,N,C) :- write(C), Aux is J+1, squareAux(I,Aux,N,C).

square(N,C) :- squareAux(1,1,N,C).

% verifica daca elementul se afla in lista
element_of(X,[X|_]).
element_of(X,[_|Tail]) :- element_of(X,Tail).

% concateneaza listele
concat_lists([], List, List).
concat_lists([Elem | List1], List2, [Elem | List3]) :- concat_lists(List1, List2, List3).

% exerictiul 3
% verifica daca toate elementele din lista sunt a
all_a([a | List]) :- all_a(List).
all_a([]).

% verifica daca prima lista are doar a si a doua lista
% are doar b si cele doua liste sunt egale
trans_a_b([a | List1], [b | List2]) :- trans_a_b(List1, List2).
trans_a_b([], []).

% inmulteste lista cu scalarul dat ca parametru
scalarMult(n, [h:t], [n * h | [] ]) :- scalarMult(n, [t], []).
scalarMult(n, [h:t], [n * h | X]) :- scalarMult(n, [t], X).

scalarMult(_, [], []).
scalarMult(X, [Y | List], [Z | Result]) :- Z is X*Y, scalarMult(X, List, Result).