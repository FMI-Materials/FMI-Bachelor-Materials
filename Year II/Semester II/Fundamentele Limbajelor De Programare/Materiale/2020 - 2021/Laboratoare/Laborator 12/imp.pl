
:- op(100, xf, {}).
:- op(1100, yf, ;).

stmt(skip).

stmt(X = AE) :-
  atom(X),
  aexp(AE).
  
stmt(St1;St2) :-
  stmt(St1),
  stmt(St2).  

stmt({St}) :-
  stmt(St).

aexp(I) :- integer(I).

%% atomii din Prolog sunt identificatorii limbajului IMP
aexp(X) :- atom(X).


program(St,AE) :-
  stmt(St),
  aexp(AE).
 %% expresia AEXP se evalueaza in starea rezultata dupa rularea programului
 

test3 :- program({x=10; sum=0; if(11 =< x, sum=sum+x,sum=x+100)}, sum).
