import Numeric.Natural
---------------Partea 1----------------
---------------------------------------
--ex1
--a)
produsRec :: [Integer] -> Integer
produsRec [] = 1
produsRec (h:t) = h * produsRec t
--b)
produsFold :: [Integer] -> Integer
produsFold list = foldr (*) 1 list
--merge si cu omiterea argumentului il ia automat
--foldr incepe de la coada listei invers catre cap

--prop_produs x= produsRec x == produsFold x
--apel quickCheck prop_produs
--da 100 liste random si verifica daca are acelasi rezultate

--ex2
--a)
andRec :: [Bool] -> Bool
andRec [] = True
andRec (h:t) = h && andRec t
--b)
andFold :: [Bool] -> Bool
andFold = foldr (&&) True

--prop_and x = andFold x ==and Rec x

--ex3
--a)
concatRec :: [[a]] -> [a]
concatRec []=[]
concatRec (h:t)= h ++ concatRec t
--b)
concatFold :: [[a]] -> [a]
concatFold = foldr (++) []

--ex4
--a)
rmChar :: Char -> String -> String
rmChar c str= [x | x<- str, x/= c]

--rmChar chr str =filter (/= chr) str
--b)
rmCharsRec :: String -> String -> String
rmCharsRec [] []= []
rmCharsRec (c: cs) (x:xs) = (if x==c then [] else [x]) ++ (rmCharsRec cs xs)
--test_rmchars :: Bool
--test_rmchars = rmCharsRec ['a'..'l'] "fotbal" == "ot"

--c)
rmCharsFold :: String -> String -> String
rmCharsFold s1 s2= foldr(aux s1) "" s2
                              where aux s1 c1 c2
                                                |c1 `elem` s1=c2
                                                |otherwise =c1 :c2
 
-----------------Partea a 2 a----------------
---------------------------------------------
--1
ordonataNat :: [Int] -> Bool
ordonataNat []=True
ordonataNat [x]=True --cazul cand are un singur element
ordonataNat (x: xs)= x <= head xs && ordonataNat xs
--2
ordonataNat1 :: [Int] -> Bool
ordonataNat1 l=and [x <= y| (x,y)<- zip l (tail l) ] 

--3
--a)
ordonata :: [a] -> ( a -> a -> Bool) -> Bool
ordonata l rel =and [rel x y| (x,y)<- zip l (tail l) ] 
--b) apel: ordonata [1,2,3] (<)

--c)
(*<*) :: (Integer, Integer) -> (Integer, Integer) -> Bool
(*<*) (x1, y1) (x2, y2) =and [x1<x2, y1<y2]

--ex4
compuneList :: (b->c) -> [(a->b)] -> [(a->c)]
compuneList f lf = [ f.x  | x<- lf]

aplicaList :: a -> [(a->b)] ->[b]
aplicaList x l= [f x| f<-l]

--myzip3
myzip3 :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myzip3 (h1:t1) (h2:t2) (h3:t3)= (h1, h2, h3) : (myzip3 t1 t2 t3)
myzip3 _ _ _=[]

myzip33 :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myzip33 l1 l2 l3 = map(\((a,b),c)-> (a,b,c)) (zip (zip l1 l2) l3)

