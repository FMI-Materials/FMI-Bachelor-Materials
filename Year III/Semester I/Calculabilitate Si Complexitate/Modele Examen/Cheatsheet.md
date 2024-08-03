# CheatSheet Examen

## Masini Turing

* Masina Turing
    MT = (Q, V, U, delta, q0, B, F)
    Q - stari
    V - alfabet intrare
    U - alfabetul benzii
    delta - functia de tranzitii
        delta : (Q\F)xU -> Parti(QxUx{L,R})
    q0 - starea inifiala
    B - caracterul Blank
    F - starile finale

* MT determinista
    |delta(q, a)| <= 1

* Algoritm
    MT determinista care se opreste pe fiecare intrare

* TM Nedeterminist cu o banda <=> TM Determinist cu 3 benzi
    - Copiem de pe banda 1 pe banda 3 inputul.
    - Generam in ordine toate secventele de mutari posibile (Q x U x Q x U x {L,R})* dupa lungime si lexicografic.
    - Verificam daca putem executa acele mutari pe banda 3.
    - Resetam banda 3 cu banda 1, si reincepem.
    - Daca MT Nedeterminista ruleaza in O(f), atunci cea echivalenta determinista ruleaza in O(c^f) pentru un c.

* MT cu N benzi <=> MT cu o banda
    - Daca avem N benzi, consideram fiecare caracter din noua banda ca fiind un element din (Ux{DA/NU})^N.
        Fiecare caracter reprezinta ce contine fiecare banda pe acea pozitie, si daca acul de citire al acelei
        benzi este sau nu la acea pozitie.
    - La fiecare pas, parcurgem toata banda pentru a extrage valoarea fiecarui ac de citire.
    - Fiecare pas al simularii va costa O(maximul lungimii benzilor).
    - In total, simularea va fi O(Spatiu * Timp)

* MT cu N benzi <=> MT cu doua benzi
    - IDK cum
    - L este in TIME_K(f) <=> L este in TIME_2(f * log)

* Encodare cu un program standard / functie recursiva
    - Encodam starea masinii ca fiind
        `<id_stare, <pozitie_cursor, godelizare_banda>>`
    - Hardcodam cu if-uri fiecare tranzitie posibila a masinii turing

* Savici
    NSPACE(f) = DSPACE(f^2) (divide)

## Programe Standard

* Variabile
    X1...Xn... - Input
    Z1...Zn... - Variabile de calcul
    Y          - Output
    E, A1, ... - Etichete

* Operatii
    V <- V
    V <- V+1
    V <- V-1
    IF V != 0 GOTO L

* Convertire la o MT
    Cate o stare pentru fiecare intructiune
    Cate un numar unar pe banda pentru toate fiecare variabila folosita

* Encodare
    - Etichete
        E-1, A1-2, A2-3, ...
    - Variabile
        Y-1, X1-2, Z1-3, X2-4, Z2-5, ...
    - Instructiune
        `<a, <b, c>>`, unde:
        a = eticheta instructiunii / 0
        b = 
            0, 1, 2 daca avem V<-V, V<-V+1 respectiv V<-V-1
            #(L) + 2, daca instructiunea este IF V!=0 GOTO L
    - Program = Godelizare([I1, I2, ..., Ik]) - 1


## Functii Primitiv Recursive

* Functii primitiv recursive elementare
    - Succesor
        S(n) = n+1
    - Proiectie
        pi_k(x1, ..., xn) = xk
    - Constanta
        f(x1, ..., xn) = C

* Generare de functii recursive
    - Compunere
        f, g1, ..., gn recursive =>
        h(n1, ..., nm) = f(g1(n1, ...), g2(n1, ...), ...) recursiva
    - Recursive Primitiva
        h, g primitiv recursive => f primitiv recursiva, unde f este
        f(x1, ..., xn-1, 0) = h(x1, ..., xn-1)
        f(x1, ..., xn + 1) = g(x1, ..., xn, f(x1, ..., xn))

## Godelizare

* v = [a1, a2, ..., an] = Prod(pi ^ ai)
* v[i] = min_t(not (pi^(t+1) | x))

* <a, b> = 2^a * (2b + 1) - 1
* l(x) = z a.i. exista t, <z, t> = x
* r(x) = z a.i. exista t, <t, z> = x

## Halting

* Presupunem ca exista un macro
    HALT(X, T) ->
        programul codificat cu T se opreste pe intrarea codificata cu X.
* Ne uitam la P
    A: IF HALT(X1, X1) GOTO A
* Ne uitam la P(#(P))
    - Daca nu se opreste, inseamna ca HALT(#P, #P) este fals, adevarat, deci ar trebui sa se opreasca.
    - Daca se opreste, HALT(#P, #P) este adevarat, deci ar trebui sa cicleze.

## Limbaje

* L Recursiv enumerabil =>
    Exista o MT M, cu L(M) = L

* L Recusiv =>
    Exista un algoritm (o MT M care se opreste pe fiecare input), cu L(M) = L

* Limbajul Universal
    Luniv = { `<<M>, <w>>` | M accepta w }
    Luniv este recusiv enumerabil

* Limbajul Diagonal
    Enumaram toate masinile turing, cuvintele.
    Ldiag = { wi | L(Mi) nu contine wi }
    Ldiag nu este acceptat de nicio masina turing (nu e recusiv enumerabil).

## Clase de Limbaje

* TIME_M(n) = numarul de pasi facuti de M pe intrarea n

* TIME_K(f) = { L | exista o MT M cu k benzi, L(M) = L, TIME_M(n) <= f(n) pt oricare n}

* MT OFF-line: Nu avem voie sa scriem pe prima banda, care nu se pune la complexitatea spatiu.

* SPACE_M(n) = dimensiunea maxima a unei benzi folosite in acceptarea lui n.

* SPACE_K(f) = { L | exista o MT M cu K benzi, L(M) = L, foloseste sub f(n) spatiu pe input n}

* Reducere de constante:
    - (N)(D)SPACE_K(f) = (N)(D)SPACE_K(c * f)
    - f supra-liniar => (N)(D)TIME_K(f) = (N)(D)TIME_K(c * f)

* L reductibil in timp polinomial la L' <=> exista o MT M cu timp polinomial,
    care reduce L la L'. Putem folosi translatori off-line, pt care banda de citire si cea de scriere nu se pun la complexitatea spatiu.
    Daca translatorul are spatiu logaritmic, limbajul este reductibil in spatiu logaritmic.

## Ierarhii de Clase De Complexitate

* f spatiu construibila (sc) <=> exista o MT M cu
    oricare n, SPACE_M(n) <= f, si exista w cu |w| = n, SPACE_M(w) = f(n)

* f spatiu construbila complext (scc) <=> exista o MT M
    oricare n, w cu |w|=n, SPACE_M(w) = f(n)

* S1, S2 > log, S2 SCC, lim(S1/S2) = 0 => 
    DSPACE(S2) \ DSPACE(S1) nevid

* T1, T2, T2 SCC, lim(T1 log(T1) / T2) = 0 => 
    DTIME(T2) \ DTIME(T1) nevid

* NSPACE(S) inclus in DSPACE(S^2)

p7 - nedeterminist <=> determinist

 * O masina turing care simuleaza alta masina turing.
   * Ce complexitate ai, daca masina pe care o simulezi are f?
 * 
