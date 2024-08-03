/-
  # Data: 19.04.2022
  # Prenume: Theodor-Pierre
  # Nume: Moroianu
  # Grupa: 334
-/

open Classical 
/-
  # Test de Laborator Lean - Elemente de Securitate si Logica Aplicata

  Testul este format din 3 exercitii, fiecare valorand 1p. 
  Se acorda punctaje partiale! 
-/

/-
  **Exercitiul 1**
  Fie urmatoarea definitie pentru tipul inductiv al formulelor logicii modale.
  Sa se scrie o functie care primeste o formula 
    si returneaza numarul de atomi propozitionali utilizati.

  *Observatie*: fiecare atom intalnit se considera diferit de ceilalti deja existenti.
  De exemplu, o formula atom → atom se considera a avea doi atomi propozitionali,
    intrucat nu am definit tipul inductiv form astfel incat sa distinga intre cei doi.
-/

section Exercitiul1

inductive form where 
  | atom : form 
  | neg : form → form 
  | impl : form → form → form 
  | box : form → form 

notation:40 "¬"p => form.neg p 
infix:50 "→" => form.impl 
notation p "∧" q => ¬(p → ¬q)
notation p "∨" q => ¬(¬p ∧ ¬q)
prefix:80 "□" => form.box 
notation "⋄"p => ¬(□(¬p))

open form 

def ex1 : form → Nat :=
  fun t =>
  match t with
  | atom => 1
  | neg a => ex1 a
  | impl a b => ex1 a + ex1 b
  | box a => ex1 a


#eval ex1 $ □(atom → atom) → (atom → (¬atom))

end Exercitiul1 


/-
  # Exercitiul 2
  Demonstrati urmatoarea teorema in logica propozitionala, utilizand Lean.
  ⊢ p → (s → ¬q) → (¬p ∨ q) → s → r 

  Poate fi aleasa orice metoda, sau *tactic-mode*, sau *term-mode*.
  **NU** se cer ambele metode! 
-/


-- theorem dne { p : Prop } : ¬¬p → p :=
--   fun hnnp : ¬¬p =>
--   show p from Or.elim (em p) 
--   (
--     fun hp : p => show p from hp
--   )
--   (
--     fun hnp : ¬p => show p from absurd hnp hnnp
--   )

-- furat din lab2
theorem dne { p : Prop } : (¬¬p) → p :=
  fun hnnp : ¬¬p =>
  show p from Or.elim (em p) 
  (
    fun hp : p => show p from hp
  )
  (
    fun hnp : ¬p => show p from absurd hnp hnnp
  )


theorem ex2term { p q r s : Prop } : p → (s → ¬q) → (¬p ∨ q) → s → r :=
  fun hp: p =>
  fun hsnq: s → ¬q =>
  fun hnporq => -- probabil ca din cauza ex1 are un tip mai ciudat, daca ar fi o disjunctie am face
                -- cu Or.elim (...)
  fun hs =>
  have hnq: ¬q := hsnq hs
  have hnporq' := dne hnporq
  have hnporq'' := dne hnporq'
  have hnnq := hnporq'' hp
  have hq := dne hnnq
  have hr: r := absurd hq hnq
  show r from hr

-- theorem ex2tactic { p q r s : Prop } : p → (s → ¬q) → (¬p ∨ q) → s → r := by
--   sorry 

/-
  # Exercitiul 3
  Sa se implementeze urmatoarea functie in Lean:
  ex3 : Nat → Nat → Nat 
  ex3 (x, y) := 
  {
    1                 daca x = 0 si y = 0
    y + 1             daca x = 0
    ex3(x, 1)         daca y = 0
    ex3(x, ex3(x, y)) altfel 
  }

  Implementarea trebuie sa fie facuta prin *recursie structurala*.
  Verificati ce rezultat obtineti pentru x = 2 si y = 3. 
-/

-- def ex3 : Nat → Nat → Nat :=
--   fun n1 n2 =>
--   match n1, n2 with
--   | 0, _ => n2 + 1
--   | n1' + 1, 0 => ex3 n1' 1
--   | n1' + 1, n2' + 1 => ex3 n1' $ ex3 (n1' + 1) n2'


/- DEFINITIA CARE MERGE
ex3(x, y) := 
{
  1                         x=0, y=0
  y + 1                     x=0, y!=0
  ex3(x-1, 1)               x!=0, y=0
  ex3(x-1, ex3(x-1, y-1))   x!=0, y!=0
}
-/

def ex3 : Nat → Nat → Nat :=
  fun n1 =>
  match n1 with
  | 0 => fun n2 => n2 + 1
  | n1' + 1 =>
    fun n2 =>
    match n2 with
    | 0 => ex3 n1' 1
    | n2' + 1 => ex3 n1' $ ex3 n1' n2'

def ex3' : Nat → Nat → Nat :=
  fun n1 n2 =>
  match n1, n2 with
  | 0, n2' => n2' + 1
  | n1' + 1, 0 => ex3' n1' 1
  | n1' + 1, n2' + 1 => ex3' n1' $ ex3' n1' n2'


#eval ex3 2 3

