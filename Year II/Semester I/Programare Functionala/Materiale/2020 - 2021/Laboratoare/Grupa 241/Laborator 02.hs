-- la nevoie decomentati liniile urmatoare:
import Data.Char
import Data.List
---------------------------------------------
-------RECURSIE: FIBONACCI-------------------
---------------------------------------------
{-fibonaci pe cazuri-}
fibonacciCazuri :: Integer -> Integer
fibonacciCazuri n
  | n < 2     = n
  | otherwise = fibonacciCazuri (n - 1) + fibonacciCazuri (n - 2)

{-fibonaci ecuational-}
fibonacciEcuational :: Integer -> Integer
fibonacciEcuational 0 = 0
fibonacciEcuational 1 = 1
fibonacciEcuational n =
    fibonacciEcuational (n - 1) + fibonacciEcuational (n - 2)

{-fibonaci liniar cel mai optim-}
fibonacciLiniar :: Integer -> Integer
fibonacciLiniar 0 = 0
fibonacciLiniar n = snd (fibonacciPereche n)
  where
    fibonacciPereche :: Integer -> (Integer, Integer)
    fibonacciPereche 1 = (0, 1)
    fibonacciPereche n = let (precedent, curent) = fibonacciPereche(n-1) in (curent, precedent + curent)
  

---------------------------------------------
----------RECURSIE PE LISTE -----------------
---------------------------------------------
semiPareRecDestr :: [Int] -> [Int]
semiPareRecDestr l
  | null l    = l
  | even h    = h `div` 2 : t'
  | otherwise = t'
  where
    h = head l
    t = tail l
    t' = semiPareRecDestr t

{-implementare folosind sabloane-}
semiPareRecEq :: [Int] -> [Int]
semiPareRecEq [] = []
semiPareRecEq (h:t)
  | even h    = h `div` 2 : t'
  | otherwise = t'
  where t' = semiPareRecEq t

---------------------------------------------
----------DESCRIERI DE LISTE ----------------
---------------------------------------------
semiPareComp :: [Int] -> [Int]
semiPareComp l = [ x `div` 2 | x <- l, even x ]


-- L2.2
{-comprehesiune-}
inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp lo hi xs = [x | x<-xs, x>=lo, x<=hi]

{-recursiv-}
inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec lo hi xs
  |null xs = xs
  |h>lo && h<hi= h:t'
  |otherwise =t'
  where
     h= head xs
     t=tail xs
     t'=inIntervalRec lo hi t

-- L2.3

pozitiveRec :: [Int] -> Int
pozitiveRec l 
 | null l = 0
 | h > 0 = 1 + n'
 | otherwise =n'
 where
     h = head l
     t = tail l
     n' = pozitiveRec t

pozitiveComp :: [Int] -> Int
pozitiveComp l = length [x | x<-l, x>0] 
{-import Data.List-}

-- L2.4 
pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec l = pozitiiAux 0 l
  where 
    pozitiiAux :: Int -> [Int] -> [Int]
    pozitiiAux _ [] = []
    pozitiiAux n (x:t) = let t'= pozitiiAux (n+1) t in ( if (odd x) then n:t' else t' )


pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp l = [y | (x,y)<-zip l [0..], odd x]


-- L2.5
multDigitsRec :: String -> Int
multDigitsRec sir 
 | null sir = 1
 | isDigit h == True = digitToInt h* n'
 | otherwise = n'
 where
     h = head sir
     t = tail sir
     n' = multDigitsRec t

multDigitsComp :: String -> Int
multDigitsComp sir = product [digitToInt x | x<-sir, isDigit x == True]

-- L2.6 

discountRec :: [Float] -> [Float]
discountRec list 
 | null list = list
 | 0.75*h<200= 0.75*h :n'
 | otherwise = n'
 where
     h = head list
     t = tail list
     n' = discountRec t

discountComp :: [Float] -> [Float]
discountComp list = [0.75*x | x<-list, 0.75*x<200]