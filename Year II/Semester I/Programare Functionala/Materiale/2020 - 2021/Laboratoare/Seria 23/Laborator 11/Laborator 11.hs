{-# LANGUAGE FlexibleInstances #-}
import Data.Monoid
import Data.Semigroup (Max (..), Min (..))
import Data.Foldable (foldMap, foldr)
import Data.Char (isUpper)

elem' :: (Foldable t, Eq a) => a -> t a -> Bool
elem' x = getAny . foldMap (Any . (==x))

null' :: (Foldable t) => t a -> Bool
null' = getAll . foldMap (All . (const False))

length' :: (Foldable t) => t a -> Int
length' = getSum . foldMap (Sum . (const 1))

toList :: (Foldable t) => t a -> [a]
toList = foldMap (:[])

fold :: (Foldable t, Monoid m) => t m -> m
fold = foldMap id

data Constant a b = Constant b
instance Foldable (Constant a) where
   foldMap f (Constant b) = f b

data Two a b = Two a b deriving Show
instance Foldable (Two a) where
   foldMap f (Two a b) = f b

data Three a b c = Three a b c deriving Show
instance Foldable (Three a b) where
   foldMap f (Three a b c) = f c

data Three' a b = Three' a b b deriving Show
instance Foldable (Three' a) where
   foldMap f (Three' a b1 b2) = f b1 <> f b2

data Four' a b = Four' a b b b
instance Foldable (Four' a) where
   foldMap f (Four' a b1 b2 b3) = f b1 <> f b2 <> f b3

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)

filterF :: (Applicative f, Foldable t, Monoid (f a)) => (a -> Bool) -> t a -> f a
filterF f = foldMap select
   where 
     select a
      | f a = pure a
      | otherwise = mempty

unit_testFilterF1 = (filterF Data.Char.isUpper "aNA aRe mEre") == "NARE"
unit_testFilterF2 = filterF Data.Char.isUpper "aNA aRe mEre" == First (Just 'N')
unit_testFilterF3 = filterF Data.Char.isUpper "aNA aRe mEre" == Min 'A'
unit_testFilterF4 = filterF Data.Char.isUpper "aNA aRe mEre" == Max 'R'
unit_testFilterF5 = filterF Data.Char.isUpper "aNA aRe mEre" == Last (Just 'E')

newtype Identity a = Identity a
 
data Pair a = Pair a a
 
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
   fmap f (K a) = K a
 
newtype Flip f a b = Flip (f b a) deriving (Eq, Show)
  -- pentru Flip nu trebuie să faceți instanță

instance Functor (Flip K a) where
   fmap f (Flip (K b)) = Flip (K (f b)) 
 

data LiftItOut f a = LiftItOut (f a)
instance Functor f => Functor (LiftItOut f) where
   fmap f (LiftItOut fa) = LiftItOut (fmap f fa) 

data Parappa f g a = DaWrappa (f a) (g a)
instance (Functor f, Functor g) => Functor (Parappa f g) where
   fmap f (DaWrappa fa ga) = DaWrappa (fmap f fa) (fmap f ga)

data IgnoreOne f g a b = IgnoringSomething (f a) (g b)
instance (Functor g) => Functor (IgnoreOne f g a) where
   fmap f (IgnoringSomething fa gb) = IgnoringSomething fa (fmap f gb)

data Notorious g o a t = Notorious (g o) (g a) (g t)
instance (Functor g) => Functor (Notorious g o a) where
   fmap f (Notorious go ga gt) = Notorious go ga (fmap f gt)

-- scrieți o instanță de Functor pentru tipul GoatLord de mai sus
-- data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)

instance Functor GoatLord where
   fmap _ NoGoat = NoGoat
   fmap f (OneGoat a) = OneGoat (f a)
   fmap f (MoreGoats g1 g2 g3) = MoreGoats (fmap f g1) (fmap f g2) (fmap f g3)


data TalkToMe a = Halt | Print String a | Read (String -> a)
instance Show (TalkToMe a) where
   show Halt = "Halt"
   show (Print s a) = "Print: "++s++" " 
instance Functor TalkToMe where
   fmap _ Halt = Halt
   fmap f (Print s a) = Print s (f a)
   fmap f (Read sa) = Read (f . sa)


main = undefined


