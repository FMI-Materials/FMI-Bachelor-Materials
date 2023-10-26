culoare(albastru).
culoare(rosu).
culoare(verde).
culoare(galben).

harta(RO, SE, MD, UA, BG, HU) :- 
    vecin(RO, SE), vecin(RO, UA), 
    vecin(RO, MD), vecin(RO, BG), 
    vecin(RO, HU), vecin(UA, MD),
    vecin(BG, SE), vecin(SE, HU).

vecin(X, Y) :- 
    culoare(X), 
    culoare(Y), 
    X \== Y.