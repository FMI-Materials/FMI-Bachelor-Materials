import Data.Char
import Data.List
--Dima Oana Teodora 241
--ex1 a)
f :: Char -> Bool
f chr= if isLetter chr == False then error "Nu este litera"
            else toUpper chr <= 'M'

--b) List comprehension
g :: String -> Bool
g str = length [x | x <- str, isLetter x, f x] > length [x | x <- str, isLetter x, f x ==False]

--c)Recursiv
h :: String -> Bool
h str = (>0) $ count 0 str
    where
        count cnt [] = cnt
        count cnt (x:xs)
            | isLetter x && f x = count (cnt+1) xs
            | isLetter x && not (f x) = count (cnt-1) xs
            | otherwise = count cnt xs
      
    
--prop_verif x= g x == h x
--apel quickCheck prop_verif

--ex2 a)
--functie auxiliara care face perechi


c :: [Int] -> [Int]
c []=[]
c (x:xs)= [x | (x,y)<- zip(x:xs)xs, x==y] 

--b)

d:: [Int]-> [Int]
d [] =[]
d l 
  | length l ==1 = []
  |h ==head t = h: t'
  |otherwise= t' 
  where
    h=head l
    t=tail l
    t'=d t

--c)
--prop_cd x= c x == d x
--apel quickCheck prop_cd