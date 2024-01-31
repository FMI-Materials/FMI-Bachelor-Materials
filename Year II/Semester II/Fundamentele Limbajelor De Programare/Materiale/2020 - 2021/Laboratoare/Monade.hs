-- TOATE MONADELE


-- the type of monad m
data m a = ...

-- return ia o valoare si o impacheteaza in monada
return :: a -> m a

-- bind is a function that combines a monad instance m a with a computation
-- that produces another monad instance m b from a's to produce a new
-- monad instance m b
(>>=) :: m a -> (a -> m b) -> m b


{-

showM :: Show a => M a -> String
showM ma = let (va, news) = (runState ma 0) in "Value: " ++ (show va) ++ " Count: " ++ (show news)

-}

-- MONADA MAYBE -- pentru a marca erorile mai bine

{- Monada Maybe este definita in GHC.Base 

instance Monad Maybe where
  return = Just
  Just va  >>= k = k va --> functia k se aplica pe va
  Nothing >>= _ = Nothing


instance Applicative Maybe where
  pure = return
  mf <*> ma = do
    f <- mf
    va <- ma
    return (f va)       

instance Functor Maybe where              
  fmap f ma = pure f <*> ma   
-}


-- MONADA WRITER

{-

este folosita pentru a acumula (logging) informatia produsa în timpul executiei

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
    a <- ma
    return (f a)       

instance  Functor WriterS where              
  fmap f ma = pure f <*> ma  

tell :: String -> WriterS () 
tell log = Writer ((), log) 


-}

-- MONADA READER

{-

newtype Reader env a = Reader { runReader :: env -> a }

instance Monad (Reader env) where
  return x = Reader (\_ -> x)
  ma >>= k = Reader f
    where f env = let a = runReader ma env
                  in  runReader (k a) env


instance Applicative (Reader env) where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)

instance Functor (Reader env) where
  fmap f ma = pure f <*> ma


ask :: Reader env env
ask = Reader id

local :: (env -> env) -> Reader env a -> Reader env a
local f ma = Reader $ (\r -> (runReader ma)(f r))

-}



-- MONADA IDENTITY


-- Monada Identity

{-
newtype Identity a = Identity { runIdentity :: a }


instance Show a => Show (Identity a) where
    show p = show (runIdentity p)
    

instance Monad Identity where
  return = Identity
  va  >>= k = k (runIdentity va) -- k :: a -> va


instance Applicative Identity where
  pure = return
  mf <*> ma = do
    f <- mf
    va <- ma
    return (f va)       

instance Functor Identity where              
  fmap f ma = pure f <*> ma   
-}


-- MONADA EITHER -- pentru a marca erorile mai bine

{-
newtype EitherT a m b = EitherT { runEitherT :: m (Either a b) }

instance Monad (Either e) where
        return = Right
        Right m >>= k = k m
        Left e  >>= _ = Left e

instance Applicative (Either e) where
	pure = Right
	a <*> b = do x <- a; y <- b; return (x y)

instance Functor f => Functor (EitherT a f) where
	fmap f = EitherT . fmap (fmap f) . runEitherT
    
-}


-- MONADA STATE

{-

newtype IntState a = IntState { runIntState :: Integer -> (a, Integer) }

instance Show a => Show (IntState a) where
    show val = show (runIntState val 0)
    
instance Monad (IntState) where
    return x = IntState (\s -> (x,s))
    ma >>= k = IntState f
        where f s = let (a, i1) = runIntState ma s
                        (b, i2) = runIntState (k a) i1
                    in (b, i2)

instance  Applicative IntState where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance  Functor IntState where              
  fmap f ma = pure f <*> ma  
  
modify :: (Integer -> Integer) -> IntState ()
modify f =  IntState (\s -> ((), f s))

get :: IntState Integer  
get = IntState (\s -> (s,s)) 

tickS :: IntState ()
tickS = modify (\x -> x+1)

-}