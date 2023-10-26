:- ensure_loaded("07").

all_ones([]).
all_ones([1|T]):- 
    all_ones(T).
taut(X):- 
    all_evals(X, As), all_ones(As).