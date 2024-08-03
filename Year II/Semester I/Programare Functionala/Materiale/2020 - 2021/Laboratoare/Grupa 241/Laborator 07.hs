import Test.QuickCheck
import Data.List
import Data.Char

double :: Int -> Int
double x = 2*x
triple :: Int -> Int
triple x = 3*x
penta :: Int -> Int
penta x = 5*x

--proprietate adevarata
test :: Int-> Bool
test x = (double x + triple x) == (penta x)
-- *Main> quickCheck test
-- +++ OK, passed 100 tests.
--proprietata falsa
testFals :: Int-> Bool
testFals x = double x  == (penta x)
-- *Main> quickCheck testFals
-- *** Failed! Falsified (after 2 tests):
-- 1

--Tipul Maybe
--data Maybe a = Nothing | Just a
--data Maybe String= Nothing | Just String
myLookUp :: Int -> [(Int,String)]-> Maybe String
myLookUp _ [] = Nothing
myLookUp key ((key2, value):xs)
     | key == key2 = Just value
     | otherwise = myLookUp key xs

testLookUp :: Int -> [(Int,String)] -> Bool
testLookUp key env = myLookUp key env == lookup key env
-- *Main> quickCheck testLookUp 
-- +++ OK, passed 100 tests.

--TESTARE CU CONSTRANGERI
--Property ne  ajuta sa extindem limbajul logic cu combinatori precum: ==>
--daca premisa este falsa testul este "discarded"
testLookUpCond :: Int -> [(Int,String)] -> Property
testLookUpCond n list = n > 0 && n `div` 5 == 0 ==> testLookUp n list
-- *Main> quickCheck testLookUpCond
-- *** Gave up! Passed only 67 tests; 1000 discarded tests.

--ex 8
--a)
myLookUp' :: Int -> [(Int,String)]-> Maybe String
myLookUp' _ [] = Nothing
myLookUp' key ((key2, head: tail):xs)
     | key == key2 = Just (toUpper head : map toLower tail)
     | otherwise = myLookUp' key xs

--b)
--Property trebuie sa dea un Bool
test' :: Int -> [(Int,String)] -> Property
test' n list =  (length list == length [ (key, head:tail) | (key, head: tail)<-list, head == toUpper head ]) ==> testLookUp n list
-- *Main> quickCheck test'
-- +++ OK, passed 100 tests; 690 discarded.

------------Testare pt tipuri de date algebrice------------
-----------------------------------------------------------

data ElemIS = I Int | S String
     deriving (Show,Eq)
--Tipurile de date care pot fi testate cu QuickCheck trebuie sa fie
--instante ale clasei Arbitrary


env=[(1,S "ana"), (2, I 3), (3, S "mere")]

myLookUpElem :: Int -> [(Int,ElemIS)]-> Maybe ElemIS
myLookUpElem _ [] = Nothing
myLookUpElem n (x:xs)
     | n==(fst x) = Just (snd x)
     | otherwise = myLookUpElem n xs

--nu vrea cu quickCheck
testLookUpElem :: Int -> [(Int,ElemIS)] -> Bool
testLookUpElem key env = myLookUpElem key env == lookup key env

--------------------------------
--data Person = P {​​nume :: String}​​
--Echivalent 
--data Person = P String
--nume  :: Person -> String
data Person = P (String -> String)

transforma :: String-> String
transforma s = tail s
--data Person = P {​​fnume :: String -> String }​​


