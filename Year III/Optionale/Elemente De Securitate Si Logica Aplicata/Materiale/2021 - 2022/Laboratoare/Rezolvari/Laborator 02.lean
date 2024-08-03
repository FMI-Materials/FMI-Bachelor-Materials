/-

Logica propozitionala in Lean

- sistemul Hilbert, sistem deductiv format din
* trei axiome
  (A1) φ → (ψ → φ)
  (A2) (φ → (ψ → χ) → (φ → ψ) → (φ → χ)))
  (A3) (¬ψ → ¬φ) → (φ → ψ)

* regula de deductie Modus Ponens 
  φ     φ → ψ
  -----------
      ψ 

Sistemul de deductie naturala 
- ofera reguli de introducere si eliminare pentru toti conectorii logici

Regulile pentru conjunctie
- introducere
  daca φ este adevarata, si daca si ψ este adevarata, atunci φ ∧ ψ 
  And.intro 

- eliminare
  φ ∧ ψ atunci φ      And.left
  φ ∧ ψ atunci ψ      And.right 

Regulile pentru disjunctie
- introducere
  daca φ este adevarata, atunci φ ∨ ψ este adevarata Or.inl 
  daca ψ este adevarata, atunci φ ∨ ψ este adevarata Or.inr    

- eliminare
  daca φ ∨ ψ este adevarata 
    arat ca din φ pot demonstra χ 
    arat ca din ψ pot demonstra χ 
  atunci χ este adevarata Or.elim 

- modus ponens == regula de eliminare a implicatiei 
  este doar aplicarea de functii 

  hpq : p → q 
  hp  : p
  hpq hp

- regula de introducere a implicatiei φ → ψ 
  fun hp : φ => ... show ψ ... 

- presupun p fals si demonstrez ¬p → False, atunci p este adevarat
  byContradiction 

- daca am p si ¬ p simultan adevarate
  p ∧ ¬p ⊢ ψ 
  absurd 

- principiul tertului exclus, em 
  p ∨ ¬p 
-/

open Classical

#check @And.intro         -- ∧i 
#check @And.left          -- ∧l
#check @And.right         -- ∧r
#check @Or.inl            -- ∨l
#check @Or.inr            -- ∨r
#check @Or.elim           -- ∨e
#check @False.elim        -- ⊥ ⊢ anything 
#check @absurd            -- a ∧ ¬a ⊢ anything 
#check @em                -- a ∨ ¬a
#check @byContradiction   -- ¬p → False ⊢ p



/-
  `Prop` is the type of propositions. 
  Examples of propositions are equalities, like the ones we've seen in Lab1. 
-/
#check Prop 
#check 5 = 3

/-
  A proposition is itself a type. If `p : Prop`, we can speak of terms `h` of type `p`.
  We interpret some `h : p` as a *proof* of `p`, so we can say that `p` is the type of all its proofs.
  Proving a proposition `p` therefore means providing some term of type `p`.
  For instance, `rfl` from Lab1 is such term of type `x = x`, and therefore a proof that `x = x`.
-/

section PropositionalLogic 

/-
  Lean defines the usual propositional constructors: conjunction, disjunction, negation.
  Each of them is governed by so-called principles of *introduction* and *elimination*.
  The introduction principle answers the question:
  *how can one, in general, prove a conjunction / disjunction?*,
  while the elimination principle refers to 
  *how can one prove something from a conjunction / disjunction?*
-/

/-
  Using `variable`, we can consider in this section two arbitrary propositions `p` and `q`,
  as if we said *let p and q be any propositions*.
-/

variable (p q : Prop)

/-
  ## And 
  The notation `p ∧ q` is used for `And p q`. 
-/
#check And
#check And p q
#check @And.intro 
#check @And.left 
#check @And.right 

/-
  ## Or
  The notation `p ∨ q` is used for `Or p q`.
-/
#check Or 
#check Or p q
#check @Or.inl 
#check @Or.inr 
#check @Or.elim

/-
  #False
-/
#check @False.elim

/-
  ## Not
  Negation is defined by `Not p := p → False`.
-/
#check Not 
#check Not p

#check em

