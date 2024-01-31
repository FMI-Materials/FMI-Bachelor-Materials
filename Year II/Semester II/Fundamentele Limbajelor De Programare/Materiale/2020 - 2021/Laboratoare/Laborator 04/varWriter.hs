
--- Monada Identity

newtype StringWriter a = StringWriter { runStringWriter :: (a, String) }

type M = StringWriter
--- Limbajul si  Interpretorul

instance Show a => Show (StringWriter a) where
    show sw = let (a, b) = runStringWriter sw in
      "Output: " ++ b ++ "Value: " ++ show a

instance Monad StringWriter where
   return x = StringWriter (x, "")
   sw >>= f = let (a, b) = runStringWriter sw in
              let (StringWriter (a1, b1)) = f a in
                StringWriter (a1, b ++ b1)

instance Applicative StringWriter where
  pure = return
  a <*> b = do
    f <- a
    f <$> b

instance Functor StringWriter where
  fmap f a = f <$> a

showM :: Show a => M a -> String
showM = show

type Name = String

data Term = Var Name
          | Con Integer
          | Term :+: Term
          | Lam Name Term
          | App Term Term
          | Out Term
  deriving (Show)


data Value = Num Integer
           | Fun (Value -> M Value)
           | Wrong

instance Show Value where
 show (Num x) = show x
 show (Fun _) = "<function>"
 show Wrong   = "<wrong>"

type Environment = [(Name, Value)]

interp :: Term -> Environment -> M Value
interp (Var n) env = case lookup n env of
     Nothing -> return Wrong
     (Just x) -> return x
interp (Con x) _ = return (Num x)
interp (t1 :+: t2) env = do
     v1 <- interp t1 env
     v2 <- interp t2 env
     case (v1, v2) of
       (Num x, Num y) -> return (Num (x + y))
       (_, _) -> return Wrong
interp (Lam n t) env = return $ Fun (\x -> interp t ((n, x) : env))
interp (App t1 t2) env = case (interp t1 env, interp t2 env) of
     (StringWriter (Fun f, _), StringWriter (x, _)) -> f x
     (_, _) -> return Wrong
interp (Out t) env = do
     v <- interp t env
     StringWriter (v, show v ++ "; ")


test :: Term -> String
test t = showM $ interp t []

pgm1:: Term
pgm1 = App (Lam "x" ((Out (Var "x") :+: Out (Con 1)) :+: Con 33)) (Con 12)
-- test pgm
-- test pgm1
