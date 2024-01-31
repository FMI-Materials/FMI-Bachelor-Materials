--- Monada Identity

newtype Identity a = Identity { runIdentity :: a }

type M = Identity
--- Limbajul si  Interpretorul

instance Show a => Show (Identity a)where
    show (Identity a) = show a

instance Monad Identity where
   return x = Identity x
   (Identity a) >>= ma = ma a

instance Applicative Identity where
  pure = return
  a <*> b = do
    f <- a
    f <$> b

instance Functor Identity where
  fmap f a = f <$> a

showM :: Show a => M a -> String
showM = undefined

type Name = String

data Term = Var Name
          | Con Integer
          | Term :+: Term
          | Lam Name Term
          | App Term Term
  deriving (Show)

pgm :: Term
pgm = App
  (Lam "y"
    (App
      (App
        (Lam "f"
          (Lam "y"
            (App (Var "f") (Var "y"))
          )
        )
        (Lam "x"
          (Var "x" :+: Var "y")
        )
      )
      (Con 3)
    )
  )
  (Con 4)


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
interp (Lam n t) env = Identity $ Fun (\x -> interp t ((n, x) : env))
interp (App t1 t2) env = case (interp t1 env, interp t2 env) of
     (Identity (Fun f), Identity x) -> f x
     (_, _) -> return Wrong
-- test :: Term -> String
-- test t = showM $ interp t []

pgm1:: Term
pgm1 = App
          (Lam "x" ((Var "x") :+: (Var "x")))
          ((Con 10) :+:  (Con 11))
-- test pgm
-- test pgm1
