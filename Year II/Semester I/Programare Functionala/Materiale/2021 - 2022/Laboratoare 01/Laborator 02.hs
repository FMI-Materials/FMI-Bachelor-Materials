

--1. Sa se scrie o functie poly2 care are patru argumente de tip Double, a,b,c,x si calculeaza a*xˆ2+b*x+c.
--Scrieti s, i signatura funct, iei (poly :: ceva).
poly2 :: Double -> Double -> Double -> Double -> Double 
poly2 a b c x =  a * x *x + b * x + c


--2.Să se scrie o funct, ie eeny care întoarce “eeny” pentru input par s, i “meeny” pentru input impar. Hint:
--puteti folosi functia even (puteti căuta pe https://hoogle.haskell.org/).

eeny :: Integer -> String
eeny x =
    if even x
        then "eeny"
        else "meeny"

--3.Să se scrie o funct, ie fizzbuzz care întoarce “Fizz” pentru numerele divizibile cu 3, “Buzz” pentru
--numerele divizibile cu 5 s, i “FizzBuzz” pentru numerele divizibile cu ambele. Pentru orice alt număr se
--întoarce s, irul vid. Pentru a calcula modulo a două numere putet, i folosi funct, ia mod. Să se scrie această
--funct, ie în 2 moduri: folosind if s, i folosind gărzi (condit, ii).
fizzbuzz :: Integer -> String
fizzbuzz x = 
   if mod x 3 == 0 && mod x 5 == 0 
       then "FizzBuzz"
       else if mod x 3 == 0
           then "Fizz"
           else if mod x 5 == 0
               then "Buzz"
               else ""


fizzbuzz1 :: Integer -> String
fizzbuzz1 x
    | mod x 3 == 0 && mod x 5 == 0 = "FizzBuzz"
    | mod x 3 == 0 = "Fizz"
    | mod x 5 == 0 = "Buzz"
    | otherwise = ""


-- Fibonacci
fibonacciCazuri :: Integer -> Integer
fibonacciCazuri n
    | n < 2 = n
    | otherwise = fibonacciCazuri(n-1) + fibonacciCazuri(n-2)

fibonacciEcuational :: Integer -> Integer
fibonacciEcuational 0 = 0
fibonacciEcuational 1 = 1
fibonacciEcuational n = fibonacciEcuational(n-1) + fibonacciEcuational(n-2)

--4.Tribonacci
tribonacci :: Integer -> Integer
tribonacci 1 = 1
tribonacci 2 = 1
tribonacci 3 = 2
tribonacci n = tribonacci(n-1) + tribonacci(n-2) + tribonacci(n-3)

--5.binomial
binomial :: Integer -> Integer -> Integer
binomial n 0 = 1
binomial 0 k = 0
binomial n k = binomial (n-1) k + binomial (n-1) (k-1)

--6.
--a)verifL - verifică dacă lungimea unei liste date ca parametru este pară
verifL :: [Int] -> Bool
verifL x = even (length x)

--b)takefinal - pentru o listă dată ca parametru s, i un număr n, întoarce lista cu ultimele n elemente.
--Dacă lista are mai putin de n elemente, se intoarce lista nemodificată.
takefinal :: [Int] -> Int -> [Int]
takefinal x n =
    if length x < n
        then x
        else drop (length x + (-n)) x

--c)remove - pentru o listă s, i un număr n se întoarce lista din care se s, terge elementul de pe pozit, ia n.
--(Hint: putet, i folosi funct, iile take s, i drop). Scrit, i si prototipul functiei.
remove :: [Int] -> Int -> [Int]
remove x n =
    if length x < n
        then x
        else concat[take (n-1) x, takefinal x (length x + (-n))]

--7.
--a)myreplicate - pentru un întreg n si o valoare v întoarce lista de lungime n ce are doar elemente egale
--cu v. Să se scrie s, i prototipul functiei.
myreplicate :: Int -> Int -> [Int]
myreplicate 0 v = []
myreplicate n v = v:myreplicate (n-1) v

--b)sumImp - pentru o listă de numere întregi, calculează suma valorilor impare. Să se scrie s, i prototipul
--functiei.
sumImp :: [Int] -> Int
sumImp [] = 0
sumImp (x:xs) = 
    if even x
        then sumImp xs
        else x + sumImp xs

--c)totalLen - pentru o listă de s, iruri de caractere, calculează suma lungimilor s, irurilor care încep cu
--caracterul ‘A’. 
totalLen :: [String] -> Int
totalLen [] = 0
totalLen (x:xs) =
    if head x == 'A'
        then length x + totalLen xs
        else totalLen xs

f x = let x = 3; y = 4 in x + y
