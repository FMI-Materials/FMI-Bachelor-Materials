
-- map (\x -> 2 * x) [1..10] = [2,4,6,8,10,12,14,16,18,20]
-- map (1 `elem`) [[2,3], [1,2]] = [False, True]
-- map (`elem` [2,3]) [1,3,4,5] = [False,True,False,False]

-- exercitii

-- 1. Scrieti o functie generică firstEl care are ca argument o listă de perechi 
-- de tip (a,b) si întoarce lista primelor elementelor din fiecare pereche:
-- firstEl [('a',3),('b',2), ('c',1)] => "abc"

firstEl :: [(a,b)] -> [a]
firstEl = map fst

-- 2.Scrieti functia sumList care are ca argument o listă de liste de valori
-- Int si întoarce lista sumelor elementelor din fiecare listă (suma elementelor
-- unei liste de întregi se calculează cu functia sum):

sumList :: [[Int]] -> [Int]
sumList = map sum

-- 3.3. Scrieti o functie prel2 care are ca argument o listă de Int si
-- întoarce o listă în care elementele pare sunt înjumătătite, 
-- iar cele impare sunt dublate:

prel2 :: [Int] -> [Int]
prel2 = map (\x -> if odd x then 2 *x else x `div` 2)

-- 4. Scrieti o functie care primeste ca argument un caracter si o listă 
-- de siruri rezultatul fiind lista sirurilor care contin caracterul
-- respectiv (folositi functia elem).

functie :: Char -> [String] -> [String]
functie x = filter (x `elem`)

-- 5. Scrieti o functie care primeste ca argument o listă de întregi si
-- întoarce lista pătratelor numerelor impare.

functie2 :: [Int] -> [Int]
functie2 l = map (\x -> if odd x then x * x else x) l

-- 6.Scrieti o functie care primeste ca argument o listă de întregi 
-- si întoarce lista pătratelor numerelor din pozitii impare. 
-- Pentru a avea acces la pozitia elementelor folositi zip.

functie3 :: [Int] -> [Int]
functie3 l = map (\(a,b) -> a * a) (filter (odd . snd) (zip l [1..length l]))

-- 7. Scrieti o functie care primeste ca argument o listă de siruri de 
-- caractere si întoarce lista obtinută prin eliminarea consoanelor din 
-- fiecare sir.
charToString :: Char -> String
charToString c = [c]

aux :: String -> String
aux "" = ""
aux (xs:s) =
    if xs `elem` "aeiouAEIOU"
        then charToString xs ++ aux s
        else aux s
numaiVocale :: [String] -> [String]
numaiVocale s = map (aux) s

-- 8. Definiti recursiv functiile mymap si myfilter cu aceeasi functionalitate
-- ca si functiile predefinite.

mymap :: (a -> b) -> [a] -> [b]
mymap fct [] = []
mymap fct (x:xs) = fct x : mymap fct xs

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter fct [] = []
myfilter fct (x:xs) =
    if fct x
        then x : myfilter fct xs
        else myfilter fct xs

-- 9. Calculati suma pătratelor elementelor impare dintr-o listă dată ca parametru.

sumImpare :: [Int] -> Int
sumImpare l = foldr (+) 0  ( filter (odd) l)

-- 10. Scrieti o functie care verifică faptul că toate elementele dintr-o 
-- listă sunt True, folosind foldr.

verif :: [Bool] -> Bool
verif l = foldr (&&) True l

-- 11.
-- (a) Scrieti o functie care elimină un caracter din sir de caractere.

rmChar :: Char -> String -> String
rmChar a s = filter (/= a) s

-- (b) Scrieti o functie recursivă care elimină toate caracterele din al 
-- doilea argument care se găsesc în primul argument, folosind rmChar.

rmCharsRec :: String -> String -> String
rmCharsRec [] b = b
rmCharsRec a [] = []
rmCharsRec (x:xa) b =
    if x `elem` b
        then rmCharsRec xa (rmChar x b)
        else rmCharsRec xa b

-- (c) Scrieti o functie echivalentă cu cea de la (b) care foloseste
-- foldr în locul recursiei si rmChar.

rmCharsFold :: String -> String -> String
rmCharsFold a b = foldr rmChar b a

