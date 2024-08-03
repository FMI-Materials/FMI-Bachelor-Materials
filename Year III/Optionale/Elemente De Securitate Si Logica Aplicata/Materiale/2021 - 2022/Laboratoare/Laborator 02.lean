
/-
  # LAB 2: Propositions and proofs in Lean
-/


open Classical

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
  This perspective is known as *Propositions as types* or the *Curry-Howard correspondence*.
-/

section PropositionalLogic 

/-
  Lean defines the usual propositional constructors: conjunction, disjunction, negation, etc.
  Each of them is governed by so-called principles of *introduction* and *elimination*.
  The introduction principle answers the question:
  *how can one, in general, prove a conjunction / disjunction / etc?*,
  while the elimination principle refers to 
  *what can obtain from a conjunction / disjunction / etc?*

  Implication is not defined. 
  Rather, the notions of implication and that of function coincide.
  Given `p q : Prop`, we will have another proposition `p → q : Prop` 
  representing the implication from `p` to `q`, but this is simply the type of functions from `p` to `q`. 
  There is no difference between the `→` used here, 
  and the symbol `→` in `Int → String`, the type of functions from `Int` to `String`.
  Intuitevly, in order to prove that `p` implies `q`, 
  one has to give a function that transforms proofs of `p` into proofs of `q`.
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
#print And
#check @And.intro 
#check @And.left 
#check @And.right 

/-
  ## Or
  The notation `p ∨ q` is used ofr `Or p q`.
-/
#check Or 
#check Or p q
#print Or
#check @Or.inl 
#check @Or.inr 
#check @Or.elim

/-
  #False
-/
#check False 
#print False
#check @False.elim
/-
  Fortunately, no introduction rule for `False` exists.
  Indeed, a way of proving `False` would mean Lean is inconsistent.
-/

/-
  ## Not
  Negation is defined by `Not p := p → False`.
-/
#check Not 
#check Not p
#print Not

/-
  The law of excludded middle.
-/
#check em

/-
  **Exercise 1**: Prove the following theorem.
  Hint: Look at the `applyFunction` function defined in Lab1
-/
theorem modus_ponens : p → (p → q) → q := sorry

/-
  **Exercise 2**: Prove the following theorem.
  Hint: Look at the `swap` function defined in Lab1
-/
theorem and_comm : p ∧ q → q ∧ p := sorry 


/-
  In principle, any theorem can be proved by simply writing a function of the appropriate type 
  (the type of the theorem's statement), like above.
  This can get unwieldy for complex proofs, so Lean offers a different embedded language called *tactic mode*.
  At any point in a proof, there is a *proof state* composed of a number of hypotheses and a number of goals needing to be proved.
  A tactic changes the proof state, until no more goals are left.
-/

theorem modus_ponens_tactics : p → (p → q) → q := by --we enter tactic mode with `by`. Note the infoview on the right.
  -- we need to prove an implication. We first suppose its premise.
  intros hp -- suppose a proof of `p` exists, and call it `hp`
            -- note the change in the proof state
  -- we still have an implication to prove, so we again assume its premise.
  intros hpq
  -- we need to prove `q`. We can obtain `q` from the conclusion of `hpq` if we provide the right premise to it
  apply hpq -- the goal would follow from `hpq` if we proved its required conclusion. Note the goal change
  -- the goal is now just one of the hypotheses
  assumption

theorem and_comm_tactics : p ∧ q → q ∧ p := by --we enter tactic mode with `by`. Note the infoview on the right.
  -- we need to prove an implication. We first suppose its premise 
  intros hpq -- suppose a proof of `p wedge q` exists, and call it `hpq`
             -- note the change in the proof state 
  -- we know p ∧ q, and from it can obtain both `p` and `q` 
  cases hpq with | _ hp hq => 
  -- we need to prove `q ∧ p`. We know this can be proved from `And.intro` 
  apply And.intro 
  -- in order to apply `And.intro` we need to to have both a proof of `p` and a proof of `q`
  -- Lean produced two new goals, both of which are trivial two solve
  case left => 
    assumption 
  case right => 
    assumption 
  

/-
  Usually, tactic mode and term mode may be freely combined.
  For instance, a more concise version of the above may be:
-/
theorem and_comm_tactics' : p ∧ q → q ∧ p := by 
  intros hpq 
  cases hpq with | intro hp hq =>
  exact And.intro hq hp

/-
  **Exercise 3**: Prove the following theorem, using tactic mode
-/
example : p → q → (p ∧ q) := sorry 

/-
  **Exercise 4**: Give the shortest possible *term mode* proof you can think of for the above statement
-/
example : p → q → (p ∧ q) := sorry 


/-
  **Exercise 5**: Prove the following, using tactic or term mode.
-/

/-**5.1**-/ 
example : p ∧ (q ∨ r) → (p ∨ q) ∨ (p ∧ r) := sorry 

/-**5.2**-/ 
example : p ∨ q → q ∨ p := sorry 

/-**5.3**-/ 
example : p → ¬¬p := sorry 

/-**5.4**-/ 
example : (p → q) → ¬q → ¬p := sorry
/-
  After you have solved **5.4**, uncomment the following line.
-/
-- #eval remark

/-**5.5**-/ 
example : ¬¬p → p := sorry
/-
  If you get stuck, uncomment the following line to get a hint for the last exercise above.
-/
-- #eval hint




end PropositionalLogic





