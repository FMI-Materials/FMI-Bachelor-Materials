{-# OPTIONS_GHC -Wno-deferred-out-of-scope-variables #-}
import GHC.Float (divideDouble)
import Data.List
import Data.Char
--1) Sa se scrie o functie nrVocale care pentru o lista de siruri de caractere, calculeaza numarul total de vocale ce apar 
--în cuvintele palindrom. Pentru a verifica daca un sir e palindrom,puteti folosi functia reverse, iar pentru a cauta un element într-o lista puteti 
--folosi functia elem. Puteti defini oricâte functii auxiliare.
numarVocaleCuvant :: String -> Int
numarVocaleCuvant [] = 0
numarVocaleCuvant (x:xs) =
    if x `elem` "aeiouAEIOU"
        then 1 + numarVocaleCuvant xs
        else numarVocaleCuvant xs

nrVocale :: [String] -> Int
nrVocale [] = 0
nrVocale (x:xs) =
    if x == reverse x
        then numarVocaleCuvant x + nrVocale xs
        else nrVocale xs

--2)Sa se scrie o functie care primeste ca parametru un numar 
--si o lista de întregi si adauga elementul dat dupa fiecare 
--element par din lista.
--  Sa se scrie si prototipul functiei.
functie :: Int -> [Int] -> [Int]
functie _ [] = []
functie x (ls:l) = 
  if even ls 
    then [ls] ++ [x] ++ functie x l
    else [ls] ++ functie x l 


semiPareComp :: [Int] -> [Int]
semiPareComp l = [x `div` 2 | x <- l, even x]

--3)Sa se scrie o functie care are ca parametru un numar întreg  si determina lista de divizori ai  
--acestui numar. Sa se scrie s i prototipul functiei.

divizori :: Int -> [Int]
divizori x = [y | y <-[1..x], mod x y == 0]

--4)Sa se scrie o functie care are ca parametru o lista de numere întregi 
-- si calculeaza lista listelor  de divizori.
listadiv :: [Int] -> [[Int]]
listadiv [] = []
listadiv l = [ divizori x | x <- l]

--5)Scrieti o functie care date fiind limita inferioara si cea superioara (întregi) 
--a unui interval  ̆închis si o lista de numere întregi, calculeaza lista numerelor
-- din lista care apartin intervalului.
--a  doar recursie
inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec x y [] = []
inIntervalRec x y (l:ls) =
  if x <= l && l <= y
    then l : inIntervalRec x y ls
    else inIntervalRec x y ls

--b descrieri de liste
inIntervalComp :: Int ->  Int -> [Int] -> [Int]
inIntervalComp x y l = [ z | z <- l, x <= z && z <= y]

--6)Scrieti o functie care numara câte numere strict pozitive sunt într-o lista data
--  ca argument.
--a) recursiv
pozitiveRec :: [Int] -> Int
pozitiveRec [] = 0
pozitiveRec (l:ls) =
  if l > 0
    then 1 + pozitiveRec ls
    else pozitiveRec ls

--b) descrieri de liste
pozitiveComp :: [Int] -> Int
pozitiveComp [] = 0
pozitiveComp l = length [z | z <-l , z > 0]

--7)Scrieti o functie care data fiind o lista de numere calculeaza lista pozitiilor
-- elementelor impare din lista originala.

--a) recursiv -> pozitiiImpareRec
pozitii :: [Int] -> Int -> [Int]
pozitii [] poz = []
pozitii (l:ls) poz = 
  if odd l 
    then poz : pozitii ls (poz + 1)
    else pozitii ls (poz + 1)

pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec l = pozitii l 0

--b)descrieri de liste -> pozitiiImpareComp
pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp l = [ i | (i, x) <- zip [0..] l, odd x]

--8) Scrieti o functie care calculeaza produsul tuturor cifrelor care apar în  sirul 
--de caractere dat ca intrare. Daca nu sunt cifre în sir, raspunsul functiei trebuie sa 
--fie  ̆1 .
--a)Folositi doar recursie. Denumiti functia multDigitsRec
multDigitsRec :: String -> Int 
multDigitsRec "" = 1
multDigitsRec (xs:s) = 
  if xs `elem` "0123456789"
    then (ord xs + (-1) * ord '0' )* multDigitsRec s
    else multDigitsRec s
--b)Folositi descrieri de liste.. Denumiti functia multDigitsComp
multDigitsComp :: String -> Int
multDigitsComp "" = 1
multDigitsComp l = product [digitToInt z | z<-l, isDigit z ]