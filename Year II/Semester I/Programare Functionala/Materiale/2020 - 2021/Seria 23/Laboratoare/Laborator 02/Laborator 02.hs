-- la nevoie decomentati liniile urmatoare:

import Data.Char
import Data.List

-- pentru teste
--import Test.QuickCheck

---------------------------------------------
-------RECURSIE: FIBONACCI-------------------
---------------------------------------------

fibonacciCazuri :: Integer -> Integer
fibonacciCazuri n
  | n < 2     = n
  | otherwise = fibonacciCazuri (n - 1) + fibonacciCazuri (n - 2)

fibonacciEcuational :: Integer -> Integer
fibonacciEcuational 0 = 0
fibonacciEcuational 1 = 1
fibonacciEcuational n =
    fibonacciEcuational (n - 1) + fibonacciEcuational (n - 2)

-- pentru testarea echivalenței celor 2 definiții de mai sus
-- testFibo :: Integer -> Property
-- testFibo n = n >= 0 && n < 25 ==> fibonacciCazuri n == fibonacciEcuational n

{-| @fibonacciLiniar@ calculeaza @F(n)@, al @n@-lea element din secvența
Fibonacci în timp liniar, folosind funcția auxiliară @fibonacciPereche@ care,
dat fiind @n >= 1@ calculează perechea @(F(n-1), F(n))@, evitănd astfel dubla
recursie. Completați definiția funcției fibonacciPereche.

Indicație:  folosiți matching pe perechea calculată de apelul recursiv.
-}
fibonacciLiniar :: Integer -> Integer
fibonacciLiniar 0 = 0
fibonacciLiniar n = snd (fibonacciPereche n)
  where
    fibonacciPereche :: Integer -> (Integer, Integer)
    fibonacciPereche 1 = (0, 1)
    fibonacciPereche n = undefined



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
inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec _ _ [] = []
inIntervalRec lo hi (x:t)
  | x >= lo && x<=hi = x:(inIntervalRec lo hi t)
  | otherwise = inIntervalRec lo hi t

inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp lo hi xs = [ x | x<-xs, x>=lo && x<=hi ]

-- L2.3

pozitiveRec :: [Int] -> Int
pozitiveRec [] = 0
pozitiveRec (h:t) = if h>0 then
       1 + (pozitiveRec t)
   else
       pozitiveRec t

pozitiveComp :: [Int] -> Int
pozitiveComp l = length [x | x<-l, x>0]

-- L2.4 
pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec' :: Int -> [Int] -> [Int]
pozitiiImpareRec' _ [] = []
pozitiiImpareRec' p (h:t) = let imp = (h `mod` 2) == 1 in
   if imp then (p:(pozitiiImpareRec' (p+1) t))
   else pozitiiImpareRec' (p+1) t
pozitiiImpareRec l = pozitiiImpareRec' 0 l


pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp l = let zl = zip l [0..((length l)-1)] in
   [snd x | x<-zl, (fst x) `mod` 2 == 1]


-- L2.5

multDigitsRec :: String -> Int
multDigitsRec [] = 1
multDigitsRec (h:t) = if isDigit h then
       (digitToInt h) * (multDigitsRec t)
   else
       multDigitsRec t

multDigitsComp :: String -> Int
multDigitsComp sir = foldl (\x y -> x*y) 1 [digitToInt x | x<-sir, isDigit x]

-- L2.6 

discountRec :: [Float] -> [Float]
discountRec [] = []
discountRec (h:t) = let nh = 0.75 * h in
   if nh < 200 then
       nh:(discountRec t)
   else
       discountRec t

discountComp :: [Float] -> [Float]
discountComp list = [0.75*x | x <-list, (0.75*x) < 200]

main = print "Hello"
