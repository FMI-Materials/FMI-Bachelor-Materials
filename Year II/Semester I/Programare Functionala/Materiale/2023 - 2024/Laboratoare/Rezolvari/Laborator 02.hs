-- 1
poly :: Double -> Double -> Double -> Double -> Double
poly a b c x = a * x * x + b * x + c

-- 2
eeny :: Integer -> String
eeny x 
    | even x = "eeny"
    | otherwise = "meeny"

-- 3
fizzbuzz :: Integer -> String
fizzbuzz x
    | x `mod` 15 == 0 = "FizzBuzz"
    | x `mod` 5 == 0 = "Buzz"
    | x `mod` 3 == 0 = "Fizz"
    | otherwise = ""

fizzbuzz' :: Integer -> String
fizzbuzz' x =
    if x `mod` 15 == 0 then "FizzBuzz"
    else if x `mod` 5 == 0 then "Buzz"
    else if x `mod` 3 == 0 then "Fizz"
    else  ""

-- 4
tribonacci :: Integer -> Integer
tribonacci n
    | n < 3 = 1
    | n == 3 = 2
    | otherwise = tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3)

tribonacci' :: Integer -> Integer
tribonacci' 1 = 1
tribonacci' 2 = 1
tribonacci' 3 = 2
tribonacci' n = tribonacci'(n - 1) + tribonacci'(n - 2) + tribonacci'(n - 3)

-- 5
binomial :: Integer -> Integer -> Integer
binomial n k
    | k == 0 = 1
    | n == 0 = 0
    | otherwise = binomial (n - 1) (k - 1) + binomial (n - 1) k

-- 6
-- a)
verifL :: [Int] -> Bool
verifL l = even (length l)

-- b)
takefinal :: [a] -> Int -> [a]
takefinal l n 
    | length l < n = l
    | otherwise = drop (length l - n) l

-- c)
remove :: [Int] -> Int -> [Int]
remove l n
    | length l < n = l
    | otherwise = take (n - 1) l ++ drop n l 

-- 7
-- a)
myreplicate :: Int -> Int -> [Int]
myreplicate n v
    | n == 0 = []
    | otherwise = v : myreplicate (n - 1) v

-- b)
sumImp :: [Int] -> Int
sumImp [] = 0
sumImp (h:t)
    | odd h = h + sumImp t
    | otherwise = sumImp t

-- c)
totalLength :: [String] -> Int
totalLength [] = 0
totalLength (h:t)
    | head h == 'A' = length h + totalLength t
    | otherwise = totalLength t 