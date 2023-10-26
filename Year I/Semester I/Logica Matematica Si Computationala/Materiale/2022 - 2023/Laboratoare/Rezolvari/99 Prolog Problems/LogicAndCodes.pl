% 1) table(A, B, and(A, or(A, B))).
and(A,B):- 
    A, B.
or(A, _):- 
    A.
or(_, B):- 
    B.
equ(A,B):- 
    or(and(A, B), and(not(A), not(B))).
xor(A, B):- 
    not(equ(A,B)).
nor(A, B):- 
    not(or(A, B)).
nand(A, B):- 
    not(and(A, B)).
impl(A, B):- 
    or(not(A), B).
bind(true).
bind(fail).
do(A, B, _):- 
    write(A), write('  '), write(B), write('  '), fail.
do(_, _, Expr):- 
    Expr, !, write(true), nl.
do(_, _, _):- 
    write(fail), nl.
table(A, B, Expr):- 
    bind(A), bind(B), do(A, B, Expr), fail.

% 2) table(A, B, A and (A or not B)).
:- op(900, fy, not).
:- op(910, yfx, and).
:- op(910, yfx, nand).
:- op(920, yfx, or).
:- op(920, yfx, nor).
:- op(930, yfx, impl).
:- op(930, yfx, equ).
:- op(930, yfx, xor).

% 3) table([A,B,C], A and (B or C) equ A and B or A and C).
bindList([]).
bindList([V|Vs]):- 
    bind(V), bindList(Vs).
writeVarList([]).
writeVarList([V|Vs]):-
    write(V), write('  '), writeVarList(Vs).
writeExpr(Expr):- 
    Expr, !, write(true).
writeExpr(_):- 
    write(fail).
do(VarList,Expr):- 
    writeVarList(VarList), writeExpr(Expr), nl.
table(VarList,Expr) :- bindList(VarList), do(VarList,Expr), fail.

% 4) 
% a) gray(3, C).
prepend(_, [], []):- !.
prepend(X, [C|Cs], [CP|CPs]):- 
    atom_concat(X, C, CP), prepend(X, Cs, CPs).
gray(1, ['0','1']).
gray(N, C):- 
    N > 1, N1 is N - 1, gray(N1, C1), reverse(C1, C2), prepend('0', C1, C1P), prepend('1', C2, C2P), append(C1P, C2P, C).

% b) gray_c(3, C).
:- dynamic gray_c/2.
gray_c(1, ['0', '1']):- !.
gray_c(N, C):- 
    N > 1, N1 is N-1,  gray_c(N1, C1), reverse(C1, C2), prepend('0', C1, C1P), prepend('1', C2, C2P), append(C1P, C2P, C), asserta((gray_c(N, C) :- !)).

% c) gray_alt(3, C).
postpend(_, [], []).
postpend(P, [C|Cs], [C1P, C2P|CsP]):- 
    P = [P1, P2], atom_concat(C, P1, C1P), atom_concat(C, P2, C2P), reverse(P, PR), postpend(PR, Cs, CsP).
gray_alt(1, ['0', '1']).
gray_alt(N, C):- 
    N > 1, N1 is N - 1, gray_alt(N1, C1),  postpend(['0', '1'], C1, C).
