adauga(_,[],[]).
adauga(V, [E|T], [[(V, 0)| E], [(V, 1)|E]|Es]):- 
    adauga(V, T, Es).
evs([], [[]]).
evs([V|T], Es):- 
    evs(T, Esp), adauga(V, Esp, Es).