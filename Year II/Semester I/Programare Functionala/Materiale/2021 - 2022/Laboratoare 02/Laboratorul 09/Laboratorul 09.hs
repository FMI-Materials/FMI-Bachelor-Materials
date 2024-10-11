{-# LANGUAGE InstanceSigs #-}
-- EXERCITII SUPLIMENTARE

-- 1.a functie care numara cate propozitii sunt intr-un text dat

sfChr :: Char -> Bool
sfChr c =  c `elem` ".!?:"

nrPropozitii :: String -> Int
nrPropozitii [] = 0
nrPropozitii (h:t) = if sfChr h then 1 + nrPropozitii t else nrPropozitii t

-- 1.b acelasi exercitiu cu metoda prin selectie

nrPropSelectie :: String -> Int
nrPropSelectie s = sum [if sfChr x then 1 else 0 | x <- s]

-- 2. functie care primeste o matrice de numere intregi si un numar n
-- si verifica daca toate liniile de lungime n au elementele strict pozitive

liniiN :: [[Int]] -> Int -> Bool
liniiN [] n = True
liniiN (h:t) n
    | length (filter (> 0) h) == n = liniiN t n
    | otherwise = False

---

-- puncte cu numarul variabil de coordonate
data Punct = Pt [Int]
    deriving Show

-- arbori cu informatia in frunze
data Arb = Vid | F Int | N Arb Arb
    deriving Show

arbore = N (N (F 3) (Vid)) (F 5)

class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a

-- 3. sa se scrie o instanţă a clasei ToFromArb pentru tipul de date Punct
-- astfel incat lista coordonatelor punctului sa coincidă cu frontiera arborelui

instance ToFromArb Punct where
    toArb :: Punct -> Arb
    toArb (Pt []) = Vid
    toArb (Pt (x:xs)) = N (F x) (toArb (Pt xs))
    fromArb :: Arb -> Punct
    fromArb Vid = Pt []
    fromArb (F x) = Pt [x]
    fromArb (N arb1 arb2) = let (Pt x) = fromArb arb1; (Pt y) = fromArb arb2 in Pt (x ++ y)