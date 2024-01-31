%---------------------------
% Knowledge base example 2
%---------------------------

eating(joffrey).
deceased(rickard).
dislike(cersei,tyrion).

happy(cersei) :- happy(joffrey).
happy(ser_jamie) :- happy(cersei), deceased(robert). 
happy(joffrey) :- dislike(joffrey,sansa). 
happy(joffrey) :- eating(joffrey). 

/** examples

?- happy(joffrey).
?- happy(cersei).
?- happy(ser_jamie).
?- happy(X). 
*/