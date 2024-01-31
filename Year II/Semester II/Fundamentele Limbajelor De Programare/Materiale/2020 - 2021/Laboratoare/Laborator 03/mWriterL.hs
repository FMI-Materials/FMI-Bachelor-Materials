
--- Monada Writer



newtype WriterLS a = Writer { runWriter :: (a, [String]) } deriving (Show)


instance  Monad WriterLS where
  return va = Writer (va, [])
  ma >>= k = let (va, log1) = runWriter ma
                 (vb, log2) = runWriter (k va)
             in  Writer (vb, log1 ++ log2)


instance  Applicative WriterLS where
  pure = return
  mf <*> ma = do
    f <- mf
    f <$> ma

instance  Functor WriterLS where
  fmap f ma = f <$> ma


-- 2
tell :: String -> WriterLS ()
tell log = Writer ((), [log])

logIncrement :: Int  -> WriterLS Int
logIncrement x = Writer (x + 1, ["increment: " ++ show x])


logIncrementN :: Int -> Int -> WriterLS Int
logIncrementN x 0 = return x
logIncrementN x n =  do
  y <- logIncrement x
  logIncrementN y (n-1)

-- 3
isPos :: Int -> WriterLS Bool
isPos x = if x>= 0 then Writer (True, ["poz"]) else Writer (False, ["neg"])


mapWriterLS :: (a -> WriterLS b) -> [a] -> WriterLS [b]
mapWriterLS _ [] = return []
mapWriterLS f (x:xs) = do
  h <- f x
  rest <- mapWriterLS f xs
  return $ h : rest