/-
  Exercise 1: Prove the following theorem.
  Hint: Look at the `applyFunction` function defined in Lab1
-/
theorem modus_ponens : p → (p → q) → q := 
  fun (hp : p) (hpq : p → q) => hpq hp 

/-
  Exercise 2: Prove the following theorem.
  Hint: Look at the `swap` function defined in Lab1
-/
theorem and_comm : p ∧ q → q ∧ p := 
  fun hpq : p ∧ q => And.intro (And.right hpq) (And.left hpq)


/-
  In principle, any theorem can be proved by simply writing a function of the appropriate type 
  (the type of the theorem's statement), like above.
  This can get unwieldy for complex proofs, so Lean offers a different embedded language called *tactic mode*.
  At any point in a proof, there is a *proof state* composed of a number of hypotheses and a number of goals needing to be proved.
  A tactic changes the proof state, until no more goals are left.
-/

theorem modus_ponens_tactics : p → (p → q) → q := by --we enter tactic mode with `by`. Note the infoview on the right.
  -- we need to prove an implication. We first suppose its premise.
  intros hp -- suppose a proof of `p → q` exists, and call it `h_imp_q`
            -- note the change in the proof state
  -- we still have an implication to prove, so we again assume its premise.
  intros hpq 
  -- we need to prove `q`. We can obtain `q` from the conclusion of `hpq` if we provide the right premise to it
  apply hpq -- the goal would follow from `hpq` if we proved its required conclusion. Note the goal change
  -- the goal is now just an assumption 
  assumption

theorem and_comm_tactics : p ∧ q → q ∧ p := by --we enter tactic mode with `by`. Note the infoview on the right.
  -- we need to prove an implication. We first suppose its premise 
  intros hpq -- suppose a proof of `p wedge q` exists, and call it `hpq`
             -- note the change in the proof state 
  -- we know p ∧ q, and from it can obtain both `p` and `q` by 
  cases hpq with | intro hp hq => 
  -- we need to prove `q ∧ p`. We know this can be proved from `And.intro` 
  apply And.intro 
  -- in order to apply `And.intro` we need to to have both a proof of `p` and a proof of `q`
  -- Lean produced two new goals, both of which are trivial two solve
  case left => assumption 
  case right => assumption 
  

/-
  Usually, tactic mode and term mode may be freely combined.
  For instance, a more concise version of the above may be:
-/
theorem and_comm_tactics' : p ∧ q → q ∧ p := by 
  intros hpq 
  cases hpq with | intro hp hq =>
  exact And.intro hq hp

/-
  Exercise 3: Prove the following theorem, using tactic mode
-/
example : p → q → (p ∧ q) := by 
  intro hp hq 
  apply And.intro 
  case left => assumption
  case right => assumption 

/-
  Exercise 4: Give the shortest possible *term mode* proof you can think of for the above statement
-/
example : p → q → (p ∧ q) := And.intro  


/-
  Exercise 5
-/


#check @And.intro         -- ∧i 
#check @And.left          -- ∧l
#check @And.right         -- ∧r
#check @Or.inl            -- ∨l
#check @Or.inr            -- ∨r
#check @Or.elim           -- ∨e
#check @False.elim        -- ⊥ ⊢ anything 
#check @absurd            -- a ∧ ¬a ⊢ anything 
#check @em                -- a ∨ ¬a
#check @byContradiction   -- ¬p → False ⊢ p


example { p q r : Prop } (h₀ : (p ∧ q) ∧ r) (h₁ : s ∧ t) : q ∧ s :=
  sorry 

-- **term-mode**
example { p q r : Prop } : ((p ∧ q) ∧ r) → (s ∧ t) → q ∧ s := 
  fun h₀ : (p ∧ q) ∧ r =>
  fun h₁ : s ∧ t =>
  have h₂ : p ∧ q := And.left h₀
  have h₃ : q := And.right h₂ 
  have h₄ : s := And.left h₁ 
  show q ∧ s from And.intro h₃ h₄  

-- **tactic-mode**
example { p q r : Prop } : ((p ∧ q) ∧ r) → (s ∧ t) → q ∧ s := by
  intro h₀ h₁
  apply And.intro
  case left => exact And.right $ And.left h₀
  case right => exact And.left h₁

/-
  Exercise 6: prove dne and dni
-/

#check em p

theorem dne { p : Prop } : ¬¬p → p :=
  fun hnnp : ¬¬p =>
  show p from Or.elim (em p) 
  (
    fun hp : p => show p from hp
  )
  (
    fun hnp : ¬p => show p from absurd hnp hnnp
  )


example { p : Prop} : ¬¬p → p := by
  intro hnnp 
  apply Or.elim (em p)
  case left => 
    intro hp
    exact hp
  case right =>
    intro hnp 
    exact absurd hnp hnnp 

theorem dni { p : Prop } : p → ¬¬p := 
  fun hp : p => 
  show ¬¬p from byContradiction 
  (
    fun hnnnp : ¬¬¬p =>
    have hnp : ¬p := dne hnnnp 
    show False from absurd hp hnp 
  )


#check @byContradiction 

/-
  Exercise 7
-/

example { p q r : Prop } : p → ¬¬(q ∧ r) → ¬¬p ∧ r := 
  fun h₀ : p =>
  fun h₁ : ¬ ¬ (q ∧ r) =>
  have h₂ : ¬ ¬ p := dni h₀ 
  have h₃ : q ∧ r := dne h₁ 
  have h₄ : r := And.right h₃ 
  show ¬¬p ∧ r from And.intro h₂ h₄  

example { p q r : Prop } : p → ¬¬(q ∧ r) → ¬¬p ∧ r := by 
  intro h₀ h₁
  apply And.intro 
  case left => exact dni h₀
  case right => exact And.right $ dne h₁
/-
  Exercise 8
-/

example { p q r : Prop } : (p ∧ q → r) → (p → q → r) := 
  fun h₀ : p ∧ q → r =>
  fun hp : p =>
  fun hq : q =>
  have hpq : p ∧ q := And.intro hp hq 
  show r from h₀ hpq 

example { p q r : Prop } : (p ∧ q → r) → (p → q → r) := by
  intro h₀ 
  intro hp 
  intro hq 
  exact h₀ (And.intro hp hq)

/-
  Exercise 9
-/

example { p q r : Prop } : p ∧ (q ∨ r) → ((p ∧ q) ∨ (p ∧ r)) := 
  fun h₀ : p ∧ (q ∨ r) =>
  have hp : p := And.left h₀ 
  have hqr : q ∨ r := And.right h₀ 
  show (p ∧ q) ∨ (p ∧ r) from Or.elim hqr 
  (
    fun hq : q => 
    have hpq : p ∧ q := And.intro hp hq 
    show (p ∧ q) ∨ (p ∧ r) from Or.inl hpq 
  )
  (
    fun hr : r =>
    have hpr : p ∧ r := And.intro hp hr 
    show (p ∧ q) ∨ (p ∧ r) from Or.inr hpr 
  )

example { p q r : Prop } : p ∧ (q ∨ r) → ((p ∧ q) ∨ (p ∧ r)) := by
  intro h₀ 
  cases h₀ with | intro hp hqr =>
  apply Or.elim hqr 
  case left => 
    intro hq 
    exact Or.inl $ And.intro hp hq
  case right =>
    intro hr 
    exact Or.inr $ And.intro hp hr 

/-
  Exercise 10
-/

example { p q : Prop} : (p → q) → (p → ¬q) → ¬p := 
  fun hpq : p → q =>
  fun hpnq : p → ¬q => 
  show ¬p from byContradiction 
  ( 
    fun hnnp : ¬¬p =>
    have hp : p := dne hnnp 
    have hq : q := hpq hp 
    have hnq : ¬q := hpnq hp
    show False from absurd hq hnq
  )


/-
  Exercise 11
-/

theorem modus_tollens { φ ψ : Prop } : (φ → ψ) → ¬ψ → ¬φ := 
  sorry 

example { p q r : Prop } : (p → (q → r)) → ((p ∧ q) → r) := by 
  intro h₀ hpq 
  cases hpq with | intro hp hq =>
  exact h₀ hp hq

end PropositionalLogic