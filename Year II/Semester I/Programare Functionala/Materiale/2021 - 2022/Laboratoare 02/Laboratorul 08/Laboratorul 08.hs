import System.Win32 (COORD(yPos))
import Data.Maybe
import Data.List
-- LOGICA PROPOZITIONALA

type Nume = String
data Prop = Var Nume | F | T | Not Prop | Prop :|: Prop | Prop :&: Prop
    deriving Eq
infixr 2 :|:
infixr 3 :&:

-- 1. Scrieti urmatoarele formule ca expresii de tip Prop

-- a. (P ∨ Q) ∧ (P ∧ Q)
p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

-- b. (P ∨ Q) ∧ (¬P ∧ ¬Q)
p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: (Not (Var "P") :&: Not (Var "Q"))

-- c. (P ∧ (Q ∨ R)) ∧ ((¬P ∨ ¬Q) ∧ (¬P ∨ ¬R))
p3 :: Prop
p3 = (Var "P" :&: (Var "Q" :|: Var "R")) :&: ((Not (Var "P") :|: Not (Var "Q")) :&: (Not (Var "P") :|: Not (Var "R")))

-- 2. Faceti tipul Prop instanta a clasei de tipuri Show
-- înlocuind conectivele Not, :|: si :&: cu ~, | si &
-- si folosind direct numele variabilelor in loc de Var nume

instance Show Prop where
    show (Var x) = x
    show (Not x) = "(~" ++ show x ++ ")"
    show (x :|: y) = "(" ++ show x ++ " | " ++ show y ++ ")"
    show (x :&: y) =  "(" ++ show x ++ " & " ++ show y ++ ")"
    show F = "False"
    show T = "True"

--- EVALUAREA EXPRESIILOR LOGICE

-- mediu de evaluare care asociaza valori
-- de tip Bool variabilelor propozitionale
type Env = [(Nume, Bool)]

-- Pentru a obtine valoarea asociata unui Nume in Env
-- vom folosi o functie care genereaza o eroare daca
-- nu gasesc 0 valoare asociata
impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a

-- 3. functie care primeste o expresie logica si un mediu de
-- evaluare si calculeaza valoarea de adevar a expresiei

eval :: Prop -> Env -> Bool
eval F _ = False
eval T _ = True
eval (Var x) y = impureLookup x y
eval (Not x) y = not (eval x y)
eval (x :|: y) z = eval x z || eval y z
eval (x :&: y) z = eval x z && eval y z

-- SATISFIABILITATE

-- 4. functie care colecteaza lista tuturor
-- variabilelor dintr-o formula data

variabile' :: Prop -> [Nume]
variabile' F = []
variabile' T = []
variabile' (Var x) = [x]
variabile' (Not x) = variabile' x
variabile' (x :|: y) = variabile' x ++ variabile' y
variabile' (x :&: y) = variabile' x ++ variabile' y

variabile :: Prop -> [Nume]
variabile x = nub (variabile' x)

-- 5. data fiind o lista de nume sa se atribuie toate
-- valorile de adevar posibile pentru ea

produsCartezian :: [a] -> Int -> [[a]]
produsCartezian a 1 = [[x] | x <- a]
produsCartezian a n = [x : b | x <- a, b <- produsCartezian a (n - 1)]


envs :: [Nume] -> [Env]
envs [] = []
envs nume = [zip nume val | val <- produsCartezian [False, True] (length nume)]

-- 6 functie care verifica daca o propozitie este satisfiabila
-- adica daca exista valori astfel incat formula sa fie True

satisfiabila :: Prop -> Bool
satisfiabila p = or [y| x <- envs (variabile p), let y = eval p x]

-- 7

-- 8

-- 9

-- 10