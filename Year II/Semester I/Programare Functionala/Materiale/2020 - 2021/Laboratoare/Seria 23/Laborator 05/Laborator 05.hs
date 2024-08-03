import Numeric.Natural


logistic :: Num a => a -> a -> Natural -> a
logistic rate start = f
  where
    f 0 = start
    f n = rate * f (n - 1) * (1 - f (n - 1))

logistic0 :: Fractional a => Natural -> a
logistic0 = logistic 3.741 0.00079

ex1 :: Natural
ex1 = 100


ex20 :: Fractional a => [a]
ex20 = [1, logistic0 ex1, 3]

ex21 :: Fractional a => a
ex21 = head ex20

ex22 :: Fractional a => a
ex22 = ex20 !! 2

ex23 :: Fractional a => [a]
ex23 = drop 2 ex20

ex24 :: Fractional a => [a]
ex24 = tail ex20


ex31 :: Natural -> Bool
ex31 x = x < 7 || logistic0 (ex1 + x) > 2

ex32 :: Natural -> Bool
ex32 x = logistic0 (ex1 + x) > 2 || x < 7
ex33 :: Bool
ex33 = ex31 5

ex34 :: Bool
ex34 = ex31 7

ex35 :: Bool
ex35 = ex32 5

ex36 :: Bool
ex36 = ex32 7


semn :: [Integer] -> String
semn = f
   where
     f [] = ""
     f (h:t) = if h >= -9 && h<0 then
                   '-':(f t)
               else if h == 0 then
                   '0':(f t)
               else if h>0 && h<=9 then
                   '+':(f t)
               else
                   (f t)

semnFold :: [Integer] -> String
semnFold = foldr op unit
   where
     unit = ""
     op = (\a b -> if a==0 then '0':b else if a>=(-9) && a<0 then '-':b else if a>0 && a<=9 then '+':b else b)
     
     
     
matrice :: Num a => [[a]]
matrice = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]     


corect :: [[a]] -> Bool 
corect = f
   where
     f [] = True
     f [a,b] = (length a) == (length b) 
     f (a:b:t) = if (length a) == (length b) then f (b:t) else False

el :: [[a]] -> Int -> Int -> a

el' [a] _ = a
el' (h:t) p = if p==0 then h else el' t (p-1)

el'' :: [a] -> Int -> a
el'' [a] _ = a
el'' (h:t) p = if p==0 then h else el'' t (p-1)

--el l p1 p2 = el'' (el' l p1) p2
el matrix i j = (matrix !! i) !! j

transforma :: [[a]] -> [(a, Int, Int)]
transforma  = undefined

main = undefined
