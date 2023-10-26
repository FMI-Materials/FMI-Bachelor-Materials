import Data.Monoid

-- FOLDABLE

-- 1. implementati functiile elem, null, length, toList, fold
-- folosind functiile foldMap si foldr din clasa Foldable

elem' :: (Foldable t, Eq a) => a -> t a -> Bool
elem' x col = getAny $ foldMap f col
            where f el = Any (x == el)

null' :: (Foldable t) => t a -> Bool
null' = foldr (\_ _ -> False) True

length' :: (Foldable t) => t a -> Int
length' = foldl (\c _ -> c+1) 0 

-- 2. scrieti instance ale lui Foldable pentru urmatoarele
-- tipuri implmentand functia foldMap

-- a
data Constant a b = Constant b

instance Foldable (Constant a) where
    foldMap f (Constant x) = f x

-- b
data Two a b = Two a b

instance Foldable (Two a) where
    foldMap f (Two x y) = f y


-- c
data Three a b c = Three a b c

instance Foldable (Three a b) where
    foldMap f (Three x y z) = f z

-- d
data Three' a b = Three' a b b

instance Foldable (Three' a) where
    foldMap f (Three' x y z) = f y <> f z

-- e
data Four' a b = Four' a b b b

instance Foldable (Four' a) where
    foldMap f (Four' x y z t) = f y <> f z <> f t

-- f
data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)

instance Foldable GoatLord where
    foldMap f NoGoat = mempty
    foldMap f (OneGoat x) = f x
    foldMap f (MoreGoats x y z) = foldMap f x <> foldMap f y <> foldMap f z

