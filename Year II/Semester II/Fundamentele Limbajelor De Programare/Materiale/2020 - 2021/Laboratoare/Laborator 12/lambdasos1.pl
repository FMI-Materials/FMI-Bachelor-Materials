:- op(100,xfy,or).
:- op(100,xfy,and).
:- op(200,yfx,$).


remove(Env, X, Env1) :-
    select((X,_), Env, Env1),!.
remove(Env, _, Env).

set(Env, X, T, [(X,T) | Env1]) :-
    remove(Env, X, Env1).
get(Env, X, T) :-
    member((X, T), Env).

% Rules for +
step(Env, A + B, A1 + B) :-
    step(Env, A, A1).
step(Env, A + B, A + B1) :-
    step(Env, B, B1).
step(_, I1 + I2, I) :-
    integer(I1),
    integer(I2),
    I is I1 + I2.

% Rules for -
step(Env, A - B, A1 - B) :-
    step(Env, A, A1).
step(Env, A - B, A - B1) :-
    step(Env, B, B1).
step(_, I1 - I2, I) :-
    integer(I1),
    integer(I2),
    I is I1 - I2.

% Rules for *
step(Env, A * B, A1 * B) :-
    step(Env, A, A1).
step(Env, A * B, A * B1) :-
    step(Env, B, B1).
step(_, I1 * I2, I) :-
    integer(I1),
    integer(I2),
    I is I1 * I2.

% Rules for /
step(Env, A / B, A1 / B) :-
    step(Env, A, A1).
step(Env, A / B, A / B1) :-
    step(Env, B, B1).
step(_, I1 / I2, I) :-
    integer(I1),
    integer(I2),
    I is I1 / I2.

% Rules for <
step(Env, A < B, A1 < B) :-
    step(Env, A, A1).
step(Env, A < B, A < B1) :-
    step(Env, B, B1).
step(_, I1 < I2, B) :-
    integer(I1),
    integer(I2),
    I1 < I2
    ->  B = true
    ;   B = false.

% Rules for =<
step(Env, A =< B, A1 =< B) :-
    step(Env, A, A1).
step(Env, A =< B, A =< B1) :-
    step(Env, B, B1).
step(_, I1 =< I2, B) :-
    integer(I1),
    integer(I2),
    I1 =< I2
    ->  B = true
    ;   B = false.

% Rules for >=
step(Env, A >= B, A1 >= B) :-
    step(Env, A, A1).
step(Env, A >= B, A >= B1) :-
    step(Env, B, B1).
step(_, I1 >= I2, B) :-
    integer(I1),
    integer(I2),
    I1 >= I2
    ->  B = true
    ;   B = false.

% Rules for not
step(Gamma, not(B), not(B1)) :-
    step(Gamma, B, B1).
step(_, not(true), false).
step(_, not(false), true).

% Rule for identifiers
step(Env, X, V) :-
    atom(X), get(Env, X, V).

% Rules for and
step(Env, A and B, A1 and B) :-
    step(Env, A, A1).
step(Env, A and B, A and B1) :-
    step(Env, B, B1).
step(_, false and _, false).
step(_, _ and false, false).
step(_, true and true, true).

% Rules for ;
step(Env, A ; B, C) :-
    step(Env, A, A1)
    ->  C = (A1 ; B)
    ;   C = B.

% Rules for if
step(Env, if(B, S1, S2), if(B1, S1, S2)) :-
     step(Env, B, B1).
step(_, if(true, S1, _), S1).
step(_, if(false, _, S2), S2).

% Rules for let
step(_, let(X, E1, E2), (X -> E2) $ E1).

% Rules for lambda
step(Env, X -> E, closure(X, E, Env)).

% Rules for apply
step(Env, A $ B, A1 $ B) :-
    step(Env, A, A1).
step(Env, A $ B, A $ B1) :-
    step(Env, B, B1).
step(_, closure(X, E, Env) $ V, Result) :-
    set(Env, X, V, Env1), 
    step(Env1, E, E1)
    ->  Result = closure(X, E1, Env) $ V
    ;   Result = E.

% Rules for lists
step(Env, cons $ H $ T, cons $ H1 $ T) :-
    step(Env, H, H1).
step(Env, cons $ H $ T, cons $ H $ T1) :-
    step(Env, T, T1).
step(Env, cons $ H $ T, [H|T]) :-
    \+ step(Env, H, _),
    \+ step(Env, T, _).
step(_, empty, []).

% Rules for uncons, the construct for defining function on lists by cases
step(_, uncons $ [] $ D $ _, D).
step(_, uncons $ [H|T] $ _ $ F, F $ H $ T).

all_steps(Env, E1, Trace, E) :-
    step(Env, E1, E2)
    ->  all_steps(Env, E2, Trace1, E), Trace = [E2|Trace1]
    ;   E = E1, Trace=[].

run(E, V) :- all_steps([], E, _, V).

print_list([]).
print_list([H|T]) :- print(H), nl, print_list(T).

trace(E1) :- all_steps([], E1, Trace, _), print_list(Trace).



lam1((f -> (f $ 1) + (f $ 2)) $ (x -> x)).
lam2((f -> if(f $ true, f $ 1, f $ 2)) $ (x -> x)).

let1(let(f, x -> x, f$1 + f$2)).
let2(let(f, x -> x, if(f $ true, f $ 1, f $ 2))).



test1(V) :- lam1(X), run(X, V).
test2(V) :- lam2(X), run(X, V).
test3(V) :- let1(X), run(X, V).
test4(V) :- let2(X), run(X, V).

testtrace :- lam1(X), trace(X).

%:- trace(let(head, default -> l -> uncons $ l $ default $ (h -> t -> h), head $ 0 $ (cons $ 4 $ empty)))

