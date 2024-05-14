import Debug.Trace

data Term = Variable String | FuncSym String [Term]
    deriving (Eq, Show)
    
union2 :: (Eq a) => [a] -> [a] -> [a]
union2 x y = x ++ [z | z <- y, notElem z x]
    
union :: (Eq a) => [[a]] -> [a]
union = foldr union2 []

-- returns all variables of a term
var :: Term -> [String]
var (Variable x) = [x]
var (FuncSym f ts) = union (map var ts)

-- substitutes, in a term, a variable by another term
subst :: Term -> String -> Term -> Term
subst (Variable x) y t | x == y = t
subst (Variable x) _ _ = Variable x
subst (FuncSym f ts) y t = FuncSym f (map (\u -> subst u y t) ts)

data Equ = Equ Term Term
    deriving Show

data StepResult = FailureS | Stopped | SetS [Equ]
    deriving Show

step1 :: [Equ] -> StepResult
step1 [] = Stopped
step1 ((Equ (FuncSym f ss) (FuncSym g ts)):es) | f == g = SetS ((zipWith Equ ss ts) ++ es)
step1 (e:es) = case (step1 es) of
                    Stopped -> Stopped
                    SetS fs -> SetS (e:fs)

step2 :: [Equ] -> StepResult
step2 [] = Stopped
step2 ((Equ (FuncSym f ss) (FuncSym g ts)):es) | f /= g = FailureS
step2 (e:es) = step2 es

step3 :: [Equ] -> StepResult
step3 [] = Stopped
step3 ((Equ (Variable x) (Variable y)):es) | x == y = SetS es
step3 (e:es) = case (step3 es) of
                    Stopped -> Stopped
                    SetS fs -> SetS (e:fs)

step4 :: [Equ] -> StepResult
step4 [] = Stopped
step4 ((Equ (FuncSym f ss) (Variable x)):es) = SetS ((Equ (Variable x) (FuncSym f ss)):es)
step4 (e:es) = case (step4 es) of
                    Stopped -> Stopped
                    SetS fs -> SetS (e:fs)

step5 :: [Equ] -> StepResult
step5 [] = Stopped
step5 ((Equ (Variable x) (FuncSym f ss)):es) | elem x (var (FuncSym f ss)) = FailureS
step5 (e:es) = step5 es

-- candidates for "x=t" in step 6 of the algorithm
step6cand :: [Equ] -> [Equ]
step6cand es = [Equ (Variable x) t | (Equ (Variable x) t) <- es, not (elem x (var t)), length [1 | (Equ s u) <- es, or [elem x (var s), elem x (var u)]] > 1]

-- substitutes in a list of equations a variable by a term EXCEPT for the equation "variable=term" (as used in step 6 of the algorithm)
substeq :: [Equ] -> String -> Term -> [Equ]
substeq [] _ _ = []
substeq ((Equ s u):es) x t | (s == Variable x) && (u == t) = (Equ s u):(substeq es x t)
substeq ((Equ s u):es) x t = (Equ (subst s x t) (subst u x t)):(substeq es x t)

step6 :: [Equ] -> StepResult
step6 es = case (step6cand es) of
                [] -> Stopped
                (Equ (Variable x) t):_ -> SetS (substeq es x t)
                
onestep :: [Equ] -> StepResult
onestep es = case (step1 es) of
              SetS fs -> SetS fs
              Stopped -> case (step2 es) of
                          FailureS -> FailureS
                          Stopped -> case (step3 es) of
                                      SetS fs -> SetS fs
                                      Stopped -> case (step4 es) of
                                                  SetS fs -> SetS fs
                                                  Stopped -> case (step5 es) of
                                                              FailureS -> FailureS
                                                              Stopped ->  case (step6 es) of
                                                                           SetS fs -> SetS fs
                                                                           Stopped -> Stopped

data AllResult = Failure | Set [Equ]
    deriving Show

unify :: [Equ] -> AllResult
unify es = case (onestep es) of
                    Stopped -> Set es
                    FailureS -> Failure
                    SetS fs -> unify fs
                    
-- This is where the new stuff starts

-- an endless reservoir of variables
freshvarlist :: [String]
freshvarlist = map ("x" ++) (map show [0..])

-- a list of equations in solved form acting as a substitution
substitute :: [Equ] -> Term -> Term
substitute [] t = t
substitute ((Equ (Variable x) s):es) t = substitute es (subst t x s)

data AtomicRel = AtomicRel String [Term]
    deriving (Eq, Show)

-- variables of a relational atomic formula
vara :: AtomicRel -> [String]
vara (AtomicRel p ts) = union (map var ts)

-- substitution for an atomic formula
substitutea :: [Equ] -> AtomicRel -> AtomicRel
substitutea es (AtomicRel p ts) = AtomicRel p (map (substitute es) ts)

-- unification for two atomic formulas
unifya :: AtomicRel -> AtomicRel -> AllResult
unifya (AtomicRel p ts) (AtomicRel q us) | p == q = unify (zipWith Equ ts us)
unifya _ _ = Failure

