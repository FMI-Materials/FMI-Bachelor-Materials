## Seminar 1 (14 Oct 2021) - Tema

### Masina Turing care sa gasesasca `a^n b^n c^n`

#### Idee

Luam cate un `a`, `b` si `c` pana am consumat tot inputul.

#### Descrierea Masinii Turing

Starile masinii: `{ q1, q2, q3, q4, q5, q6 }`.

Alfabetul de intrare: `{ a, b, c }`.

Alfabetul masinii: `{ a, b, c, A, B, C, Blank }`.

Starea initiala: `q1`.

Starea finala: `q6`.

Tranzitiile:

 * Luam un a:
	`(q1, a) -> (q2, A, R)`
 * Inaintam pana dam de un b:
	`(q2, a) -> (q2, a, R)`
	`(q2, B) -> (q2, B, R)`
 * Luam un b:
	`(q2, b) -> (q3, B, R)`
 * Inaintam pana dam de un c:
	`(q3, b) -> (q3, b, R)`
	`(q3, C) -> (q3, C, R)`
 * Luam un c:
	`(q3, c) -> (q4, C, L)`
 * Mergem inapoi pana dam de un A:
	`(q4, a) -> (q4, a, L)`
	`(q4, b) -> (q4, b, L)`
	`(q4, c) -> (q4, c, L)`
	`(q4, B) -> (q4, B, L)`
	`(q4, C) -> (q4, C, L)`
 * Dam de un A:
	`(q4, A) -> (q1, A, R)`
 * Am terminat toti a:
	`(q1, B) -> (q5, B, R)`
 * Mergem pana dam de `Blank`:
	`(q5, B) -> (q5, B, R)`
	`(q5, C) -> (q5, C, R)`
 * Am dat de `Blank`:
	`(q5, Blank) -> (q6, Blank, L)`

#### Complexitatea

Complexitatea masinii turing este `O(N * Lungime)`.

### Masina turing pentru `w wRev w` (`w` + `w` reversed + `w`)

#### Idee

Nu prea stim ce sa facem pentru ca avem 3 componente (`w`, `wT` si `w`).
Ca sa scapam de problema asta, putem sa facem o schema:
 * In prima componenta `w`, inlocuim `a`, `b` si `c` cu `a1`, `b1` si `c1`.
 * In prima componenta `wT`, inlocuim `a`, `b` si `c` cu `a2`, `b2` si `c2`.
 * In prima componenta `w`, inlocuim `a`, `b` si `c` cu `a3`, `b3` si `c3`.

Observam ca dupa ce am facut aceasta schimbare, problema devine una triviala, pentru ca putem sa o spargem in verificarea prefixului `w wT` si a sufixului `wT w` independent.

#### Solutie

