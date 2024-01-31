{-# LANGUAGE FlexibleInstances #-}
{-# OPTIONS_GHC -Wno-overlapping-patterns #-}
{- Monada Maybe este definita in GHC.Base 

instance Monad Maybe where
  return = Just
  Just va  >>= k   = k va
  Nothing >>= _   = Nothing


instance Applicative Maybe where
  pure = return
  mf <*> ma = do
    f <- mf
    va <- ma
    return (f va)       

instance Functor Maybe where              
  fmap f ma = pure f <*> ma   
-}

(<=<) :: (a -> Maybe b) -> (c -> Maybe a) -> c -> Maybe b
f <=< g = \x -> g x >>= f

-- 1.1
f x = Just (x * 10)
g x = Just (x + 10)
testMonad = f <=< g

-- 1.2
  
asoc :: (Int -> Maybe Int) -> (Int -> Maybe Int) -> (Int -> Maybe Int) -> Int -> Bool
asoc f g h x = (h <=< (g <=< f) $ x) == ((h <=< g) <=< f $ x)

-- 2
pos :: Int -> Bool
pos x = x >= 0

foo :: Maybe Int ->  Maybe Bool
--foo mx = mx >>= (\x -> Just (pos x))

-- 2.1
-- Functia foo foloseste Monada pentru a verifica daca valoare lui Maybe este pozitiva

-- 2.2
foo mx = do
    x <- mx
    Just (pos x)

-- 3
-- 3.1
addM :: Maybe Int -> Maybe Int -> Maybe Int
addM (Just x) (Just y) = Just (x + y)
addM _ _ = Nothing 

-- 3.2
addM' :: Maybe Int -> Maybe Int -> Maybe Int
addM' mx my = do
    x <- mx
    y <- my
    Just (x + y)

-- 3.3
testAddM :: Maybe Int -> Maybe Int -> Bool
testAddM mx my= addM mx my == addM' mx my

-- 4
cartesian_product xs ys = do
  x <- xs
  y <- ys
  return (x, y)
  
prod f xs ys = [f x y | x<-xs, y<-ys]

myGetLine :: IO String 
myGetLine = do
  x <- getChar 
  if x == '\n' then
    return []
  else do
    xs <- myGetLine
    return (x:xs)

-- 5

  