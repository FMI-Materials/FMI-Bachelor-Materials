f :: a -> b -> c

pure f :: m (a -> b -> c)

ma :: m a
mb :: m b

pure f <*> ma <*> mb   ::  m c

fmap f ma <*> mb

f <$> ma <*> mb :: m c


[(1 +), (3 *)] <*> [2, 4]
[3, 5, 6, 12]



instance Applicative [] where
  pure a    = [a]
  lf <*> la = [ f a  | f <- fa, a <- la ]


env -> a

instance Functor ((->) env) where
  -- fmap :: (a -> b)  -> (env -> a) -> (env -> b)
  fmap f ca = f . ca

instance Applicative ((->) env) where
  -- pure :: a -> (env -> a)
  pure a = \env -> a
  -- (<*>) :: (env -> (a -> b)) -> (env -> a) -> (env -> b)
  cf <*> ca = \env -> cf env (ca env)
  
  
  ZipList lf <*> ZipList la = ZipList (zipWith ($) lf la)
  
  zipWith3 :: (a -> b -> c -> d) -> [a] -> [b] -> [c] -> [d]
  zipWith3 f la lb lc = get (pure f <*> ZipList la <*> ZipList lb <*> ZipList lc)
  
  
  (.) :: (b -> c) -> (a -> b) -> (a -> c)
  
  pure (.) :: m ((b -> c) -> (a -> b) -> (a -> c))
  
  mg :: m (b -> c)
  mf :: m (a -> b)
  ma :: m a
  
  pure (.) <*> mg <*> mf <*> ma === mg <*> (mf <*> ma)
  
  
  
newtype Parser a = Parser { apply :: String -> [(a, String)] }
  
apply pa s :: [(a, String)]
  
fmap :: (a -> b) -> Parser a -> Parser b
fmap f pa = Parser (\s -> [(f a, rest) | (a, rest) <- apply pa s ]



Exp -> Termen
Exp -> Termen + Exp

Termen -> Factor
Termen -> Factor * Termen

Factor -> Int
Factor -> ( Exp )


Exp ::= Termen
      | Termen '+' Exp

Termen ::= Factor
         | Factor '*' Termen

Factor ::= Int
         | '(' Exp ')'



  
  


  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
