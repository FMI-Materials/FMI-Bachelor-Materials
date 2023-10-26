-- 1
{-
[x^2 | x <- [1..10], x `rem` 3 == 2]
[(x, y) | x <- [1..5], y <- [x..(x+2)]]
[(x, y) | x <- [1..3], let k = x^2, y <- [1..k]]
[x | x <- "Facultatea de Matematica si Informatica", elem x ['A'..'Z']]
[[x..y] | x <- [1..5], y <- [1..5], x < y]
-}

-- 2
factori :: Int -> [Int]
factori n = [x | x <- [1..n], n `rem` x == 0]

-- 3
prim :: Int -> Bool
prim n
    | factori n == [1, n] = True
    | otherwise = False

-- 4
numerePrime :: Int -> [Int]
numerePrime n = [x | x <- [2..n], prim x == True]

-- 5
myzip3 :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myzip3 (x:xs) (y:ys) (z:zs) = (x, y, z) : myzip3 xs ys zs
myzip3 _ _ _ = []

-- 6
firstEl :: [(a, b)] -> [a]
firstEl l = map (\(x, _) -> x) l

-- 7
sumList :: [[Int]] -> [Int]
sumList l = map (sum) l

-- 8
prel2 :: [Int] -> [Int]
prel2 l = map (\x -> if even x then x `div` 2 else x * 2) l

-- 9
contineCh :: Char -> [String] -> [String]
contineCh ch l = filter (ch `elem`) l

-- 10
patrateImpare :: [Int] -> [Int]
patrateImpare l = map (\x -> x^2) $ filter (odd) l

-- 11
patratePozImpare :: [Int] -> [Int]
patratePozImpare l = map (\x -> x^2) [(fst x) | x <- zip l [1..], odd (snd x)]

-- 12
numaiVocale :: [String] -> [String]
numaiVocale l = map (\x -> filter (\y -> y `elem` "aeiouAEIOU") x) l

-- 13
mymap :: (a -> b) -> [a] -> [b]
mymap f [] = []
mymap f (x:xs) = f x : mymap f xs

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter f [] = []
myfilter f (x:xs)
    | f x = x : myfilter f xs
    | otherwise = myfilter f xs
