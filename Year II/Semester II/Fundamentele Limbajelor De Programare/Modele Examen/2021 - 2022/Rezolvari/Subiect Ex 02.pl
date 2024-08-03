:- op(100, xf, {}).
:- op(1100, yf, ;).

aexp(I) :- integer(I).
aexp(X) :- atom(X).
aexp(A1 + A2) :- aexp(A1), aexp(A2).
aexp(A1 - A2) :- aexp(A1), aexp(A2).
aexp(A1 * A2) :- aexp(A1), aexp(A2).

bexp(true). bexp(false).
bexp(A1 =< A2) :- aexp(A1), aexp(A2).
bexp(A1 >= A2) :- aexp(A1), aexp(A2).
bexp(A1 ==A2) :- aexp(A1), aexp(A2).
bexp(not(B)) :- bexp(B).
bexp(and(BE1,BE2)) :- bexp(BE1), bexp(BE2).
bexp(or(BE1,BE2)) :- bexp(BE1), bexp(BE2).

stmt(skip).
stmt(X = AE) :- atom(X), aexp(AE).
stmt(if(BE,St1,St2)) :- bexp(BE), stmt(St1), stmt(St2).
stmt(while(BE,St)) :- bexp(BE), stmt(St).
stmt({St}) :- stmt(St).
stmt(St1;St2) :- stmt(St1), stmt(St2).

program(St,AE) :- stmt(St), aexp(AE).

run(skip,I,_,I):- integer(I).