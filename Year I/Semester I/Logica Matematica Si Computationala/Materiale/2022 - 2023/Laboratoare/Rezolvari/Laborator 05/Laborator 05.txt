ex1:

vars(V,[V]) :- atom(V).
vars(non(X),S) :- vars(X,S).
vars(si(X,Y),S) :- vars(X,T), vars(Y,U), union(T,U,S).
vars(sau(X,Y),S) :- vars(X,T), vars(Y,U), union(T,U,S).
vars(imp(X,Y),S) :- vars(X,T), vars(Y,U), union(T,U,S).

ex2:

val(V,[(V,A)|_],A).
val(V,[_|T],A) :- val(V,T,A).

%Solutie alternativa:

val(V,E,A) :- member((V,A),E).

ex3:

bnon(0,1). bnon(1,0).
bsi(0,0,0). bsi(0,1,0). bsi(1,0,0). bsi(1,1,1).
bsau(0,0,0). bsau(0,1,1). bsau(1,0,1). bsau(1,1,1).
% X -> Y = (non X) sau Y
bimp(X,Y,Z) :- bnon(X,NX), bsau(NX,Y,Z).

ex4:

eval(V,E,A) :- atom(V), val(V,E,A).
eval(non(X),E,A) :- eval(X,E,B), bnon(B,A).
eval(si(X,Y),E,A) :- eval(X,E,B), eval(Y,E,C), bsi(B,C,A).
eval(sau(X,Y),E,A) :- eval(X,E,B), eval(Y,E,C), bsau(B,C,A).
eval(imp(X,Y),E,A) :- eval(X,E,B), eval(Y,E,C), bimp(B,C,A).

ex5:

evals(_,[],[]).
evals(X,[E|Es],[A|As]) :- eval(X,E,A), evals(X,Es,As).

ex6:

evs([],[[]]).
evs([V|T],Es) :- evs(T,Esp), adauga(V,Esp,Es).
adauga(_,[],[]).
adauga(V,[E|T], [[(V,0)|E],[(V,1)|E]|Es]) :- adauga(V,T,Es).

ex7:

all_evals(X,As) :- vars(X,S), evs(S,Es), evals(X,Es,As).

ex8:

all_ones([]).
all_ones([1|T]) :- all_ones(T).
taut(X) :- all_evals(X,As), all_ones(As).