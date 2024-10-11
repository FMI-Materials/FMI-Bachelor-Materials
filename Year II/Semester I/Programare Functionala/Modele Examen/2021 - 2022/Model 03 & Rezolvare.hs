import Prelude
import Data.List

--I
--1 a (==) pentru ca nu e necesar sa definesti ambele functii
--2 c (se face == si intre variabile de tip a, si intre variabile de tip b)

data MyData a b = MyData a b b
f :: (Eq a, Eq b) => MyData a b -> MyData a b -> Bool
f (MyData x1 y1 z1) (MyData x2 y2 z2 ) = x1 == x2 && y1 == y2 && z1 == z2

--3 a
-- sa zicem ca ai tipu de date data Tip x1 x2 x3 .. xn
-- part 1
-- ca sa faci functor, trebuie sa apelezi pe toate in afara de ultima
-- instance Functor (Tip x1 x2 x3 .. xn-1 **lipseste xn) where
-- part 2 functorul modifica decat variabilele de tipul pe care nu l-ai pus in antet
-- adica aici pe xn

data MyData2 a b e f g h c = MyData2 a c b f
instance Functor (MyData2 a b e f g h) where
    fmap f (MyData2 x y z w) = MyData2 x (f y) z w

--4 a

--5 a
-- mempty e in monoid, operatia de <> e in semigrup. un monoid include un semigrup
-- adica daca nu ai semigrupul definit cu <> nu poti face un monoid
-- mempty este 
newtype MyBool = MyBool Bool
    deriving (Eq, Show)

instance Semigroup MyBool where
    MyBool x <> MyBool y = MyBool ( x || y )
instance Monoid MyBool where
    mempty = MyBool True

--6 a
-- x <> y = x + y + 1
-- 0 <> 5 = 0 + 5 + 1 = 6 nu e corect ca tre sa-ti dea tot 5
-- -1 <> 5 = 5 + 1 - 1 = 5

--7 a
-- nu e c ca are MyData a b si trebuie doar MyData a
-- avem MyData a b b, deci vrem sa facem foldable doar pe elementele de tipul b
-- punctu b face pe un element de tip b, dar nu pe toate 
-- punctu d face pe element de tip a

--8 a
-- d are tipul b inclus
-- c returneaza Data 1 in loc de valoare, cand elementul nu e de tipul cerut
-- se returneaza mempty
-- b returneaza f x, dar trebuie sa returneze mempty

--9 a

--10 eroare, trebuie sa fie lista de functii dar e doar functie

--II

--1
f1 :: String -> String -> String
f1 [] _ = ""
f1 _ [] = ""
f1 (c1:str1) (c2:str2)
    | c1 == c2 = c1 : f1 str1 str2
    | otherwise = ""

-- "s" : "i" : "r" : (f "ulnr1" "doi") = "sir"

--2
f2 :: [Int] -> [Int] -> Int
f2 [] [] = 0
f2 (c1:list1) (c2:list2)
    | length list1 /= length list2 = error "parametri de lungime diferita"
    | otherwise = (c1^2) * (c2^2) + f2 list1 list2

--varianta 2
f3 :: [Int] -> [Int] -> Int
f3 list1 list2
    | length list1 /= length list2 = error "parametri de lungime diferita"
    | otherwise =  sum [(fst c)^2 * (snd c)^2 |c <- list1 `zip` list2]

--III
--a
data PairInt = P Int Int deriving Show
data MyList = L [PairInt] deriving Show

data Exp = I Int | Add Exp Exp | Mul Exp Exp deriving Show

class MyClass m where
    toExp :: m -> Exp

instance MyClass MyList where
    toExp (L []) = I 1
    toExp (L ((P e1 e2):xs)) = Mul (Add (I e1) (I e2)) (toExp (L xs))

--b
evalAux :: Exp -> Int
evalAux (I x) = x
evalAux (Mul arb1 arb2) = evalAux arb1 * evalAux arb2
evalAux (Add arb1 arb2) = evalAux arb1 + evalAux arb2

eval :: MyList -> Int 
eval list = evalAux (toExp list)
    