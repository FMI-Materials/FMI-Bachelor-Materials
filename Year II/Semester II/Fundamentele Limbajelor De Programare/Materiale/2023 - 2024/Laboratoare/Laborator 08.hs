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
                    
data LambdaTerm = Var String | Lam String LambdaTerm | App LambdaTerm LambdaTerm
    deriving Show

-- free variables of a lambda term
fv :: LambdaTerm -> [String]
fv (Var x) = [x]
fv (Lam x t) = [y | y <- fv t, y /= x]
fv (App t s) = union2 (fv t) (fv s)

-- an endless reservoir of variables
freshvarlist :: [String]
freshvarlist = map ("x" ++) (map show [0..])

-- This is where the new stuff starts

-- annotated lambda term
data AnnLambdaTerm = AVar String | ALam String String AnnLambdaTerm | AApp AnnLambdaTerm AnnLambdaTerm
    deriving Show

-- the gamma_M context from the type inference algorithm
gamma :: LambdaTerm -> [(String,String)]
gamma t = zip (fv t) freshvarlist

-- auxiliary function for annotation: given a term and a list of fresh variables, returns the annotated term and the list of remaining fresh variables
annotate_aux :: LambdaTerm -> [String] -> (AnnLambdaTerm, [String])
annotate_aux = undefined

-- annotates a term as in the type inference algorithm; returns the annotated term and the list of remaining fresh variables 
annotate :: LambdaTerm -> (AnnLambdaTerm, [String])
annotate t = annotate_aux t [x | x <- freshvarlist, notElem x [w | (z, w) <- (gamma t)]]

-- auxiliary function for constraints: given an annotated term, a list of fresh variables and a context, returns the list of equationsand the list of remaining fresh variables
constraints_aux :: AnnLambdaTerm -> [String] -> [(String,String)] -> ([Equ], [String])
constraints_aux = undefined

-- finds the list of equations associated to a term together with the type variable to which the term corresponds
constraints :: LambdaTerm -> ([Equ], String)
constraints t = let (u, z:zs) = annotate t
                    (es, _) = constraints_aux u (z:zs) (gamma t)
                in (es, z)

-- finds the value of a variable in a set of equations in solved form
find :: String -> [Equ] -> Term
find z ((Equ (Variable w) t):es) | z == w = t
find z ((Equ t (Variable w)):es) | z == w = t
find z (_:es) = find z es

data SimpleType = TypeVar String | Arrow SimpleType SimpleType
    deriving Show

-- converts a type expressed as a first-order term into a type properly formalized
totype :: Term -> SimpleType
totype (Variable x) = TypeVar x
totype (FuncSym a [t, s]) = Arrow (totype t) (totype s)

-- finds the type of a term if it exists
typeinf :: LambdaTerm -> Maybe SimpleType
typeinf t = let (es, z) = constraints t
            in case (unify es) of
                   Set fs -> Just (totype (find z fs))
                   Failure -> Nothing

testl1 = typeinf $ Lam "x" (Var "x")     
testl2 = typeinf $ Lam "x" (Lam "y" (Var "x"))
testm1 = typeinf $ (App (Lam "z" (Lam "u" (Var "z"))) (App (Var "y") (Var "x")))
testm2 = typeinf $ (App (Var "x") (Var "x"))
