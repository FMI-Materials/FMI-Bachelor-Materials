married(peter, lucy).
married(paul, mary).
married(bob, juliet).
married(harry, geraldine).

single(Person) :- \+ married(Person, _), \+ married(_, Person).

% Presupunem ca Anne este single deoarece nu am putut demonstra ca este casatorita.