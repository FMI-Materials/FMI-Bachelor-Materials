{-# LANGUAGE InstanceSigs #-}

-- Exercitiul 1
-- a) Scrieti o functie care numără câte propozitii sunt într-un text dat.
-- Puteti scrie o functie auxiliară sfChr care verifică dacă un caracter e sfârsit de propozitie.
-- Considerăm semne de sfarsit de propozitie: punct ‘.’, semnul intrebarii ‘?’, semnul
-- exclamarii ‘!’, doua puncte ‘:’. In rezolvarea exercitiului puteti folosi doar recursie
-- si sfChr, fara metoda prin selectie sau functii de nivel inalt.

sfChr :: Char -> Bool
sfChr x =
    x == '.' || x == '?' || x == '!' || x == ':'

numara :: String -> Int
numara "" = 0
numara (x : xs)  =
    if sfChr x
        then 1 + numara xs
    else numara xs
-- b) Rezolvati acelasi exercitiu folosind doar metoda prin selectie.

numara_selectie :: String -> Int
numara_selectie l = length [x | x <- l, sfChr x]


-- Exercitiul 2
-- Scrieti o functie linii N care are ca parametru o matrice de numere 
-- întregi ([[Int]]) si un număr întreg n, si verifică dacă toate liniile
-- de lungime n din matrice au doar elemente strict pozitive. 
-- In rezolvarea exercitiului folositi functii de nivel inalt.

data Linie = L [Int]
   deriving Show
data Matrice = M [Linie]
   deriving Show

verifica :: Matrice -> Int -> Bool
verifica (M m) n = foldr(\(L line) result -> result && length(filter (>0) line) == n) True m

test_verifica = verifica (M[L[1,2,3], L[2,3,4], L[-1,-2,3],L[1,2,3]]) 3 

test_verifica1 = verifica (M[L[1,2,3], L[2,3,4], L[1,2,3],L[1,2,3]]) 3 

-- Exercitiul 3
-- Se dau următoarele tipuri de date ce reprezinta puncte cu numar variabil de coordonate
-- intregi:
data Punct = Pt [Int]
    deriving (Show, Eq)
--Arbori cu informatia în frunze 
-- şi clasă de tipuri ToFromArb

data Arb = Vid | F Int | N Arb Arb
    deriving (Show, Eq)

class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a
-- Să se scrie o instanţă a clasei ToFromArb pentru tipul de date Punct astfel incat lista
-- coordonatelor punctului sa coincidă cu frontiera arborelui.
-- toArb (Pt [1,2,3]) N (F 1) (N (F 2) (N (F 3) Vid))
-- fromArb $ N (F 1) (N (F 2) (N (F 3) Vid)) :: Punct
-- Pt [1,2,3]
(*++*) :: Punct -> Punct -> Punct
Pt l1 *++* Pt l2 = Pt (l1 ++ l2)

instance (ToFromArb Punct) where
    toArb :: Punct -> Arb
    toArb (Pt []) = Vid
    toArb (Pt (x:xs)) = N (F x) (toArb (Pt xs))

    fromArb :: Arb -> Punct
    fromArb Vid = Pt []
    fromArb (F x) = Pt [x]
    fromArb (N ram1 ram2) = fromArb ram1 *++* fromArb ram2

test_toArb :: Bool 
test_toArb = toArb (Pt[1, 2, 3]) == N (F 1) (N (F 2) (N (F 3) Vid))


test_fromArb :: Bool 
test_fromArb = fromArb(N (F 1) (N (F 2) (N (F 3) Vid))) == Pt[1, 2, 3]

