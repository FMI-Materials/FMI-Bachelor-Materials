import   Data.List

-- L3.1 Încercati sa gasiti valoarea expresiilor de mai jos si
-- verificati raspunsul gasit de voi în interpretor:
{-
[x^2 | x <- [1 .. 10], x `rem` 3 == 2]
[(x, y) | x <- [1 .. 5], y <- [x .. (x+2)]]
[(x, y) | x <- [1 .. 3], let k = x^2, y <- [1 .. k]]
[x | x <- "Facultatea de Matematica si Informatica", elem x ['A' .. 'Z']]
[[x .. y] | x <- [1 .. 5], y <- [1 .. 5], x < y ]

-}

factori :: Int -> [Int]
factori x = [f | f<-[1..x], x `mod` f == 0]

prim :: Int -> Bool
prim x = length (factori x) == 2

numerePrime :: Int -> [Int]
numerePrime x = [y | y<-[1..x], prim y]

-- L3.2 Testati si sesizati diferenta:
-- [(x,y) | x <- [1..5], y <- [1..3]]
-- zip [1..5] [1..3]

myzip3 :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myzip3 l1 l2 l3 = [(x,y,z) | x<-l1, y<-l2, z<-l3]


--------------------------------------------------------
----------FUNCTII DE NIVEL INALT -----------------------
--------------------------------------------------------
aplica2 :: (a -> a) -> a -> a
--aplica2 f x = f (f x)
--aplica2 f = f.f
--aplica2 f = \x -> f (f x)
aplica2  = \f x -> f (f x)

-- L3.3
{-
map (\ x -> 2 * x) [1 .. 10]
map (1 `elem` ) [[2, 3], [1, 2]]
map ( `elem` [2, 3] ) [1, 3, 4, 5]
-}

-- firstEl [ ('a', 3), ('b', 2), ('c', 1)]
firstEl l = map (\x -> fst x) l

-- sumList [[1, 3],[2, 4, 5], [], [1, 3, 5, 6]]
sumList l = map (\x -> sum x) l

-- prel2 [2,4,5,6]
prel2 l = map (\x -> if x `mod` 2 == 0 then x `div` 2 else x * 2) l

main = print "Hello"