* Pasii pentru a converti `a`, `b` si `c` in `a1-3`, `b1-3` si `c1-3`:

	Pentru a imparti in `w`, `wT` si `w`, vrem practic sa impartim in 3 parti egale inputul.
	Pentru a face asta, pentru fiecare litera, marcam intr-o culoare primele doua aparitii nemarcate si cu alta culoare ultima apartitie nemarcata.

	Astfel, obtinem impartirea in `w wT` si `w`. Procedam similar pentru a colora diferit primele doua bucati.
	1. Inlocuim `[a b c]^3N` in `[a0 b0 c0]^2N [a3 b3 c3]^N`.
		* Mergem la dreapta cat timp avem o litera de forma `X0`.
		* Daca dam de `X3` atunci am terminat pasul 1.
		* Luam litera curenta. Fie `X`. Sunt numai 3 posibilitati (`a`, `b` sau `c`), deci putem sa o encodam in starea masinii turing.
			* Il setam pe `X` in `X0`.
			* Mergem la dreapta pana dam de alt `X`.
			* Il setam si pe acest `X` in `X0`.
			* Mergem la dreapta pana la sfarsitul benzii.
			* Mergem la stanga pana dam de un `X`.
			* Setam acest `X` in `X3`.
		* Mergem la stanga pana la inceputul benzii.
		* Mergem inapoi la inceputul pasului 1.
	2. Inlocuim `[a0 b0 c0]^2N [a3 b3 c3]^N` in `[a1 b1 c1]^N [a2 b2 c2]^N [a3 b3 c3]^N`.
		* Mergem la dreapta cat timp avem o litera de tipul `X1`.
		* Luam litera curenta. Fie `X`. Sunt un numar finit de posibilitati, deci le putem encoda in starea masinii turing.
			* Daca `X` nu este de forma `*0`, atunci am terminat pasul 2.
			* Inlocuim litera din `X0` in `X1`.
			* Mergem la dreapta pana dam de o litera de forma `Y3`.
			* Mergem la stanga pana dam de `X0`.
			* Il inlocuim pe `X0` cu `X2`.
		* Mergem la stanga pana la inceputul benzii.
		* Ne ducem inapoi la inceputul pasului 2.
	3. Verificam ca am impartit corect (detectam daca inputul nu este corect si avem o impartire gresita).
		* Cat timp avem caractere de tipul `X1` mergem la dreapta.
		* Cat timp avem caractere de tipul `X2` mergem la dreapta.
		* Cat timp avem caractere de tipul `X3` mergem la dreapta.
		* Daca nu am dat de `Blank`, refuzam cuvantul.
		* Mergem la stanga pana la inceputul benzii.
* Pasii pentru a verifica ca primele doua bucati (`w` si `wT`) sunt corecte.

	Pentru a face asta, vom inlocui simultan din ambele cuvinte pe `X1/2` cu `X1/2'`.
	4. Inlocuim cuvintele.
		* Mergem la dreapta pana dam de un caracter care sa nu fie de tipul `X1'`.
		* Daca am dat de `X2'`, atunci am terminat pasul 4.
		* Daca dam de `X2`, atunci refuzam cuvantul si ne oprim.
		* Daca dam de un caracter de tipul `X1`, atunci encodam pe `X` in starea automatului si:
			* inlocuim pe `X1` cu `X1'`.
			* Mergem la dreapta pana dam de un caracter de tipul `Y3`.
			* Mergem la stanga pana dam de `X2`.
			* Il inlocuim pe `X2` cu `X2'`.
		* Mergem la stanga pana la inceputul benzii.
		* Ne ducem inapoi la inceputul pasului 4.
	5. Resetam pe `X2'` in `X2`.
		* Mergem la dreapta pana dam de `X2'`.
		* Cat timp dam de `X2'`, facem:
			* Il inlocuim pe `X2'` cu `X2`.
			* Mergem o pozitie la dreapta.
		* Mergem in stanga pana la inceputul benzi.
* Pasii pentru a verifica ca ultimele doua bucati (`wT` si `w`) sunt corecte.

	Procedam ca la pasii precedenti.
	6. Centram acul de citire la inceputul lui `wT`.
		* Cat timp avem un `X1'`, mergem la dreapta.
	7. Inlocuim cuvintele.
		* Mergem la dreapta pana dam de un caracter care sa nu fie de tipul `X2'`.
		* Daca am dat de `X3'`, atunci acceptam cuvantul si ne oprim.
		* Daca dam de `X3`, atunci refuzam cuvantul si ne oprim.
		* Daca dam de un caracter de tipul `X2`, atunci encodam pe `X` in starea automatului si:
			* inlocuim pe `X2` cu `X2'`.
			* Mergem la dreapta pana dam de un `Blank`.
			* Mergem la stanga pana dam de `X3`.
			* Il inlocuim pe `X3` cu `X3'`.
		* Mergem la stanga pana la inceputul benzii.
		* Ne ducem inapoi la inceputul pasului 6.

#### Complexitate

Complexitatea este `O(N^2)`.