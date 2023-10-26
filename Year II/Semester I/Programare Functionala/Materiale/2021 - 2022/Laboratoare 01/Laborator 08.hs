import Data.Maybe
import Data.List
import GHC.Exts.Heap (GenClosure(var))
import Distribution.Simple.Utils (xargs)
type Nume = String
data Prop
    = Var Nume
    | F
    | T
    | Not Prop
    | Prop :|: Prop
    | Prop :&: Prop
    | Prop :->: Prop
    | Prop :<->: Prop
    deriving Eq
infixr 2 :|:
infixr 3 :&:

-- 1. Scrieti următoarele formule ca expresii de tip Prop, denumindu-le p1, p2, p3.
-- 1. (P ∨ Q) ∧ (P ∧ Q)
p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

-- 2. (P ∨ Q) ∧ (¬P ∧ ¬ Q)
p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: (Not (Var "P") :&: Not (Var "Q"))

-- 3. (P ∧ (Q ∨ R)) ∧ ((¬P ∨ ¬Q) ∧ (¬P ∨ ¬R))
p3 :: Prop
p3 = (Var "P" :&: (Var "Q" :|: Var "R")) :&: ((Not (Var "P") :|: Not (Var "Q")) :&: (Not (Var "P") :|: Not (Var "R")))

-- Ex 2
instance Show Prop where
    show (Var nume) = nume
    show (a :|: b) = "(" ++ show a ++ "|" ++ show b ++ ")"
    show (a :&: b) = "(" ++ show a ++ "&" ++ show b ++ ")"
    show (Not a) = "(~" ++ show a ++ ")"
    show (a :->: b) = "(" ++ show a ++ "->" ++ show b ++ ")"
    show (a :<->: b) = "(" ++ show a ++ "<->" ++ show b ++ ")"
    show F = "F"
    show T = "T"

test_ShowProp :: Bool
test_ShowProp = show (Not (Var "P") :&: Var "Q") == "((~P)&Q)"

-- Ex3

type Env = [(Nume, Bool)]

impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a

impl :: Bool -> Bool -> Bool 
impl False _ = True 
impl _ x = x

echiv :: Bool -> Bool -> Bool 
echiv x y = x == y

eval :: Prop -> Env -> Bool
eval (Var x) env = impureLookup x env
eval T _ = True 
eval F _ = False
eval (Not p) env = not (eval p env)
eval (p :&: q) env = (eval p env) && (eval q env)
eval (p :|: q) env = (eval p env) || (eval q env)
eval (p :->: q) env = (eval p env) `impl` (eval q env)
eval (p :<->: q) env = (eval p env) `echiv` (eval q env)
 
test_eval = eval  (Var "P" :|: Var "Q") [("P", True), ("Q", False)] == True

variabile :: Prop -> [Nume]
variabile (Var p) = [p]
variabile (Not p) = nub (variabile p)
variabile (p :&: q) = nub (variabile p ++ variabile q)
variabile (p :|: q) = nub (variabile p ++ variabile q)
variabile (p :->: q) = nub (variabile p ++ variabile q)
variabile (p :<->: q) = nub (variabile p ++ variabile q)
variabile _ = []

 
test_variabile =
  variabile (Not (Var "P") :&: Var "Q") == ["P", "Q"]

-- Ex 5

envs :: [Nume] -> [Env]
envs [] = []
envs [x] = [[(x, True)], [(x, False)]]
envs (str:xs) = let r = envs xs in  map (\x-> (str,False):x) r  ++ map (\x->(str,True):x) r
 
test_envs = 
    envs ["P", "Q"]
    ==
    [ [ ("P",False)
      , ("Q",True)
      ]
    , [ ("P",False)
      , ("Q",False)
      ]
    , [ ("P",True)
      , ("Q",True)
      ]
    , [ ("P",True)
      , ("Q",False)
      ]
    ]

-- Ex 6

satisfiabila :: Prop -> Bool
satisfiabila p = or (map (eval p) (envs (variabile p)))
 
test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q") == True
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P") == False

-- Ex 7

valida :: Prop -> Bool
valida p = satisfiabila (Not p) == False

test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 = valida (Not (Var "P") :|: Var "P") == True

-- Ex 9 & 10

echivalenta :: Prop -> Prop -> Bool
echivalenta p q = all (\env -> eval (p :<->: q) env) (envs (nub (variabile p ++ variabile q)))
 
test_echivalenta1 = True == (Var "P" :&: Var "Q") `echivalenta` (Not (Not (Var "P") :|: Not (Var "Q")))
test_echivalenta2 = False == (Var "P") `echivalenta` (Var "Q")
test_echivalenta3 = True == (Var "R" :|: Not (Var "R")) `echivalenta` (Var "Q" :|: Not (Var "Q"))