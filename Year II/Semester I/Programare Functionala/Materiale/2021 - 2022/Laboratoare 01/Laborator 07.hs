
-- Exercitiul 1

data Fruct
  = Mar String Bool
  | Portocala String Int

ionatanFaraVierme = Mar "Ionatan" False
goldenCuVierme = Mar "Golden Delicious" True
portocalaSicilia10 = Portocala "Sanguinello" 10
listaFructe = [Mar "Ionatan" False,
                Portocala "Sanguinello" 10,
                Portocala "Valencia" 22,
                Mar "Golden Delicious" True,
                Portocala "Sanguinello" 15,
                Portocala "Moro" 12,
                Portocala "Tarocco" 3,
                Portocala "Moro" 12,
                Portocala "Valencia" 2,
                Mar "Golden Delicious" False,
                Mar "Golden" False,
                Mar "Golden" True]


-- a) Scrieti o functie care indica daca un frunct este o portocala de Sicilia sau nu
ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Mar _ _ ) = False
ePortocalaDeSicilia (Portocala soi felii)
    | soi == "Tarocco" || soi == "Moro" || soi == "Sanguinello" = True
    | otherwise = False

test_ePortocalaDeSicilia1 =
    ePortocalaDeSicilia (Portocala "Moro" 12)
test_ePortocalaDeSicilia2 =
    not (ePortocalaDeSicilia (Mar "Ionatan" True))


-- b) Scrieti o functie care calculeaza numarul total de felii ale portocalelor de Sicilia dintr-o lista de fructe
nrFeliiPortocala :: Fruct -> Int
nrFeliiPortocala (Portocala _ felii) = felii

nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia [] = 0
nrFeliiSicilia (x : l)
    | ePortocalaDeSicilia(x) == True = nrFeliiPortocala(x) + nrFeliiSicilia l
    | ePortocalaDeSicilia(x) == False  = 0 + nrFeliiSicilia l
    | otherwise = 0 + nrFeliiSicilia l

test_nrFeliiSicilia = nrFeliiSicilia listaFructe == 52


-- c) Scrieti o functie care calculeaza numarul de mere care au viermi dintr-o lista de fructe

nrMereViermi :: [Fruct] -> Int
nrMereViermi [] = 0
nrMereViermi ((Portocala _ _) : l) = nrMereViermi l
nrMereViermi ((Mar soi vierme) : l)
    | vierme == True = 1 + nrMereViermi(l)
    | otherwise = 0 + nrMereViermi(l)


nrMereViermi1 :: [Fruct] -> Int
nrMereViermi1 list = length [ b | Mar s b <- list , b ]

test_nrMereViermi = nrMereViermi listaFructe == 2


-- Exercitiul 2

type NumeA = String
type Rasa = String
data Animal = Pisica NumeA | Caine NumeA Rasa
    deriving Show

-- a) Scrieti o functie care intoare "Meow!" pentru pisica si "Woof!" pentru caine

vorbeste :: Animal -> String
vorbeste (Pisica _) = "Meow!"
vorbeste (Caine _ _) = "Woof!"

-- b) Va reamintiti tipul de date predefinit Maybe care intoarce rasa unui caine dat ca parametru
-- sau Nothing daca parametrul este o pisica.

rasa :: Animal -> Maybe String
rasa (Pisica _) = Nothing
rasa (Caine _ rasa) = Just rasa


-- Exercitiul 3

data Linie = L [Int]
   deriving Show
data Matrice = M [Linie]
   deriving Show

-- a) Scrieti o functie care verifica daca suma elementelor de pe fiecare linie este egala cu o valoare n.
-- Rezolvati cerinta folosind foldr.

verifica :: Matrice -> Int -> Bool
verifica (M m) n = foldr( \(L line) result -> result && (foldr (+) 0 line) == n) True m

verifica1 :: Matrice -> Int -> Bool 
verifica1 (M m) n = foldr (\result curent -> result && curent) True  (map (\(L line) -> sum line == n) m)


test_verif1 = not (verifica1 (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 10)
test_verif2 = verifica1 (M[L[2,20,3], L[4,21], L[2,3,6,8,6], L[8,5,3,9]]) 25


test_verif11 = not (verifica (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 10)
test_verif22 = verifica (M[L[2,20,3], L[4,21], L[2,3,6,8,6], L[8,5,3,9]]) 25


-- b) Scrieti o functie doarPozN care are ca parametru un element de tip Matrice si un
-- numar intreg n, si care verifica daca toate liniile de lungime n din matrice au
-- numai elemente strict pozitive.
verif :: Linie -> Int -> Bool 
verif (L line) n =
    if length line == n
        then length (filter (>0) line) == n
        else True 
doarPozN :: Matrice -> Int -> Bool
doarPozN (M m) n = foldr( \(L line) result -> result && verif (L line) n) True m

testPoz1 = doarPozN (M [L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3

testPoz2 = not (doarPozN (M [L[1,2,-3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3)


-- c) Definiti predicatul corect care verifică dacă toate liniile dintr-o matrice au aceeasi lungime.


corect :: Matrice -> Bool
corect (M []) = True 
corect (M [x]) = True
corect (M (x:y:lines)) = 
    if (length first) == (length second)
        then True && corect (M (y:lines))
        else False 
    where 
        first = (\(L x) -> x) x
        second = (\(L y) -> y) y

testcorect1 = not (corect (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]))
testcorect2 = corect (M[L[1,2,3], L[4,5,8], L[3,6,8], L[8,5,3]])

-- factorial :: Int -> Int 
-- factorial 0 = 1
-- factorial n = n * factorial(n-1)

-- combinari :: Int -> Int -> Int 
-- combinari n k = (factorial n) `div` ((factorial k) * factorial(n - k))

-- functie :: Int -> [Int] -> Int 
-- functie n [] = 0
-- functie n (x:xs) = combinari n x * (x^n) + functie n xs
