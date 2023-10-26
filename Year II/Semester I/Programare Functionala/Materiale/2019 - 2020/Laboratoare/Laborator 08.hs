import Test.QuickCheck
    ( (==>), quickCheck, Arbitrary(arbitrary), Property ) 

import Data.List
import Data.Char (toUpper, isUpper)
import Data.Maybe

double :: Int -> Int
double x = 2 * x
triple :: Int -> Int
triple x = 3 * x
penta :: Int -> Int
penta x = 5 * x

test :: Int -> Bool
test x = (double x + triple x) == penta x

-- un test care verifica o proprietate falsa
anotherTest :: Int -> Bool
anotherTest x = double(triple x) == penta x

-- functia myLookUp cauta un element intreg intr-o lista de perechi cheie-valoare 
-- si intoarce valoarea gasita folosind un raspuns de tip Maybe String
myLookUp :: Int -> [(Int,String)] -> Maybe String
myLookUp _ [] = Nothing
myLookUp x ((key,val):xs) = if x == key then Just val else myLookUp x xs

testLookUp :: Int -> [(Int,String)] -> Bool
testLookUp cheie lista = myLookUp cheie lista == lookup cheie lista

-- testam ca myLookUp este echivalenta cu lookUp predefinita doar pentru chei pozitive si divizibile cu 5
testLookUpCond :: Int -> [(Int,String)] -> Property
testLookUpCond n list = n > 0 && n `div` 5 == 0 ==> testLookUp n list

runTest :: IO ()
runTest = quickCheck testLookUpCond

myLookUp' :: Int -> [(Int,String)] -> Maybe String
myLookUp' _ [] = Nothing
myLookUp' x ((key,s0:s):xs) = if x == key then Just (toUpper s0:s) else myLookUp' x xs

-- un predicat care testeaza ca myLookUp' este echivalenta cu lookUp pentru listele care contin doar valori care incep cu majuscula
testLookUpCond' :: Int -> [(Int,String)] -> Property
testLookUpCond' n list = all (\(_,y) -> primaLiteraMajuscula y) list ==> testLookUp n list
    where 
        primaLiteraMajuscula sir = sir /= "" && isUpper (head sir)


quicksort :: Ord a => [a] -> [a]
quicksort []     = []
quicksort (x:xs) = smalls ++ [x] ++ bigs
                 where smalls = quicksort [n | n <- xs, n <= x]
                       bigs   = quicksort [n | n <- xs, n > x]


-- Testam ca quicksort(quicksort(l)) = quicksort(l)
testQuickSort1 :: [Int] -> Bool
testQuickSort1 list = quicksort ( quicksort list ) == quicksort list

-- Testam ca prin aplicarea sortarii pe o lista si pe lista inversata se obtin doua liste identice
reverseList :: [a] -> [a]
reverseList [] = []
reverseList (x:xs) = reverseList xs ++ [x]

testQuickSortInv :: [Int] -> Bool
testQuickSortInv list = quicksort list == quicksort ( reverseList list )

-- Testam ca prin sortarea listei [1..n] nu se modifica lista
testQuickSortIdent :: Int -> Bool
testQuickSortIdent n = quicksort [1..n] == [1..n]

-- Testam ca prin sortare nu se modifica lungimea listei
testQuickSortLength :: Ord a => [a] -> Bool
testQuickSortLength list = length list == length ( quicksort list )


quicksortBuggy :: Ord a => [a] -> [a]
quicksortBuggy []     = []
quicksortBuggy (x:xs) = smalls ++ [x] ++ bigs
                where smalls = quicksortBuggy [n | n <- xs, n < x] -- oops
                      bigs   = quicksortBuggy [n | n <- xs, n > x]

-- Definirea predicatelor pentru testarea quicksortBuggy
testQuicksortBuggy1 :: [Int] -> Bool
testQuicksortBuggy1 l = quicksortBuggy (quicksortBuggy l) == quicksortBuggy l

testQuicksortBuggy2 :: [Int] -> Bool
testQuicksortBuggy2 l = quicksortBuggy l == quicksortBuggy (reverseList l)

testQuicksortBuggy3 :: Int -> Bool
testQuicksortBuggy3 n = quicksortBuggy [1..n] == [1..n]

testQuicksortBuggy4 :: [Int] -> Bool
testQuicksortBuggy4 l = length l == length (quicksortBuggy l)


-- Testare pentru tipuri de date algebrice

data ElemIS = I Int | S String
    deriving(Show,Eq)

instance Arbitrary ElemIS where
    arbitrary = do
        x <- arbitrary
        y <- arbitrary
        return $ if x `div` 2 == 0 then I x else S y

myLookUpElem :: Int -> [(Int,ElemIS)]-> Maybe ElemIS
myLookUpElem _ [] = Nothing
myLookUpElem elem ((key,val):xs) = if elem == key then Just val else myLookUpElem elem xs

testLookUpElem :: Int -> [(Int,ElemIS)] -> Bool
testLookUpElem n list = myLookUpElem n list == lookup n list

runTest2 :: IO ()
runTest2 = quickCheck testLookUpElem