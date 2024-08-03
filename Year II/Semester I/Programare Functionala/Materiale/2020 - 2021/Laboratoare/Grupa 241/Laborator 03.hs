import   Data.List
--import   Test.QuickCheck
--cabal install --lib --package-env . QuickCheck

-- L3.1 Încercati sa gasiti valoarea expresiilor de mai jos si
-- verificati raspunsul gasit de voi în interpretor:
--[x^2 | x <- [1 .. 10], x `rem` 3 == 2]
--[(x, y) | x <- [1 .. 5], y <- [x .. (x+2)]]
--[(x, y) | x <- [1 .. 3], let k = x^2, y <- [1 .. k]]
--[x | x <- "Facultatea de Matematica si Informatica", elem x ['A' .. 'Z']]
--[[x .. y] | x <- [1 .. 5], y <- [1 .. 5], x < y ]



factori :: Int -> [Int]
factori x = [d | d<-[2..x `div`2], x `rem` d==0]

prim :: Int -> Bool
prim x = if (x==1 || x==0 || length(factori x)>0) then False else True

numerePrime :: Int -> [Int]
numerePrime x = [y | y<-[2..x], prim y == True]

-- L3.2 Testati si sesizati diferenta:
-- [(x,y) | x <- [1..5], y <- [1..3]] produs cartezian
-- zip [1..5] [1..3] primelor 3 nr din [1..5] le pune nr din [1..3]

--------------------------------------------------------
----------FUNCTII DE NIVEL INALT -----------------------
--------------------------------------------------------
aplica2 :: (a -> a) -> a -> a
--toate variantele sunt echivalente 
--aplica2 f x = f (f x)
--aplica2 f = f.f
--aplica2 f = \x -> f (f x)
aplica2  = \f x -> f (f x)

adunare x=x+10
--apelez : aplica2 adunare 9
--apelez : aplica2 (+10) 9

-- L3.3
{-

map (\ x -> 2 * x) [1 .. 10]
map (1 `elem` ) [[2, 3], [1, 2]]
map ( `elem` [2, 3] ) [1, 3, 4, 5]

-}
firstEl :: [(a,b)] ->[a]
firstEl l = [ fst(a,b) | (a,b)<- l]
-- firstEl [ ('a', 3), ('b', 2), ('c', 1)]
--folosinf fucntia map
firstel :: [(a,b)] ->[a]
firstel l = map(\x-> fst x) l

sumList :: [[Integer]] -> [Integer] 
sumList l= [sum ls| ls<-l]
-- sumList [[1, 3],[2, 4, 5], [], [1, 3, 5, 6]]

prel2 :: [Integer] -> [Integer]
prel2 l
  |null l  = l
  |even h   = (h `div` 2):t'
  |odd h    = (2*h) :t'
  |otherwise=t'
  where
     h= head l
     t=tail l
     t'=prel2 t
            
-- prel2 [2,4,5,6]

--L3.4
ex1:: Char-> [String] -> [String]
ex1 c s = filter (c `elem`) s 

ex2 :: [Integer] -> [Integer]
ex2 l= map(\x->x*x) (filter (\x->odd x) l )

ex3 :: [Integer] ->[Integer] 
ex3 l= map(\(a,b)->a*a) (filter (\(a,b)->odd b) (zip l [0..]))

--de revenit la 4
ex4 :: [String] -> [String]
ex4 l= map(\s->filter( \c->  elem c "aeiouAEIOU") s) l

--L3.5
mymap :: (a -> b) -> [a] -> [b]
mymap _ [] = []
mymap f (x:xs) = f x : mymap f xs

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter _ [] = []
myfilter f (x:xs)
  | f x       = x : (myfilter f xs)
  | otherwise = myfilter f xs

-----------------------------------------------
-----Material suplimentar----------------------
------------------------------------------------
 
--Ciurul lui Eratostene

numerePrimeCiur :: Int -> [Int]
numerePrimeCiur x   = auxCiur [2..x]
                    where
                    auxCiur [] =[]
                    auxCiur (h:xs)= h: auxCiur [x | x<-xs, x `mod` h>0] 

