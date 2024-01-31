%---------------------------
% Knowledge base example 1
%---------------------------
 

stark(eddard).
stark(jon_snow).
stark(sansa).

lannister(tyrion). 
lannister(cersei). 

dislike(cersei,tyrion). 



/** examples

?- stark(jon_snow). 
?- dislike(cersei,tyrion). 
?- lannister(eddard). 
?- lannister(arya).
?- stark(arya). 
?- targaryen(daenerys).
?- stark(X). 
?- dislike(X,Y). 
?- dislike(X,X). 
*/