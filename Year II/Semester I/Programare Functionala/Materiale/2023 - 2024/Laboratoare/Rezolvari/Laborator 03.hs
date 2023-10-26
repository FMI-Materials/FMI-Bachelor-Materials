import Data.Char

--1
nrVocale' :: String -> Int
nrVocale' [] = 0
nrVocale' (h:t) 
    | elem h "aeiouAEIOU" = 1 + nrVocale' t
    | otherwise = nrVocale' t

nrVocale :: [String] -> Int
nrVocale [] = 0
nrVocale (h:t)
    | h == reverse h = nrVocale' h + nrVocale t
    | otherwise = nrVocale t

-- 2
f :: Int -> [Int] -> [Int]
f _ [] = []
f n (h:t)
    | even h = h : n : f n t
    | otherwise = h : f n t

-- 3
divizori :: Int -> [Int]
divizori n = [x | x <- [1..n], n `mod` x == 0]

-- 4
listadiv :: [Int] -> [[Int]]
listadiv [] = [[]]
listadiv (h:t) = 
    divizori h : listadiv t

-- 5
-- a
inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec _ _ [] = []
inIntervalRec a b (h:t)
    | a <= h && h <= b = h : inIntervalRec a b t
    | otherwise = inIntervalRec a b t

-- b
inIntervalComp :: Int -> Int -> [Int] -> [Int] 
inIntervalComp a b l = [x | x <- l, a <= x, x <= b]

-- 6
-- a
nrPozitiveRec :: [Int] -> Int
nrPozitiveRec [] = 0
nrPozitiveRec (h:t)
    | h > 0 = 1 + nrPozitiveRec t
    | otherwise = nrPozitiveRec t

-- b
nrPozitiveComp :: [Int] -> Int
nrPozitiveComp l = length [x | x <- l, x > 0]

-- 7
-- a
pozitiiImpareRec' :: [Int] -> Int -> [Int]
pozitiiImpareRec' [] _ = []
pozitiiImpareRec' (h:t) n 
    | odd h = n : pozitiiImpareRec' t (n + 1)
    | otherwise = pozitiiImpareRec' t (n + 1)

pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec l = pozitiiImpareRec' l 0

-- b
pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp l = [y | (x, y) <- zip l [0..length l - 1], odd x]

-- 8
-- a
multDigitsRec :: String -> Int
multDigitsRec "" = 1
multDigitsRec (h:t)
    | isDigit h = digitToInt h * multDigitsRec t
    | otherwise = multDigitsRec t

-- b)
multDigitsComp :: String -> Int
multDigitsComp s = product [digitToInt x | x <- s, isDigit x]

-- 9
myPermutations :: [Int] -> [[Int]]
myPermutations [] = [[]]
myPermutations (h:t) = [x | y <- myPermutations t, x <- insertEverywhere h y]
