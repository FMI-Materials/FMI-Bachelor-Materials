:- ensure_loaded("01").
:- ensure_loaded("05").
:- ensure_loaded("06").

all_evals(X, As):- 
    vars(X, S), evs(S, Es), evals(X, Es, As).