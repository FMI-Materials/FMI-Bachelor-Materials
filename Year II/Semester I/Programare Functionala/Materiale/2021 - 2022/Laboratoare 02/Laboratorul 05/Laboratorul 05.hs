-- FUNCTII DE NIVEL INALT: MAP, FILTER, FOLDR

-- 1. primeste o lista de perechi si returneaza
-- primele elemente din fiecare pereche

firstEl :: [(a,b)] -> [a]
firstEl = map fst

-- 2. primeste o lista de liste si returneaza
-- o lista cu sume elementelor din fiecare lista

sumList :: [[Int]] -> [Int]
sumList = map sum

-- 3. primeste o lista si returneaza lista ce elementele
-- pare injumatatire si cele impare dublate

prel2 :: [Int] -> [Int]
prel2 = map (\x -> if even x then x `div` 2 else x * 2)

-- 4. primeste un caracter si o lista de siruri si
-- returneaza sirurile ce contin acel caracter

contineCaracter :: Char -> [String] -> [String]
contineCaracter c = filter (c `elem`)

-- 5. primeste o lista de intregi si returneaza
-- lista patratelor numerelor impare

patratImp :: [Int] -> [Int]
patratImp ls = map (^2) (filter odd ls)

-- 6. primeste ca argument o listă de întregi si întoarce
-- lista pătratelor numerelor din pozitii impare

patratPozImp :: [Int] -> [Int]
patratPozImp x = map (^2) ([a | (a,b) <- zip x [1..], odd b])

-- 7. primeste ca argument o listă de siruri de caractere si întoarce
-- lista obtinută prin eliminarea consoanelor din fiecare sir

numaiVocale :: [[Char]] -> [[Char]]
numaiVocale = map (filter(`elem` "aeiouAEIOU"))

-- 8. functiile mymap si myfilter definite recursiv
-- cu aceiasi functionalitate ca si functiile predefinite

mymap :: (a -> b) -> [a] -> [b]
mymap f [] = []
mymap f (h:t) = f h : mymap f t

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter f [] = []
myfilter f (h:t) = if f h then h : myfilter f t else myfilter f t

-- 9. calculati suma patratelor elementelor impare
-- dintr-o lista data ca parametru

sumPatrateImpare :: [Int] -> Int
sumPatrateImpare ls = sum (map (^2) (filter odd ls))

-- 10. functie care verifică faptul că toate
-- elementele dintr-o listă sunt True

allTrue :: [Bool] -> Bool
allTrue = foldr (&&) True

-- 11.a functie care elimina un caracter dintr-un sir

rmChar :: Char -> String -> String
rmChar ch = filter (/= ch)

-- 11.b functie recursiva care elimina toate caracterele din
-- al doilea argument care se gasesc in primul argument

rmCharsRec :: String -> String -> String
rmCharsRec a = filter (`notElem` a)

-- 11.c echivalent cu b dar foloseste foldr

rmCharsFold :: String -> String -> String
rmCharsFold a b = foldr rmChar b a