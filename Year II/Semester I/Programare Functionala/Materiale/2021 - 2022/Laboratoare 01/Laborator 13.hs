import Data.Monoid
import GHC.ExecutionStack (Location(functionName))
-- Implementati următoarele functii folosind foldMap si/sau foldr din
-- clasa Foldable  apoi testati-le cu mai multe tipuri care au
-- instanta pentru Foldable
elem :: (Foldable t, Eq a) => a -> t a -> Bool
elem cautat = foldr cmp False
    where 
        cmp val soFar 
            | val == cautat = True 
            | otherwise = soFar

null' :: (Foldable t) => t a -> Bool
null' = foldr makeTrue True
    where 
        makeTrue _ _ = False
length :: (Foldable t) => t a -> Int
length = foldr func 0
    where 
        func a nr = nr + 1

toList :: (Foldable t) => t a -> [a]
toList = foldMap func
    where func a = [a]

fold :: (Foldable t, Monoid m) => t m -> m
fold = foldMap funct
    where funct m = m

-- Scrieti instante ale lui Foldable pentru următoarele tipuri, implementand functia foldMap.
data Constant a b = Constant b
instance Foldable (Constant a) where
    foldMap  f (Constant b) = f b

data Two a b = Two a b
instance Foldable (Two a) where
    foldMap f (Two a b) = f b

data Three a b c = Three a b c
instance Foldable (Three a b) where
    foldMap f (Three a b c) = f c

data Three' a b = Three' a b b
instance Foldable (Three' a) where
    foldMap f (Three' a b c) = f b <> f c

data Four' a b = Four' a b b b
instance Foldable (Four' a) where
    foldMap f (Four' a b c d ) = f b <> f c <> f d

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)
instance Foldable GoatLord where
    foldMap f NoGoat = mempty 
    foldMap f (OneGoat a) = f a
    foldMap f (MoreGoats a b c) = foldMap f a <> foldMap f b  <> foldMap f c