female(mary).
female(sandra).
female(juliet).
female(lisa).
male(peter).
male(paul).
male(dony).
male(bob).
male(harry).
parent(bob, lisa).
parent(bob, paul).
parent(bob, mary).
parent(juliet, lisa).
parent(juliet, paul).
parent(juliet, mary).
parent(peter, harry).
parent(lisa, harry).
parent(mary, dony).
parent(mary, sandra).

father_of(Father, Child):- 
    male(Father), parent(Father, Child).
mother_of(Mother, Child):- 
    female(Mother), parent(Mother, Child).
grandfather_of(Grandfather, Child):- 
    father_of(Grandfather, X), parent(X, Child).
grandmother_of(Grandmother, Child):-
    mother_of(Grandmother, X), parent(X, Child).
sister_of(Sister, Person):-
    female(Sister), parent(X, Sister), parent(X, Person), Sister \= Person.
brother_of(Brother, Person):-
    male(Brother), parent(X, Brother), parent(X, Person), Brother \= Person.
aunt_of(Aunt, Person):-
    sister_of(Aunt, X), parent(X, Person).
uncle_of(Uncle, Person):-
    brother_of(Uncle, X), parent(X, Person).