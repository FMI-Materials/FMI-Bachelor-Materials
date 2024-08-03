import Data.Char (digitToInt, isDigit)

-- RECURSIVITATE PE LISTE

-- 1. functie care calculeaza numarul total de vocale
-- al cuvintelor palindrom dintr-o lista de cuvinte

-- verifica daca un sir e palindrom
palindrom :: [Char] -> Bool
palindrom str = str == reverse str

-- calculeaza numarul de vocale dintr-un sir
vocale :: [Char] -> Int
vocale [] = 0
vocale str = if head str `elem` ['a','e','i','o','u'] then vocale (tail str) + 1 else vocale (tail str)

nrVocale :: [String] -> Int
nrVocale [] = 0
nrVocale str = if palindrom (head str) then vocale (head str) + nrVocale(tail str) else nrVocale (tail str)

-- nrVocale ["sos", "civic", "palton", "desen", "aerisirea"] = 9

-- 2. functie care primeste ca parametru un numar si o lista de întregi
-- si adauga elementul dat dupa fiecare element par din list

f :: Int -> [Int] -> [Int]
f n [] = []
f n (h:t) = if even h then h : n : f n t else h : f n t

-- LIST COMPREHENSION

-- 3. lista de divizori a unui numar

divizor :: Int -> [Int]
divizor 0 = [1]
divizor x = [y | y <- [1..x], x `mod` y == 0]

-- 4. lista listelor de divizori pentru o lista data

listadiv :: [Int] -> [[Int]]
listadiv list = [divizor x | x <- list]

-- 5. se dau limita inferioara si superioara a unui 
-- interval inchis si o lista. Sa se afiseze numerele
-- din lista care apartin intervalului

-- 5.a recursivitate

inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec x y [] = []
inIntervalRec x y (h:t)
    | x <= h && h <= y = h : t'
    | otherwise = t'
    where t' = inIntervalRec x y t

-- 5.b list comprehension

inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp x y list = [a | a <- list, x <= a, a <= y]

-- 6. numarul de elemente strict pozitive dintr-o lista

-- 6.a recursivitate

pozitiveRec :: [Int] -> Int
pozitiveRec [] = 0
pozitiveRec x = if head x > 0 then 1 + pozitiveRec (tail x)
                            else pozitiveRec (tail x)

-- 6.b list comprehension   

pozitiveComp :: [Int] -> Int
pozitiveComp x = length list where list = [y | y <- x, y > 0]

-- 7. lista pozitiilor elementelor impare dintr-o lista data

-- 7.b list comprehension

pozitiiImpareComp :: [Int] -> Int
pozitiiImpareComp x = sum [z | (y,z) <- zip x [0..], odd y]

-- 8. functie care calculeaza produsul tuturor cifrelor
-- care apar în sirul de caractere dat ca intrare

-- 8.a recursivitate

multDigitsRec :: String -> Int
multDigitsRec [] = 1
multDigitsRec (h:t) 
    | isDigit h = digitToInt h * x 
    | otherwise = x
    where x = multDigitsRec t

-- 8.b list 

multDigitsComp :: String -> Int
multDigitsComp s = product [digitToInt c | c <- s, isDigit c]
