import Prelude hiding (lookup)
import qualified Data.List as List
import Data.List
import Test.QuickCheck
import Numeric.Natural
import Data.Char
import Data.List (nub)
import Data.Maybe (fromJust)
import Test.QuickCheck
import Test.QuickCheck.Gen
import Data.Monoid
import Data.Semigroup (Max (..), Min (..))
import Data.Foldable (foldMap, foldr)
import Data.Char (isUpper)
import Data.List (nub)

data Arbore a
    = Nod (Arbore a) a (Arbore a)
    | Frunza a 
    | Vid
    deriving (Eq, Ord)
 
--1
--Punctul a)
--fac lista cu valorile din noduri
fvvv :: Arbore a -> [a]
fvvv Vid =[]
fvvv (Frunza a)=[a]
fvvv (Nod arb1 value arb2)= (fvvv arb1) ++ [value] ++ (fvvv arb2)

--verific sa fie unice
funic :: Eq a=> [a] -> Bool
funic l =length l == length (nub l)

--verific sa fie in ordine crescatoare
fcresc:: Ord a=> [a] -> Bool
fcresc l = and [x<y| (x,y)<- zip l (tail l)]

--functie ceruta la a)
faaa :: Ord a=> Arbore a-> Bool
faaa arb = (funic (fvvv arb)) && (fcresc (fvvv arb))


--Teste
t1= faaa (Nod (Nod (Frunza 22) 8 (Frunza 9)) 10 (Nod (Frunza 11) 13 (Frunza 14)))==False
--True
t2= faaa (Nod (Nod (Frunza 7) 8 (Frunza 9)) 10 (Nod (Frunza 11) 13 (Frunza 14)))==True
--True

--Punctul b)
finsert :: (Ord a) => Arbore a -> a -> Arbore a
finsert Vid a =Nod Vid a Vid
finsert (Frunza val) a= if (a<val) then Nod (Frunza a) val Vid else Nod Vid val (Frunza a)
finsert (Nod arb1 val arb2)  a= if (a< val) then Nod (finsert arb1 a) val arb2 else Nod arb1 val (finsert arb2 a)

--Test
-- *Main> finsert (Nod (Nod (Frunza 7) 8 (Frunza 9)) 10 (Nod (Frunza 11) 13 (Frunza 14))) 1
-- Nod (Nod (Nod (Frunza 1) 7 Vid) 8 (Frunza 9)) 10 (Nod (Frunza 11) 13 (Frunza 14))

--Punctul c)
instance Functor Arbore where
    fmap f (Frunza a) = Frunza (f a) 
    fmap f (Nod arb1 a arb2) = Nod (fmap f arb1) (f a) (fmap f arb2)
--Test
-- *Main> fmap (*2)  (Nod (Nod (Frunza 7) 8 (Frunza 9)) 10 (Nod (Frunza 11) 13 (Frunza 14)))
--Nod (Nod (Frunza 14) 16 (Frunza 18)) 20 (Nod (Frunza 22) 26 (Frunza 28))

---2)
--Punctul a)
instance Foldable Arbore where
    foldr f acc Vid = acc
    foldr f acc (Frunza a) = f a (foldr f acc Vid)
    foldr f acc (Nod arb1 x arb2) = foldr f (f x (foldr f acc arb2)) arb1

--Test
-- *Main> foldr (+) 0 (Nod (Nod (Frunza 7) 8 (Frunza 9)) 10 (Nod (Frunza 11) 13 (Frunza 14)))
-- 72

--Punctul b)
instance (Show a)  => Show (Arbore a)  where
    show Vid = ""
    show (Frunza x) = show x
    show (Nod l k r) = show l ++", " ++ show k ++", " ++ show r