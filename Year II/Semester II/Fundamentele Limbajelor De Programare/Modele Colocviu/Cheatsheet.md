# Prolog Cheat Sheet

## Usage

* Start prolog with `$ swipl`.
* Load code with `?- ['laborator/labx/sample.pl'].`.
* Exit `swipl` with `?- halt.`.

## Syntax

 * Variables, starting with capital letters or underscores without quotes.
 * Atoms are:
    * starting with lowercase letters.
    * Special caracters (e.g. `+`, `:::`, `<<->>+`).
    * In quotes (e.g. `"This is an atom"`).
 * Numbers
 
## Query

 ```pl
    bigger(elefant, horse).
    bigger(horse, donkey).
    bigger(donkey, mouse).
    bigger(house, elefant).

    is_bigger(A, B) :- bigger(A, B).
    is_bigger(A, B) :- bigger(A, X), is_bigger(X, B).
 ```

 * True / False query: `?- is_bigger(house, mouse).`
 * Get values: `?- is_bigger(X, mouse).`
    * `enter` to dimiss answers.
    * `;` to get next answer.
 * Multiple conditions: `?- is_bigger(house, X), is_bigger(X, Y), is_bigger(Y, mouse).`

## Aritmetics

* `=` -> Checks for same expression.
* `X is Y` -> checks if Y evaluates to X. Y NEEDS TO BE FULLY INSTANCIATED.
* `a =:= b` -> checks if the two values are equal. Equivalent to `a is b, b is a`.


## Conditions

```prolog
max([X], X).
max([H | T], M) :-
    max(T, N),
    N > H -> M = N;
             M = H. 
```

## alpha-conversii

-> Redenumim variabile bounduite pentru a evita conflicte de nume.

\x . x y =(apha) \z . z y

## beta-reductii

-> efectiv efectuam aplicarea functiei.
Trebuie ca variabilele libere din ce adaugam sa fie diferite de cele existente => facem alpha-conversii.

(\x . M) E ==beta==> M[x := E]

Beta-normala: nu se mai pot efectua beta-reductii.