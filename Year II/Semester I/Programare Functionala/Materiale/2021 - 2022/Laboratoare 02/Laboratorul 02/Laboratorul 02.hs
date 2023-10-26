-- FUNCTII

-- 1. functie care are patru argumente de tip double 
-- a, b, c, x si calculeaza a*xˆ2 + b*x + c

poly2 :: Double -> Double -> Double -> Double -> Double
poly2 a b c x = a*x*x + b*c + c


-- 2. functie care întoarce “eeny” pentru input
-- par si “meeny” pentru input impar

eeny :: Integer -> String
eeny x = if even x
            then "par"
            else "impar"

-- 3. functie care întoarce “Fizz” pentru numerele divizibile cu 3,
-- “Buzz” pentrunumerele divizibile cu 5 si
-- “FizzBuzz” pentru numerele divizibile cu ambele

fizzbuzz :: Integer -> String
fizzbuzz a
    | mod a 15 == 0 = "FizzBuzz"
    | mod a 3 ==0 = "Fizz"
    | mod a 5 ==0 = "Buzz"
    | otherwise = ""

-- RECURSIVITATE

fibonacci :: Integer -> Integer
fibonacci n
    | n < 0 = error "incorrect value"
    | n == 0 || n == 1 = n
    | otherwise = fibonacci(n - 1) + fibonacci (n - 2)

fibonacciEcuational :: Integer -> Integer 
fibonacciEcuational 0 = 0
fibonacciEcuational 1 = 1
fibonacciEcuational n = fibonacciEcuational(n - 1) + fibonacciEcuational(n - 2)

-- 4. fibonacci pentru 3 numere

tribonacci :: Integer -> Integer
tribonacci n
    | n < 1 = error "incorrect value"
    | n == 1 = 1
    | n == 2 = 1
    | n == 3 = 2
    | otherwise = tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3)

tribonacciEcuational :: Integer -> Integer 
tribonacciEcuational 1 = 1
tribonacciEcuational 2 = 1
tribonacciEcuational 3 = 2
tribonacciEcuational n = tribonacciEcuational(n - 1) + tribonacciEcuational(n - 2) + tribonacciEcuational(n - 3)

-- 5. sa se scrie o functie care calculează coeficientii binomiali

binomial :: Integer -> Integer -> Integer
binomial n 0 = 1
binomial 0 k = 0
binomial n k = binomial (n-1) k + binomial (n-1) (k-1)

-- LISTE

-- 6.a verifică dacă lungimea unei liste date ca parametru este pară

verifL :: [Int] -> Bool
verifL l = even (length l)

-- 6.b pentru o listă dată ca parametru si un număr n
-- întoarce lista cu ultimele n elemente

takefinal :: [Int] -> Int -> [Int]
takefinal list n
    | length list > n = takefinal (tail list) n
    | length list <= n = list

-- si pentru siruri de caractere
takefinalgen :: [a] -> Int -> [a]
takefinalgen list n
    | length list > n = takefinalgen (tail list) n
    | length list <= n = list

-- 6.c sterge elemetul de pe pozitia n dintr-o lista

remove :: [a] -> Int -> [a]
remove list n = take (n-1) list ++ drop n list

-- RECURSIVITATE PE LISTE

-- 7.a creeaza o lista prin repetarea valorii v de n ori

myreplicate :: Int -> a -> [a]
myreplicate 0 v = []
myreplicate n v = v : myreplicate (n-1) v

-- 7.b calculează suma valorilor impare dintr-o lista

sumImp :: [Int] -> Int
sumImp [] = 0
sumImp (h:t) = if odd h then h + sumImp t
                else 0 + sumImp t

-- 7.c pentru o listă de siruri de caractere calculează suma
-- lungimilor sirurilor care încep cu caracterul 'A'

totalLen :: [String] -> Int
totalLen [] = 0
totalLen (h:t)
    | head h == 'A' = length h + totalLen t
    | otherwise = 0 + totalLen t