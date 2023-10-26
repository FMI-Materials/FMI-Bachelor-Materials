{-# LANGUAGE InstanceSigs #-}

-- MODEL EXAMEN

-- 1. grile

-- 1. a
-- 2. c
-- 3. a
-- 4. a
-- 5. a
-- 6. a
-- 7. a
-- 8. a
-- 9. a
-- 10. a

-- 2.1 cel mai lung prefix comun

prefix :: String -> String -> String
prefix [] [] = []
prefix _ [] = []
prefix [] _ = []
prefix (h1:t1) (h2:t2) = if h1 == h2 then h1 : prefix t1 t2
                        else prefix [] []

-- 2.2 functie de calcul

calcul :: [Int] -> [Int] -> Int
calcul [] [] = 0
calcul [] ys = error "eroare"
calcul xs [] = error "eroare"
calcul (x:xs) (y:ys) = (x ^ 2) * (y ^ 2) + calcul xs ys

calculZip :: [Int] -> [Int] -> Int
calculZip x y = if length x /= length y then error "eroare"
                else sum [a^2 * b^2 | (a,b) <- zip x y]

---

data PairInt = P Int Int
    deriving Show

data MyList = L [PairInt]
    deriving Show

data Exp = I Int | Add Exp Exp | Mul Exp Exp
    deriving Show

class MyClass m where
    toExp :: m -> Exp

-- 3.1 functie care primeste o lista de perechi
-- si o transforma in expresie punand operatia Add
-- intre elementele unei perechi si Mul intre perechi

instance MyClass MyList where
    toExp :: MyList -> Exp
    toExp (L []) = I 1
    toExp (L ((P h1 h2):t)) = Mul (Add (I h1) (I h2)) (toExp (L t))

-- 3.2 functie care primeste o lista de perechi,
-- transforma lista in expresie si apoi o evalueaza

evalExp :: Exp -> Int 
evalExp (I n) =  n
evalExp (Add e1 e2) = evalExp e1 + evalExp e2
evalExp (Mul e1 e2) = evalExp e1 * evalExp e2

eval :: MyList -> Int
eval (L l) = evalExp (toExp (L l))