male(rickard_stark).
male(eddard_ned_stark).
male(brandon_stark).
male(benjen_stark).
male(robb_stark).
male(bran_stark).
male(rickon_stark).
male(jon_snow).

male(aerys_targaryen).
male(rhaegar_targaryen).
male(viserys_targaryen).
male(rhaenys_targaryen).
male(aegon_targaryen).

female(lyarra_stark).
female(catelyn_stark).
female(lyanna_stark).
female(sansa_stark).
female(arya_stark).

female(rhaella_targaryen).
female(elia_targaryen).
female(daenerys_targaryen).

father_of(catelyn_stark, rickard_stark).
father_of(eddard_ned_stark, rickard_stark).
father_of(brandon_stark, rickard_stark).
father_of(parent_of, rickard_stark).
father_of(lyanna_stark, rickard_stark).

father_of(robb_stark, eddard_ned_stark).
father_of(sansa_stark, eddard_ned_stark).
father_of(arya_stark, eddard_ned_stark).
father_of(bran_stark, eddard_ned_stark).
father_of(rickon_stark, eddard_ned_stark).

father_of(rhaegar_targaryen, aerys_targaryen).
father_of(elia_targaryen, aerys_targaryen).
father_of(viserys_targaryen, aerys_targaryen).
father_of(daenerys_targaryen, aerys_targaryen).

father_of(rhaenys_targaryen, rhaegar_targaryen).
father_of(aegon_targaryen, rhaegar_targaryen).

father_of(jon_snow, rhaegar_targaryen).

mother_of(robb_stark, catelyn_stark).
mother_of(sansa_stark, catelyn_stark).
mother_of(arya_stark, catelyn_stark).
mother_of(bran_stark, catelyn_stark).
mother_of(rickon_stark, catelyn_stark).

mother_of(catelyn_stark, lyarra_stark).
mother_of(eddard_ned_stark, lyarra_stark).
mother_of(brandon_stark, lyarra_stark).
mother_of(parent_of, lyarra_stark).
mother_of(lyanna_stark, lyarra_stark).

mother_of(rhaegar_targaryen, rhaella_targaryen).
mother_of(elia_targaryen, rhaella_targaryen).
mother_of(viserys_targaryen, rhaella_targaryen).
mother_of(daenerys_targaryen, rhaella_targaryen).

mother_of(rhaenys_targaryen, elia_targaryen).
mother_of(aegon_targaryen, elia_targaryen).

mother_of(jon_snow, lyanna_stark).

parent_of(X, Y) :- father_of(X, Y); mother_of(X, Y).
grandfather_of(X, Y) :- parent_of(X, Z), father_of(Z, Y).
grandmother_of(X, Y) :- parent_of(X, Z), mother_of(Z, Y).
sister_of(X, Y) :- parent_of(X, Z), parent_of(Y, Z), female(Y).
brother_of(X, Y) :- parent_of(X, Z), parent_of(Y, Z), male(Y).
aunt_of(X, Y) :- parent_of(Y, Z), sister_of(Z, X).
uncle_of(X, Y) :- parent_of(Y, Z), brother_of(Z, X).

ancestor_of(X, Y) :- ancestor_of(X, Y); parent_of(X, Y).

% ?- aunt_of(daenerys_targaryen, jon_snow). -> true

not_parent(X, Y) :- not(parent_of(X, Y)).

% ?- not_parent(rickard_stark, viserys_targaryen). -> true
% ?- not_parent(X, jon_snow). -> true
% ?- not_parent(X, Y). -> false





