data Fruct = Mar String Bool | Portocala String Int

-- 1.a functie care indica daca e o portocala de Sicilia sau nu
-- stiind ca soiurile de Sicilia sunt: Tarocco, Moros si Sanguinello

ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Mar _ _) = False
ePortocalaDeSicilia (Portocala soi felii) =
    soi == "Tarocco" || soi == "Moro" || soi == "Sanguinello"

-- 1.b functie care calculeaza numarul total de felii al
-- portocalelor de Sicilia dintr-o lista de fructe

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

nrFelii :: Fruct -> Int
nrFelii (Portocala soi felii) = felii
nrFelii (Mar soi bool) = 0

nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia [] = 0
nrFeliiSicilia (h:t) = if ePortocalaDeSicilia h then nrFeliiSicilia t + nrFelii h
                        else nrFeliiSicilia t

-- 1.c functie care calculeaza numarul de mere care au viermi

areViermi :: Fruct -> Bool
areViermi (Portocala soi felii) = False
areViermi (Mar soi bool) = bool

nrMereViermi :: [Fruct] -> Int
nrMereViermi [] = 0
nrMereViermi (h:t) = if areViermi h then 1 + nrMereViermi t else nrMereViermi t

---

type NumeA = String
type Rasa = String
data Animal = Pisica NumeA | Caine NumeA Rasa
    deriving Show

-- 2.a scrieti o functie care intoace Meow
-- pentru pisica, Woof pentru caine

vorbeste :: Animal -> String
vorbeste (Pisica _) = "Meow!"
vorbeste (Caine _ _) = "Woof!"

-- tipul Maybe
-- data Maybe a = Nothing | Just a

-- 2.b functie care intoarce rasa daca
-- este caine sau Nothing daca e pisica

rasa :: Animal -> Maybe String
rasa (Pisica _) = Nothing
rasa (Caine _ rasaCaine) = Just rasaCaine

---

data Linie = L [Int]
    deriving Show
data Matrice = M [Linie]
    deriving Show

-- 3.a functie care verifica daca suma elementelor
-- de pe fiecare linie este egala cu o valoare n

verifica :: Matrice -> Int -> Bool
verifica (M []) _ = True
verifica (M (h:t)) n
    | sum l == n = verifica (M t) n
    | otherwise = False
    where L l = h

-- 3.b functie care primeste o matrice si un numar n
-- si verifica daca toate liniile de lungime n
-- din matrice au numai elemente strict pozitive

pozitive :: Linie -> Bool
pozitive (L []) = True
pozitive (L (h:t)) = if h > 0 then pozitive (L t) else False

doarPozN :: Matrice -> Int -> Bool
doarPozN (M []) n = True
doarPozN (M (h:t)) n
    | length l == n && pozitive h  = doarPozN (M t) n
    | length l /= n  = doarPozN (M t) n
    | otherwise = False
    where L l = h

-- 3.c functie care verifica daca toate
-- liniile unei matrice sunt egale

corect :: Matrice -> Bool
corect (M []) = True
corect (M [x]) = True
corect (M ((L h):(L m):t))
    | length h == length m = corect (M ((L m):t))
    | otherwise = False