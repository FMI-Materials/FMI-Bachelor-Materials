-- LISTE

-- 1. returneaza lista divizorilor pozitivi

factori :: Int -> [Int]
factori x = [y | y <- [1..x], x `rem` y == 0]

-- 2. verifica daca e numar prim

prim :: Int -> Bool
prim x = length (factori x) == 2

-- 3. lista de numere prime din intervalul 2..n

numerePrime :: Int -> [Int]
numerePrime x = [y | y <- [2..x], prim y]

-- FUNCTIA ZIP

-- 4. definirea unui functii zip pentru 3 argumente

myzip3 :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myzip3 x y z = [(a, b, c) | ((a, b), c) <- zip (zip x y) z]

zip3FaraZip :: [a] -> [b] -> [c] -> [(a, b, c)]
zip3FaraZip [] _ _ = []
zip3FaraZip _ [] _ = []
zip3FaraZip _ _ [] = []
zip3FaraZip (a : as) (b : bs) (c : cs) = (a, b, c) : zip3FaraZip as bs cs

-- ORDONARE FOLOSIND SELECTIE

-- 6. verifica daca o lista de numere este ordonata (recursiv)

ordonataNat :: [Int] -> Bool
ordonataNat [] = True
ordonataNat [x] = True
ordonataNat (x:xs) = x < head xs && ordonataNat xs

-- 7. verifica daca o lista de valori este ordonata
-- in functie de o relatie binara daca ca parametru

ordonata :: [a] -> (a -> a -> Bool) -> Bool
ordonata [] op = True
ordonata [x] op = True
ordonata (x:y:z) op = op x y && ordonata (y:z) op

-- 9. primeste o functie si o lista de functii si
-- returneaza functiile obtinute prin compunerea
-- primei functii cu fiecare functie din lista

compuneList :: (b -> c) -> [a -> b] -> [a -> c]
compuneList f lf = [f.g | g <- lf]

-- 10. primeste un argument a si o lista de functii
-- si returneaza rezultatele aplicarii functiilor
-- din lista pe primul argument

aplicaList :: a -> [a -> b] -> [b]
aplicaList x lf = [f x | f <- lf]