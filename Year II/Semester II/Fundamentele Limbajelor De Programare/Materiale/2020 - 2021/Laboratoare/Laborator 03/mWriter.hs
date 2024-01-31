
--- Monada Writer

newtype WriterS a = Writer { runWriter :: (a, String) }


instance  Monad WriterS where
  return va = Writer (va, "")
  ma >>= k = let (va, log1) = runWriter ma
                 (vb, log2) = runWriter (k va)
             in  Writer (vb, log1 ++ log2)


instance  Applicative WriterS where
  pure = return
  mf <*> ma = do
    f <- mf
    f <$> ma

instance  Functor WriterS where
  fmap f ma = f <$> ma

tell :: String -> WriterS ()
tell log = Writer ((), log)

-- 1.1
logIncrement :: Int  -> WriterS Int
logIncrement x = do
  tell ("increment: " ++ show x ++ "\n")
  return (x + 1)

logIncrement2 :: Int  -> WriterS Int
logIncrement2 x = do
  y <- logIncrement x
  logIncrement y

--
logIncrementN :: Int -> Int -> WriterS Int
logIncrementN x 0 = return x
logIncrementN x n =  do
  y <- logIncrement x
  logIncrementN y (n-1)



