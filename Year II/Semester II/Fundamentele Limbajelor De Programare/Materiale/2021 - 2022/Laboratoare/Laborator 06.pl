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


test0 :- program( {x = 10 ; sum = 0; while(0 =< x,{sum = sum + x; x = x-1})}, sum).

test1 :- program( {i = 3; while(0 =< i, {i = i+ -4})},i ).
test2 :- program( {i = 3; n = false + 1; while(0 =< i, {i = i+ -4})},i ).

% test0

get(S,X,I) :- member(vi(X,I),S).
get(_,_,0).

set(S,X,I,[vi(X,I)|S1]) :- del(S,X,S1).

del([vi(X,_)|S],X,S).
del([H|S],X,[H|S1]) :- del(S,X,S1) .
del([],_,[]).

smallstepA(X,S,I,S) :- atom(X), get(S,X,I).

smallstepA(I1 + I2,S,I,S):- integer(I1),integer(I2), I is I1 + I2.
smallstepA(I + AE1,S,I + AE2,S):- integer(I), smallstepA(AE1,S,AE2,S).
smallstepA(AE1 + AE,S,AE2 + AE,S):- smallstepA(AE1,S,AE2,S).

smallstepA(I1 - I2,S,I,S):-
  integer(I1),integer(I2),
  I is I1 - I2.
smallstepA(I - AE1,S,I - AE2,S):-
  integer(I),
  smallstepA(AE1,S,AE2,S).
smallstepA(AE1 - AE,S,AE2 - AE,S):-
  smallstepA(AE1,S,AE2,S).

smallstepA(I1 * I2,S,I,S):-
  integer(I1),integer(I2),
  I is I1 * I2.
smallstepA(I * AE1,S,I * AE2,S):-
  integer(I),
  smallstepA(AE1,S,AE2,S).
smallstepA(AE1 * AE,S,AE2 * AE,S):-
  smallstepA(AE1,S,AE2,S).


/*
?-   smallstepA(a + b, [vi(a,1),vi(b,2)],AE, S).
AE = 1+b,
S = [vi(a, 1), vi(b, 2)] .

?- smallstepA(1 + b, [vi(a,1),vi(b,2)],AE, S).
AE = 1+2,
S = [vi(a, 1), vi(b, 2)] .

?- smallstepA(1 + 2, [vi(a,1),vi(b,2)],AE, S).
AE = 3,
S = [vi(a, 1), vi(b, 2)] .

*/

smallstepB(I1 =< I2,S,true,S):- integer(I1),integer(I2), (I1 =< I2).
smallstepB(I1 =< I2,S,false,S):- integer(I1),integer(I2), (I1 > I2).
smallstepB(I =< AE1,S,I =< AE2,S):- smallstepA(AE1,S,AE2,S).
smallstepB(AE1 =< AE,S,AE2 =< AE,S):- smallstepA(AE1,S,AE2,S).


smallstepB(or(true,_),S,true,S) .
smallstepB(or(false,BE2),S,BE2,S) .
smallstepB(or(BE1,BE),S,or(BE2,BE),S) :-
  smallstepB(BE1,S,BE2,S).

smallstepS({E},S,E,S).

smallstepS((skip;St2),S,St2,S).
smallstepS((St1;St),S1,(St2;St),S2) :- smallstepS(St1,S1,St2,S2).

%Semantica atribuirii
smallstepS(X = AE,S,skip,S1) :- integer(AE),set(S,X,AE,S1).
smallstepS(X = AE1,S,X = AE2,S) :- smallstepA(AE1,S,AE2,S).

%Semantica lui if


%Semantica lui while
smallstepS(while(BE,St),S,if(BE,(St;while(BE,St)),skip),S).

%Semantica programelor
smallstepP(skip,AE1,S1,skip,AE2,S2) :- smallstepA(AE1,S1,AE2,S2).
smallstepP(St1,AE,S1,St2,AE,S2) :- smallstepS(St1,S1,St2,S2).

run(skip,I,_,I):- integer(I).
run(St1,AE1,S1,I) :- smallstepP(St1,AE1,S1,St2,AE2,S2), run(St2,AE2,S2,I).
run_program(Name) :- defpg(Name,{P},E), run(P,E, [],I), write(I).

defpg(pg1,
  {nr = 0; while( nr =< 10, nr=nr+1)},
  nr).

defpg(pg2, {x = 10 ; sum = 0; while(0 =< x, {sum = sum + x; x = x - 1})},sum).

defpg(pg3, {x = 2 ; sum = 0; while(0 =< x, {sum = sum + x; x = x - 1})},sum).

defpg(pg4,{i = 3; while(0 =< i, {i = i+ -4})}, i). 


defpg(pg5,{i = 3; n = false + 1; while(0 =< i, {i = i+ -4})},i).

defpg(pg6,{i = 3; n = false + 1; while(0 =< i, {i = i+ -4})},n).

