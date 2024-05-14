data PCFTerm = Var String | Lam String PCFTerm | App PCFTerm PCFTerm | Zero | Suc PCFTerm | IfZ PCFTerm PCFTerm String PCFTerm | Fix String PCFTerm
    deriving Show

-- union of two sets represented as lists
union2 :: (Eq a) => [a] -> [a] -> [a]
union2 x y = x ++ [z | z <- y, notElem z x]

-- variables of a PCF term
var :: PCFTerm -> [String]
var = undefined

-- free variables of a PCF term
fv :: PCFTerm -> [String]
fv = undefined

-- an endless reservoir of variables
freshvarlist :: [String]
freshvarlist = map ("x" ++) (map show [0..])

-- fresh variable for a PCF term
freshforterm :: PCFTerm -> String
freshforterm t = head [x | x <- freshvarlist, notElem x (var t)]

-- the substitution operation for PCF terms
subst :: PCFTerm -> String -> PCFTerm -> PCFTerm
subst (Var x) y t
    | x == y        = t
    | otherwise     = Var x
subst (Lam x s) y t
    | x == y        = Lam x s
    | elem x (fv t) = let z = freshforterm (Lam y (App s t)) in Lam z (subst (subst s x (Var z)) y t)
    | otherwise     = Lam x (subst s y t)
subst (App s u) y t = App (subst s y t) (subst u y t)
subst Zero _ _      = Zero
subst (Suc s) y t   = Suc (subst s y t)
subst (IfZ n s w u) y t
    | w == y        = IfZ (subst n y t) (subst s y t) w u
    | elem w (fv t) = let z = freshforterm (Fix y (App u t)) in IfZ (subst n y t) (subst s y t) z (subst (subst u w (Var z)) y t)
    | otherwise     = IfZ (subst n y t) (subst s y t) w (subst u y t)
subst (Fix x s) y t
    | x == y        = Fix x s
    | elem x (fv t) = let z = freshforterm (Fix y (App s t)) in Fix z (subst (subst s x (Var z)) y t)
    | otherwise     = Fix x (subst s y t)

-- eager isValue
isValueE :: PCFTerm -> Bool
isValueE = undefined

-- eager beta reduction in one step
beta1E :: PCFTerm -> Maybe PCFTerm
beta1E = undefined

-- the ultimate reduction of a term
reduceE :: PCFTerm -> PCFTerm
reduceE = undefined

-- natural numbers in PCF
number :: Int -> PCFTerm
number 0 = Zero
number n = Suc (number (n-1))

-- conversion from PCF back to natural numbers
backnr :: PCFTerm -> Int
backnr Zero = 0
backnr (Suc n) = (backnr n) + 1

-- PCF term for addition
tadd :: PCFTerm
tadd = undefined

testadd = backnr (reduceE (App (App tadd (number 2)) (number 3)))

-- PCF term for subtraction
tsub :: PCFTerm
tsub = undefined

testsub1 = backnr (reduceE (App (App tsub (number 15)) (number 8)))

testsub2 = backnr (reduceE (App (App tsub (number 7)) (number 8)))

-- PCF term for GCD
tgcd :: PCFTerm
tgcd = undefined

testgcd = backnr (reduceE (App (App tgcd (number 30)) (number 36)))

-- PCF term for minimization
tmu :: PCFTerm
tmu = undefined

testmu1 = backnr (reduceE (App tmu (Lam "x" (App (App tsub (number 15)) (Var "x")))))
testmu2 = backnr (reduceE (App tmu (Lam "x" (App (App tadd (number 15)) (Var "x"))))) -- should not terminate