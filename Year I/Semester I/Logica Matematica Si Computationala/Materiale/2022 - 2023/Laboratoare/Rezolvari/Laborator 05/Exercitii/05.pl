:- ensure_loaded("04").

evals(_, [], []).
evals(X, [E|Et], [A|At]):-
    eval(X, E, A), evals(X, Et, At).