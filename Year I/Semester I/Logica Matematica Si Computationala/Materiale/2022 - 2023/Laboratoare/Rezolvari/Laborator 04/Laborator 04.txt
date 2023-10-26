ex1:

listaNelem(_,0,[]).
listaNelem(L,N,[H|T]) :- N > 0, P is N - 1, member(H,L), listaNelem(L,P,T).

ex2:

word(abalone,a,b,a,l,o,n,e).
word(abandon,a,b,a,n,d,o,n).
word(enhance,e,n,h,a,n,c,e).
word(anagram,a,n,a,g,r,a,m).
word(connect,c,o,n,n,e,c,t).
word(elegant,e,l,e,g,a,n,t).

crosswd(V1,V2,V3,H1,H2,H3) :-
                word(V1,_,A,_,B,_,C,_),
                word(V2,_,D,_,E,_,F,_),
                word(V3,_,G,_,H,_,I,_),
                word(H1,_,A,_,D,_,G,_),
                word(H2,_,B,_,E,_,H,_),
                word(H3,_,C,_,F,_,I,_).

ex3:

path(X,X,[X]).
path(X,Y,[X|L]) :- connected(X,Z), path(Z,Y,L).

pathc(X,Y) :- path(X,Y,_).

ex4:

word_letters(X,Y) :- atom_chars(X,Y).

liminus([C|L],C,L).
liminus([D|L],C,[D|M]) :- D\==C, liminus(L,C,M).

cover([],_).
cover([H|T],L) :- liminus(L,H,M), cover(T,M).

solution(Letters, Word, Len) :- word(Word), word_letters(Word,WordLetters), length(WordLetters,Len), cover(WordLetters, Letters).

search_solution(_,'no solution',0).
search_solution(ListLetters,Word,X) :- X > 0, solution(ListLetters,Word,X).
search_solution(ListLetters,Word,X) :- X > 0, not(solution(ListLetters,Word,X)), Y is X-1, search_solution(ListLetters,Word,Y).

topsolution(ListLetters,Word) :- length(ListLetters, MaxScore),  search_solution(ListLetters,Word,MaxScore).