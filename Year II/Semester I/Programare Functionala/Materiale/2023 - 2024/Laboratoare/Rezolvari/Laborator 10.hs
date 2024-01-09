import Data.List (nub)
import Data.Maybe (fromJust)

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
  deriving (Eq, Read)
infixr 2 :<->:
infixr 3 :->:
infixr 4 :|:
infixr 5 :&:

 -- 1
p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")    

p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: (Not (Var "P") :&: Not (Var "Q"))

p3 :: Prop
p3 = (Var "P" :&: (Var "Q" :|: Var "R")) :&: ((Not (Var "P") :|: Not (Var "Q")) :&: (Not (Var "P") :|: Not (Var "R")))

-- 2
instance Show Prop where
    show (Var name) = name
    show F = "F"
    show T = "T"
    show (Not prop) = "(" ++ "~" ++ show(prop) ++ ")"
    show (prop1 :|: prop2) = "(" ++ show(prop1) ++ "|" ++ show(prop2) ++ ")"
    show (prop1 :&: prop2) = "(" ++ show(prop1) ++ "&" ++ show(prop2) ++ ")"
    show (prop1 :->: prop2) = "(" ++ show(prop1) ++ "->" ++ show(prop2) ++ ")"
    show (prop1 :<->: prop2) = "(" ++ show(prop1) ++ "<->" ++ show(prop2) ++ ")"

test_prop :: Prop
test_prop = (Not (Var "P") :&: Var "Q")

-- 3
type Env = [(Nume, Bool)]

impureLookup :: Eq a => a -> [(a, b)] -> b
impureLookup a = fromJust . lookup a

eval :: Prop -> Env -> Bool
eval (Var name) truth_values = impureLookup name truth_values
eval (Not prop) truth_values = not (eval prop truth_values)
eval (prop1 :|: prop2) truth_values = (eval prop1 truth_values) || (eval prop2 truth_values)
eval (prop1 :&: prop2) truth_values = (eval prop1 truth_values) && (eval prop2 truth_values)
eval (prop1 :->: prop2) truth_values = not (eval prop1 truth_values) || (eval prop2 truth_values)
eval (prop1 :<->: prop2) truth_values = eval prop1 truth_values == eval prop2 truth_values
eval F _ = False
eval T _ = True

test_eval :: Bool
test_eval = eval  (Var "P" :|: Var "Q") [("P", True), ("Q", False)]

-- 4
variabile :: Prop -> [Nume]
variabile (Var name) = [name]
variabile (Not prop) = variabile prop
variabile (prop1 :|: prop2) = nub (variabile prop1 ++ variabile prop2)
variabile (prop1 :&: prop2) = nub (variabile prop1 ++ variabile prop2)
variabile (prop1 :->: prop2) = nub (variabile prop1 ++ variabile prop2)
variabile (prop1 :<->: prop2) = nub (variabile prop1 ++ variabile prop2)
variabile _ = []

test_variabile :: [Nume]
test_variabile = variabile (Not (Var "P") :&: Var "Q")

-- 5
envs :: [Nume] -> [Env]
envs [] = [[]]
envs (h:t) = let done = envs t in (map (\x -> (h, False) : x) done) ++ (map (\x -> (h, True) : x) done)

test_envs :: [Env]
test_envs = envs ["P", "Q"] 

-- 6
satisfiabila :: Prop -> Bool
satisfiabila prop1 = let values = envs (variabile prop1) in foldr (||) False (map (eval prop1) values)

test_satisfiabila1 :: Bool
test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q")
test_satisfiabila2 :: Bool
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P")

-- 7
valida :: Prop -> Bool
valida prop = satisfiabila (Not prop) == False

test_valida1 :: Bool
test_valida1 = valida (Not (Var "P") :&: Var "Q")
test_valida2 :: Bool
test_valida2 = valida (Not (Var "P") :|: Var "P")

-- 10
echivalenta :: Prop -> Prop -> Bool
echivalenta prop1 prop2 = foldr (&&) True (map (\x -> eval prop1 x == eval prop2 x) values)
    where values = envs (variabile (prop1 :&: prop2))

test_echivalenta1 :: Bool
test_echivalenta1 = (Var "P" :&: Var "Q") `echivalenta` (Not (Not (Var "P") :|: Not (Var "Q")))
test_echivalenta2 :: Bool
test_echivalenta2 = (Var "P") `echivalenta` (Var "Q")
test_echivalenta3 :: Bool
test_echivalenta3 = (Var "R" :|: Not (Var "R")) `echivalenta` (Var "Q" :|: Not (Var "Q"))