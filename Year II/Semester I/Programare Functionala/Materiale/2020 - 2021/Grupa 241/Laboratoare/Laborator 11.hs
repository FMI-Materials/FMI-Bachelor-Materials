{-# LANGUAGE FlexibleInstances #-}
import Data.Monoid
import Data.Semigroup (Max (..), Min (..))
import Data.Foldable (foldMap, foldr)
import Data.Char (isUpper)

--let xs=map Sum[1..5] --monoidul cu suma => [Sum {getSum = 1},Sum {getSum = 2},Sum {getSum = 3},Sum {getSum = 4},Sum {getSum = 5}]
--fold xs => Sum {getSum=15}

--fold (+) [1,2,3,4,5] => Eroare pt ca [1,2,3,4,5] trebuie sa fie Foldable

-- map Product [1,5] => [Product {getProduct = 1},Product {getProduct = 5}]
--let xs=map Product [1..5] --monoidul cu inmultirea
--fold xs => Product {getProduct=120}

--fold ["Nu am", "restante"] => "Nu am restante" <=> foldr (++) ""["Nu..", ".."]
  --Merge pt ca (++) cu String e Monoid
--fold-ului ii dau lista de elemente si el foloseste automat operatia din monoid

-- :t FoldMap fold + map + Sum [1..4] => foldMap Sum[1..4]
-- foldMap Sum [1..4]
-- Sum {getSum=10}
--foldMap Product[1..4]
--Product {getProduct =24} --1*2*3*4

--let fm=foldMap(+1)
--fm Nothing ::Sum Integer
--Sum { getSum=0}

data BinaryTree a=Leaf a
                  |Node (BinaryTree a )(BinaryTree a)
                  deriving Show
foldTree:: (a->b->b) -> b-> BinaryTree a -> b
foldTree f i (Leaf x) =f x i

--daca x e element al unei liste date
elem :: (Foldable t, Eq a) => a -> t a -> Bool
elem x l = foldr (\a curent -> a== x || curent) False l
--elem x = getAny . foldMap (Any . (== x))

--verifica daca o lista data e goala
null :: (Foldable t) => t a -> Bool
null l = foldr (\a curent -> False) True l
--null = getAll . foldMap (All . const False)

--returneaza lungimea unei liste
length :: (Foldable t) => t a -> Int
length l = foldr (\a curent -> curent + 1) 0 l
--length = getSum . foldMap (Sum . const 1)

--face lista din al doilea element din pereche
toList :: (Foldable t) => t a -> [a]
toList x = foldr (\a curent -> a : curent) [] x
--toList = foldMap (: [])

--fold combină elementele unei structuri folosind structura de monoid a acestora.
fold :: (Foldable t, Monoid m) => t m -> m
fold = foldMap id -- Hint: folosiți foldMap

data Constant a b = Constant b
instance Foldable (Constant a ) where
  foldMap f (Constant b)=f b
-- foldr f b (Constant x) = f x b

data Two a b = Two a b
               deriving Show
instance Foldable (Two a) where
  foldMap f (Two a b)=f b
-- foldr f b (Two _ y) = f y b

data Three a b c = Three a b c
instance Foldable (Three a b ) where
  foldMap f (Three a b c)=f c
--foldMap Sum (Two "a" 1) => Sum {getSum =1} 
--foldr f b (Three _ _ z) = f z b
--foldMap f (Three _ _ z) = f z

data Three' a b = Three' a b b
instance Foldable (Three' a) where
  foldMap f (Three' a b1 b2) =f b1 <> f b2
-- foldr f b (Three' _ y z) = f z (f y b)
--foldMap f (Three' _ y z) = f z <> f y

--foldMap Sum (Three' 1 2 3)
--Sum {getSum=5}
--foldMap Product (Three' 1 2 3)
--Product {getProduct=6}

data Four' a b = Four' a b b b
instance Foldable (Four' a) where
  foldMap f (Four' a b1 b2 b3)= f b1 <> f b2 <> f b3
-- foldr f b (Four' _ y z t) = f t $ f z $ f y b
-- foldMap f (Four' _ y z t) = f t <> f z <> f y

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)
                  deriving Show
instance Foldable GoatLord where
  -- foldr f b = go
  --   where
  --     go NoGoat = b
  --     go (OneGoat a) = f a b
  --     go (MoreGoats a1 a2 a3) = foldr f (foldr f (foldr f b a1) a2) a3
  foldMap f = go
    where
      go NoGoat = mempty
      go (OneGoat a) = f a
      go (MoreGoats a1 a2 a3) = go a1 <> go a2 <> go a3

--ex3
filterF ::( Applicative f, Foldable t, Monoid (f a)) => (a -> Bool) -> t a -> f a
filterF f = foldMap select
          where
            select a
              | f a = pure a
              | otherwise = mempty -- Hint folosiți foldMap

unit_testFilterF1 = filterF Data.Char.isUpper "aNA aRe mEre" == "NARE"
unit_testFilterF2 = filterF Data.Char.isUpper "aNA aRe mEre" == First (Just 'N')
unit_testFilterF3 = filterF Data.Char.isUpper "aNA aRe mEre" == Min 'A'
unit_testFilterF4 = filterF Data.Char.isUpper "aNA aRe mEre" == Max 'R'
unit_testFilterF5 = filterF Data.Char.isUpper "aNA aRe mEre" == Last (Just 'E')

--Exercitii pentru Functor
newtype Identity a = Identity a

instance Functor Identity where
  fmap f (Identity a) = Identity (f a)

data Pair a = Pair a a
instance Functor Pair where
  fmap f (Pair a1 a2) = Pair (f a1) (f a2)
  
-- scrieți instanță de Functor pentru tipul Two de mai sus
instance Functor (Two a) where
  fmap f (Two a b) = Two a (f b)
 
-- scrieți instanță de Functor pentru tipul Three de mai sus
instance Functor (Three a b) where
  fmap f (Three a b c) = Three a b (f c)
 
-- scrieți instanță de Functor pentru tipul Three' de mai sus
instance Functor (Three' a) where
  fmap f (Three' a b1 b2) = Three' a (f b1) (f b2)
 
data Four a b c d = Four a b c d
instance Functor (Four a b c) where
  fmap f (Four a b c d) = Four a b c (f d)
 
data Four'' a b = Four'' a a a b
instance Functor (Four'' a) where
  fmap f (Four'' a1 a2 a3 b) = Four'' a1 a2 a3 (f b) 

-- scrieți o instanță de Functor penru tipul Constant de mai sus
instance Functor (Constant a) where
  fmap f (Constant b) = Constant (f b)

data Quant a b = Finance | Desk a | Bloor b
instance Functor (Quant a) where
  fmap _ Finance = Finance
  fmap _ (Desk a) = Desk a
  fmap f (Bloor b) = Bloor (f b)
 
data K a b = K a
instance Functor (K a) where
  fmap _ (K a) = K a

 
newtype Flip f a b = Flip (f b a) deriving (Eq, Show)
  -- pentru Flip nu trebuie să faceți instanță
instance Functor (Flip K a) where
  fmap f (Flip (K b)) = Flip (K (f b))

data LiftItOut f a = LiftItOut (f a)
instance Functor fa => Functor (LiftItOut fa) where
  fmap f (LiftItOut fa) = LiftItOut (fmap f fa)
 
data Parappa f g a = DaWrappa (f a) (g a)
instance (Functor fa, Functor ga) => Functor (Parappa fa ga) where
  fmap f (DaWrappa fa ga) = DaWrappa (fmap f fa) (fmap f ga)
 
data IgnoreOne f g a b = IgnoringSomething (f a) (g b)
instance Functor gb => Functor (IgnoreOne fa gb a) where
  fmap f (IgnoringSomething fa gb) = IgnoringSomething fa (fmap f gb)

data Notorious g o a t = Notorious (g o) (g a) (g t)
instance Functor g => Functor (Notorious g o a) where
  fmap f (Notorious go ga gt) = Notorious go ga (fmap f gt)

-- scrieți o instanță de Functor pentru tipul GoatLord de mai sus
instance Functor GoatLord where
  fmap f = go
    where
      go NoGoat = NoGoat
      go (OneGoat a) = OneGoat (f a)
      go (MoreGoats a1 a2 a3) = MoreGoats (go a1) (go a2) (go a3)
 
data TalkToMe a = Halt | Print String a | Read (String -> a)
instance Functor TalkToMe where
  fmap f = go
    where
      go Halt = Halt
      go (Print s a) = Print s (f a)
      go (Read sa) = Read (f . sa)
