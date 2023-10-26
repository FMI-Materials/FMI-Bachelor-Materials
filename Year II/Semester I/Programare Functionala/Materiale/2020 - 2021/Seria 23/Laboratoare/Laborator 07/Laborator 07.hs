import Test.QuickCheck
import Data.Char
double :: Int -> Int
double a = 2 * a
triple :: Int -> Int
triple a = 3 * a
penta :: Int -> Int
penta a = 5 * a

test x = (double x + triple x) == (penta x)

myLookUp :: Int -> [(Int,String)]-> String
myLookUp _ [] = "rau"
myLookUp a b = if a == (fst (b !! 0)) then "bun" else "rau"

testLookUp :: Int -> [(Int,String)] -> Bool
testLookUp a b = (myLookUp a b) == "rau"

-- testLookUpCond :: Int -> [(Int,String)] -> Property
-- testLookUpCond n list = n > 0 && n `div` 5 == 0 ==> testLookUp n list

data ElemIS = I Int | S String
     deriving (Show,Eq)

instance Arbitrary ElemIS where
  arbitrary = do
    i <- arbitrary
    s <- arbitrary
    elements[I i, S s]

myLookUp' :: Int -> [(Int, String)] -> Maybe String
myLookUp' nr [] = Nothing
myLookUp' nr ((n, sirul) : t)
     | n == nr && sirul == "" = Just ""
     | n == nr = let (c:sir ) = sirul in Just ((toUpper c) : sir)  --sau daca vrem ca restul sa fie litere mici
     | otherwise = myLookUp' nr t                                  -- punem (map toLower sir) in loc de sir

myLookUpElem :: Int -> [(Int,ElemIS)]-> Maybe ElemIS
myLookUpElem x list = let l = [s | (i,s)<-list,i==x] in if length l == 0 then Nothing else Just $ head l


testLookUpElem :: Int -> [(Int,ElemIS)] -> Bool
testLookUpElem x l = myLookUpElem x l == lookup x l

main = undefined
