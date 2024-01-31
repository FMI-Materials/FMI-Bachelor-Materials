sits_right_of(tywinLannister, petyrBaelish).
sits_right_of(cerseiBaratheon, tywinLannister).
sits_right_of(janosSlynt, cerseiBaratheon).
sits_right_of(tyrionLannister, janosSlynt).
sits_right_of(grandMaesterPycelle, tyrionLannister).
sits_right_of(varys, grandMaesterPycelle).
sits_right_of(petyrBaelish, varys).

sits_left_of(X, Y) :- sits_right_of(Y, X).
are_neighbors_of(X, Y, Z) :- sits_left_of(X, Z), sits_right_of(Y, Z).
next_to_each_other(X, Y) :- sits_right_of(X, Y); sits_left_of(Y, X).
