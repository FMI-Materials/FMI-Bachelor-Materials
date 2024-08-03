import Numeric.Natural

logistic :: Num a => a -> a -> Natural -> a
logistic rate start = f
  where
    f 0 = start
    f n = rate * f (n - 1) * (1 - f (n - 1))

logistic0 :: Fractional a => Natural -> a
logistic0 = logistic 3.741 0.00079

ex1 :: Natural
ex1 = 1000

--ex2
ex20 :: Fractional a => [a]
ex20 = [1, logistic0 ex1, 3] --NU

ex21 :: Fractional a => a
ex21 = head ex20 --NU

ex22 :: Fractional a => a
ex22 = ex20 !! 2 --NU pt ca se incepe de la 2

ex23 :: Fractional a => [a]
ex23 = drop 2 ex20 --sterge primele 2 componente --NU

ex24 :: Fractional a => [a]
ex24 = tail ex20 --DA

--ex3
ex31 :: Natural -> Bool
ex31 x = x < 7 || logistic0 (ex1 + x) > 2

ex32 :: Natural -> Bool
ex32 x = logistic0 (ex1 + x) > 2 || x < 7

ex33 :: Bool
ex33 = ex31 5 --NU

ex34 :: Bool
ex34 = ex31 7 --DA

ex35 :: Bool
ex35 = ex32 5 --DA

ex36 :: Bool
ex36 = ex32 7 --DA

--Universalitate functiei foldr
sumaPatrateImpare :: [Integer] -> Integer
sumaPatrateImpare [] = 0
sumaPatrateImpare (a:as)
  | odd a = a * a + sumaPatrateImpare as
  | otherwise = sumaPatrateImpare as

sumaPatrateImpareFold :: [Integer] -> Integer
sumaPatrateImpareFold = foldr op unit
  where
    unit = 0
    a `op` suma
        | odd a = a * a + suma
        | otherwise = suma

--ex1
--a)
semn :: [Integer] -> String
semn [] = ""
semn (x:xs)
  | x >= -9 && x < 0 = "-" ++ semn xs
  | x >0 && x <= 9 = "+" ++ semn xs
  | x==0 = "0" ++ semn xs
  | otherwise = semn xs

--b)
semnFold :: [Integer] -> String
semnFold = foldr op unit
   where
     unit = ""
     op a b
      | a >= -9 && a < 0 = "-" ++ b
      | a > 0  && a <= 9 = "+" ++ b
      | a == 0           = "0" ++ b
      | otherwise        = b
     
---------Matrici---------     
matrice :: Num a => [[a]]
matrice = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]     

--ex1
corect :: [[a]] -> Bool 
corect [] = True
corect (x:xs) = and [length a == length b | (a, b) <- zip (x:xs) xs]

--ex2
el :: [[a]] -> Int -> Int -> a 
el matrice row col = matrice !! row !! col

--ex3
transforma :: [[a]] -> [(a, Int, Int)]
transforma matrice=undefined
  
 