data Clause = Clause AtomicRel [AtomicRel]
    deriving (Eq, Show)

-- variables of a clause
varcl :: Clause -> [String]
varcl (Clause at ats) = union (map vara (at:ats)) 

-- substitution for a clause
substitutecl :: [Equ] -> Clause -> Clause
substitutecl es (Clause at ats) = Clause (substitutea es at) (map (substitutea es) ats)

data Goal = Goal [AtomicRel]
    deriving (Eq, Show)

-- variables of a goal
vargl :: Goal -> [String]
vargl (Goal ats) = union (map vara ats)

-- fresh variables that are not in a clause and not in a goal
freshFor :: Clause -> Goal -> [String]
freshFor c g = [x | x <- freshvarlist, notElem x (varcl c), notElem x (vargl g)]

-- renaming of a clause according to a goal
renclause :: Goal -> Clause -> Clause
renclause g c = substitutecl [Equ (Variable x) (Variable y) | (x, y) <- zip (varcl c) (freshFor c g)] c

-- substitution for a goal
substitutegl :: [Equ] -> Goal -> Goal
substitutegl es (Goal ats) = Goal (map (substitutea es) ats)

-- auxiliary function for composition of solved forms
composeaux :: [Equ] -> [Equ] -> [Equ]
composeaux [] _ = []
composeaux ((Equ (Variable x) t):es) fs = (Equ (Variable x) (substitute fs t)):(composeaux es fs)

-- variables in a solved form
vareq :: [Equ] -> [String]
vareq [] = []
vareq ((Equ (Variable x) _):es) = x:(vareq es)

-- composition of solved forms
compose :: [Equ] -> [Equ] -> [Equ]
compose es fs = (composeaux es fs) ++ [Equ (Variable x) t | (Equ (Variable x) t) <- fs, notElem x (vareq es)]

-- evaluates a goal in a clause (the full program is the first argument)
evaluatenc :: [Clause] -> Goal -> Clause -> [[Equ]]
evaluatenc p (Goal (at:ats)) (Clause bt bts) = case (unifya at bt) of
                                                Failure -> []
                                                Set es -> map (compose es) (evaluatep p (substitutegl es (Goal (bts ++ ats))))

-- evaluates a program and a goal, assuming all the clauses in the program have already been appropriately renamed
evaluatenp :: [Clause] -> Goal -> [[Equ]]
evaluatenp p g = concatMap (evaluatenc p g) p

-- evaluates a program and a goal
evaluatep :: [Clause] -> Goal -> [[Equ]]
evaluatep p (Goal []) = [[]]
evaluatep p g = evaluatenp (map (renclause g) p) g

-- restricts the variables in a solved form to the variables that appear in a given list
restrict :: [String] -> [Equ] -> [Equ]
restrict _ [] = []
restrict vs ((Equ (Variable x) t):es) | elem x vs = (Equ (Variable x) t):(restrict vs es)
restrict vs (_:es) = restrict vs es

-- evaluates a program and a goal (restricting the solved form to the variables that actually appear in the goal)
evaluate :: [Clause] -> Goal -> [[Equ]]
evaluate p g = map (restrict (vargl g)) (evaluatep p g)

-- zero term
termz :: Term
termz = FuncSym "z" []

-- successor
terms :: Term -> Term
terms t = FuncSym "s" [t]

-- variables
vx :: Term
vx = Variable "x"

vy :: Term
vy = Variable "y"

vz :: Term
vz = Variable "z"

vw :: Term
vw = Variable "w"

-- addition predicate
vadd :: Term -> Term -> Term -> AtomicRel
vadd t s u = AtomicRel "add" [t, s, u]

-- multiplication predicate
vmul :: Term -> Term -> Term -> AtomicRel
vmul t s u = AtomicRel "mul" [t, s, u]

-- term for natural number
termn :: Int -> Term
termn 0 = termz
termn n = terms (termn (n-1))

-- recovering the natural number from a term
backp :: Term -> Int
backp (FuncSym "z" []) = 0
backp (FuncSym "s" [t]) = (backp t) + 1

extr :: [[Equ]] -> Int
extr (((Equ (Variable "x") t):_):_) = backp t

proga = [Clause (vadd vx termz vx) [], Clause (vadd vx (terms vy) (terms vz)) [vadd vx vy vz]]
progm = [Clause (vmul vx termz termz) [], Clause (vmul vx (terms vy) vz) [vadd vw vx vz, vmul vx vy vw]]
prog  = proga ++ progm
goal1 = Goal [vadd (termn 3) (termn 4) vx]
goal2 = Goal [vmul (termn 3) (termn 4) vx]
goal3 = Goal [vmul vx (termn 7) (termn 21)]
test1 = extr (evaluate prog goal1)
test2 = extr (evaluate prog goal2)
test3 = extr (evaluate prog goal3)