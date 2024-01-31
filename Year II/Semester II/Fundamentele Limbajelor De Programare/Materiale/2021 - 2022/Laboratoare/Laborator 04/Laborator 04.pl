% laboratorul 2

max([Max], Max).
max([Head | Tail], Max) :- max(Tail, TailMax), Head > TailMax, Max = Head.
max([Head | Tail], Max) :- max(Tail, TailMax), Head =< TailMax, Max = TailMax.

reverse(X, Y) :- reverse(X, [], Y).
reverse([], X, X).
reverse([X | Y], Z, T) :- reverse(Y, [X | Z], T).

palindrom([]).
palindrom(X) :- reverse(X,X).

remove_duplicate([],[]).
remove_duplicate([Head | Tail], Result) :- member(Head, Tail), remove_duplicate(Tail, Result).
remove_duplicate([Head | Tail], [Head | Result]) :- not(member(Head, Tail)), remove_duplicate(Tail, Result).

replace([],_,_,[]).
replace([Head | Tail], E, I, [Head | Rez]) :- Head \== E, replace(Tail, E, I, Rez).
replace([Head | Tail], E, I, [I | Rez]) :- Head == E, replace(Tail, E, I, Rez).


% laboratorul 3

% Crossword puzzle

word(abalone,a,b,a,l,o,n,e).
word(abandon,a,b,a,n,d,o,n).
word(enhance,e,n,h,a,n,c,e).
word(anagram,a,n,a,g,r,a,m).
word(connect,c,o,n,n,e,c,t).
word(elegant,e,l,e,g,a,n,t).

crossword(V1,V2,V3,H1,H2,H3) :-
word(V1,_,A,_,B,_,C,_),
word(V2,_,D,_,E,_,F,_),
word(V3,_,G,_,H,_,I,_),
word(H1,_,A,_,D,_,G,_),
word(H2,_,B,_,E,_,H,_),
word(H3,_,C,_,F,_,I,_).

% Database

born(jan, date(20,3,1977)).
born(jeroen, date(2,2,1992)).
born(joris, date(17,3,1995)).
born(jelle, date(1,1,2004)).
born(joan, date(24,12,0)).
born(joop, date(30,4,1989)).
born(jannecke, date(17,3,1993)).
born(jaap, date(16,11,1995)).

% returneaza anul in care e nascuta persoana data ca argument
year(X, Result) :- born(Result, date(_,_,X)).

% verifica daca prima data e mai mica decat a doua data
before(date(_, _, Y1), date(_, _, Y2)) :- Y1 < Y2.
before(date(_, M1, Y1), date(_, M2, Y2)) :- Y1 = Y2, M1 < M2.
before(date(D1, M1, Y1), date(D2, M2, Y2)) :- Y1 = Y2, M1 = M2, D1 < D2.

% verifica daca prima persoana e mai in varsta decat a doua
older(P1, P2) :- born(P1, Date1), born(P2, Date2), before(Date1, Date2).

% Maze

connected(1,2).
connected(2,1).
connected(1,3).
connected(3,4).

path(X, Y) :- connected(X, A), path(A, Y).
    