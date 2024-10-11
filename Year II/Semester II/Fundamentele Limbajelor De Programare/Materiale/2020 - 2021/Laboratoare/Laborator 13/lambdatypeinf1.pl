:- op(100,xfy,or).
:- op(100,xfy,and).
:- op(200,yfx,$).

remove(Gamma, X, Gamma1) :-
    select((X,_), Gamma, Gamma1),!.
remove(Gamma, _, Gamma).

set(Gamma, X, T, [(X,T) | Gamma1]) :-
    remove(Gamma, X, Gamma1).
get(Gamma, X, T) :- member((X, T), Gamma).

extract_scheme(TSX, T) :-
    \+ var(TSX),
    TSX = scheme(TX),
    copy_term(TX, T).

type(Gamma, X, T) :-
    atom(X),
    get(Gamma, X, TSX),
    (extract_scheme(TSX, TX)
    -> T = TX
    ; T = TSX).


type(_, I, int) :- integer(I).
type(_, true, bool).
type(_, false, bool).
type(Gamma, E1 + E2, int) :-
    type(Gamma, E1, int),
    type(Gamma, E2, int).
type(Gamma, E1 - E2, int) :-
    type(Gamma, E1, int),
    type(Gamma, E2, int).
type(Gamma, E1 * E2, int) :-
    type(Gamma, E1, int),
    type(Gamma, E2, int).
type(Gamma, E1 / E2, int) :-
    type(Gamma, E1, int),
    type(Gamma, E2, int).
type(Gamma, E1 =< E2, bool) :-
    type(Gamma, E1, int),
    type(Gamma, E2, int).
type(Gamma, E1 >= E2, bool) :-
    type(Gamma, E1, int),
    type(Gamma, E2, int).
type(Gamma, E1 < E2, bool) :-
    type(Gamma, E1, int),
    type(Gamma, E2, int).
type(Gamma, E1 = E2, bool) :-
    type(Gamma, E1, int),
    type(Gamma, E2, int).
type(Gamma, E1 > E2, bool) :-
    type(Gamma, E1, int),
    type(Gamma, E2, int).
type(Gamma, E1 and E2, bool) :-
    type(Gamma, E1, bool),
    type(Gamma, E2, bool).
type(Gamma, E1 or E2, bool) :-
    type(Gamma, E1, bool),
    type(Gamma, E2, bool).
type(Gamma, not(E), bool) :-
    type(Gamma, E, bool).
type(Gamma, if(E, E1, E2), T) :-
    type(Gamma, E, bool),
    type(Gamma, E1, T),
    type(Gamma, E2, T).
type(Gamma, X -> E, TX -> TE) :-
    atom(X),
    set(Gamma, X, TX, GammaX),
    type(GammaX, E, TE).
type(Gamma, E1 $ E2, T) :-
    type(Gamma, E1, T2 -> T),
    type(Gamma, E2, T2).

% list types
type(_, [], [_]).
type(Gamma, [HE | TE], [T]) :-
    type(Gamma, HE, T),
    type(Gamma, TE, [T]).  
type(_,listfn, T -> (TL -> [TL] -> T) -> [TL] -> T).    

% let types
type(Gamma, let(X, E1, E2), T) :-
    type(Gamma, E1, T1),
    copy_term(T1, FreshT1),
    set(Gamma, X, scheme(FreshT1), GammaX),
    type(GammaX, E2, T).

% list types
type(_, empty, [_]).
type(_, cons, T -> [T] -> [T]).
type(_,uncons, [TL] -> T -> (TL -> [TL] -> T) -> T).    

run(E) :-
    write("Program "),
    write(E),
    type([], E, T)
    ->  write(" has type "), write(T), nl
    ;   write(" doesn't type"), nl
    . 

%:- run(x -> y -> z -> if(y=0, z, x/y)).
%:- run(let(id, x -> x, if(id $ true, id $ 3, 4 ))).
%:- run(id -> if(id $ true, id $ 3, 4 )).
%:- run(if((x -> x) $ true, (x -> x) $ 3, 4 )).
%:- run(let(null, l -> uncons $ l $ true $ (a -> b -> false), null))
%:- run(let(tail, l -> listfn $ [] $ (h -> t -> t) $ l, null))
%:- run(let(null, l -> uncons $ l $ true $ (a -> b -> false), null $ (cons $ 4 $ empty)))
%:- run(let(tail, l -> uncons $ l $ empty $ (h -> t -> t), tail $ (cons $ 4 $ empty)))
%:- run(let(head, default -> l -> uncons $ l $ default $ (h -> t -> h), head $ 0 $ (cons $ 4 $ empty)))
