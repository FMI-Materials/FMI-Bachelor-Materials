data LambdaTerm = Var String | Lam String LambdaTerm | App LambdaTerm LambdaTerm
    deriving Show

-- union of two sets represented as lists
union2 :: (Eq a) => [a] -> [a] -> [a]
union2 x y = x ++ [z | z <- y, notElem z x]

-- variables of a lambda term
var :: LambdaTerm -> [String]
var (Var x) = [x]
var (Lam x t) = union2 (var t) [x]
var (App t s) = union2 (var t) (var s)

-- free variables of a lambda term
fv :: LambdaTerm -> [String]
fv (Var x) = [x]
fv (Lam x t) = [y | y <- fv t, y /= x]
fv (App t s) = union2 (fv t) (fv s)

-- an endless reservoir of variables
freshvarlist :: [String]
freshvarlist = map ("x" ++) (map show [0..])

-- fresh variable for a term
freshforterm :: LambdaTerm -> String
freshforterm t = head [x | x <- freshvarlist, notElem x (var t)]

-- the substitution operation for lambda terms
subst :: LambdaTerm -> String -> LambdaTerm -> LambdaTerm
subst (Var x) y t
    | x == y        = t
    | otherwise     = Var x
subst (Lam x s) y t
    | x == y        = Lam x s
    | elem x (fv t) = let z = freshforterm (Lam y (App s t)) in Lam z (subst (subst s x (Var z)) y t)
    | otherwise     = Lam x (subst s y t)
subst (App s u) y t = App (subst s y t) (subst u y t)

test_subst = subst (Lam "x" (App (Var "y") (Var "x"))) "y" (Var "x")

-- beta reduction in one step
beta1 :: LambdaTerm -> [LambdaTerm]
beta1 (Var x) = []
beta1 (Lam x t) = map (Lam x) (beta1 t)
beta1 (App (Lam x t) s) = (subst t x s):([App (Lam x u) s | u <- beta1 t] ++ [App (Lam x t) u | u <- beta1 s])
beta1 (App t s) = [App u s | u <- beta1 t] ++ [App t u | u <- beta1 s]

-- checks whether a term is in normal form
nf :: LambdaTerm -> Bool
nf = null . beta1

data TermTree = TermTree LambdaTerm [TermTree]
    deriving Show

-- the beta-reduction tree of a lambda term
reductree :: LambdaTerm -> TermTree
reductree t = TermTree t (map reductree (beta1 t))

-- depth-first traversal of all the leaves in a term tree
df_leaves :: TermTree -> [LambdaTerm]
df_leaves (TermTree t []) = [t]
df_leaves (TermTree _ l) = concatMap df_leaves l

-- the left-most outer-most reduction of a term
reduce :: LambdaTerm -> LambdaTerm
reduce = head . df_leaves . reductree

term1 = App (App (Lam "x" (Lam "y" (App (Var "x") (Var "y")))) (Var "z")) (Var "w")
term2 = App (Lam "x" (App (Lam "y" (Var "x")) (Var "z"))) (Var "w")

test_beta1 = df_leaves (reductree term1)
test_beta2 = df_leaves (reductree term2)

-- a branch of given length in a tree
branch :: Int -> TermTree -> Maybe [LambdaTerm]
branch 0 (TermTree t _) = Just [t]
branch n (TermTree t l) = case [br | Just br <- map (branch (n-1)) l] of
                                []    -> Nothing
                                (b:_) -> Just (t:b)
                                
testbranch1 = branch 2 (reductree term1)
                                
testbranch2 = branch 3 (reductree term1)

term_o = Lam "x" (App (Var "x") (Var "x"))
term_O = App term_o term_o

testO = reduce term_O -- should not terminate

term_b = App (App (Lam "x" (Lam "y" (Var "y"))) term_O) (Var "z")

testb = reduce term_b -- should terminate
                                
testbranch3 = branch 10 (reductree term_b)

-- Church numeral of a number
church :: Int -> LambdaTerm
church n = Lam "f" (Lam "x" (d n))
                    where d 0 = Var "x"
                          d n = App (Var "f") (d (n-1))

-- convert from Church numeral back to number
backch :: LambdaTerm -> Int
backch (Lam f (Lam x (Var y))) = 0
backch (Lam f (Lam x (App (Var g) t))) = backch (Lam f (Lam x t)) + 1

-- lambda term for successor
tsucc :: LambdaTerm 
tsucc = Lam "n" (Lam "f" (Lam "x" (App (Var "f") (App (App (Var "n") (Var "f")) (Var "x")))))

testsucc = backch ((reduce (App tsucc (church 7))))

-- lambda term for addition
tadd :: LambdaTerm
tadd = Lam "n" (Lam "m" (Lam "f" (Lam "x" (App (App (Var "n") (Var "f")) (App (App (Var "m") (Var "f")) (Var "x"))))))

testadd = backch ((reduce (App (App tadd (church 7)) (church 8))))