/*
?- run_program(pg1).
11
true .

?- run_program(pg2).
55
true 

?- run_program(pg3).
3
true 
*/
mytrace(skip,I,_) :- integer(I).
mytrace(St1,AE1,S1) :- smallstepP(St1,AE1,S1,St2,AE2,S2), write(St2),nl, write(AE2),nl, write(S2),nl, mytrace(St2,AE2,S2).
trace_program(Name) :- defpg(Name,{P},E), mytrace(P,E,[]).

/*
?- trace_program(pg3).
skip;sum=0;while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,2)]
sum=0;while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,2)]
skip;while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,0),vi(x,2)]
while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,0),vi(x,2)]
if(0=<x,({sum=sum+x;x=x-1};while(0=<x,{sum=sum+x;x=x-1})),skip)
sum
[vi(sum,0),vi(x,2)]
if(0=<2,({sum=sum+x;x=x-1};while(0=<x,{sum=sum+x;x=x-1})),skip)
sum
[vi(sum,0),vi(x,2)]
if(true,({sum=sum+x;x=x-1};while(0=<x,{sum=sum+x;x=x-1})),skip)
sum
[vi(sum,0),vi(x,2)]
{sum=sum+x;x=x-1};while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,0),vi(x,2)]
(sum=sum+x;x=x-1);while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,0),vi(x,2)]
(sum=0+x;x=x-1);while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,0),vi(x,2)]
(sum=0+2;x=x-1);while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,0),vi(x,2)]
(sum=2;x=x-1);while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,0),vi(x,2)]
(skip;x=x-1);while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,2),vi(x,2)]
x=x-1;while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,2),vi(x,2)]
x=2-1;while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,2),vi(x,2)]
x=1;while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,2),vi(x,2)]
skip;while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,1),vi(sum,2)]
while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,1),vi(sum,2)]
if(0=<x,({sum=sum+x;x=x-1};while(0=<x,{sum=sum+x;x=x-1})),skip)
sum
[vi(x,1),vi(sum,2)]
if(0=<1,({sum=sum+x;x=x-1};while(0=<x,{sum=sum+x;x=x-1})),skip)
sum
[vi(x,1),vi(sum,2)]
if(true,({sum=sum+x;x=x-1};while(0=<x,{sum=sum+x;x=x-1})),skip)
sum
[vi(x,1),vi(sum,2)]
{sum=sum+x;x=x-1};while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,1),vi(sum,2)]
(sum=sum+x;x=x-1);while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,1),vi(sum,2)]
(sum=2+x;x=x-1);while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,1),vi(sum,2)]
(sum=2+1;x=x-1);while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,1),vi(sum,2)]
(sum=3;x=x-1);while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,1),vi(sum,2)]
(skip;x=x-1);while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,3),vi(x,1)]
x=x-1;while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,3),vi(x,1)]
x=1-1;while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,3),vi(x,1)]
x=0;while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,3),vi(x,1)]
skip;while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,0),vi(sum,3)]
while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,0),vi(sum,3)]
if(0=<x,({sum=sum+x;x=x-1};while(0=<x,{sum=sum+x;x=x-1})),skip)
sum
[vi(x,0),vi(sum,3)]
if(0=<0,({sum=sum+x;x=x-1};while(0=<x,{sum=sum+x;x=x-1})),skip)
sum
[vi(x,0),vi(sum,3)]
if(true,({sum=sum+x;x=x-1};while(0=<x,{sum=sum+x;x=x-1})),skip)
sum
[vi(x,0),vi(sum,3)]
{sum=sum+x;x=x-1};while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,0),vi(sum,3)]
(sum=sum+x;x=x-1);while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,0),vi(sum,3)]
(sum=3+x;x=x-1);while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,0),vi(sum,3)]
(sum=3+0;x=x-1);while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,0),vi(sum,3)]
(sum=3;x=x-1);while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,0),vi(sum,3)]
(skip;x=x-1);while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,3),vi(x,0)]
x=x-1;while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,3),vi(x,0)]
x=0-1;while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,3),vi(x,0)]
x= -1;while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(sum,3),vi(x,0)]
skip;while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,-1),vi(sum,3)]
while(0=<x,{sum=sum+x;x=x-1})
sum
[vi(x,-1),vi(sum,3)]
if(0=<x,({sum=sum+x;x=x-1};while(0=<x,{sum=sum+x;x=x-1})),skip)
sum
[vi(x,-1),vi(sum,3)]
if(0=< -1,({sum=sum+x;x=x-1};while(0=<x,{sum=sum+x;x=x-1})),skip)
sum
[vi(x,-1),vi(sum,3)]
if(false,({sum=sum+x;x=x-1};while(0=<x,{sum=sum+x;x=x-1})),skip)
sum
[vi(x,-1),vi(sum,3)]
skip
sum
[vi(x,-1),vi(sum,3)]
skip
3
[vi(x,-1),vi(sum,3)]
true 

*/