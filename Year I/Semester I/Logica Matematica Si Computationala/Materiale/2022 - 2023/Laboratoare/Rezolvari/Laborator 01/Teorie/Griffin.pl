father(peter, meg).
father(peter, stewie).

mother(lois, meg).
mother(lois, stewie).

griffin(peter).
griffin(lois).

griffin(X) :- 
    father(Y, X), griffin(Y).