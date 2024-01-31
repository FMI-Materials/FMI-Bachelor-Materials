{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE UndecidableInstances #-}
--- Monada M

newtype EnvReader a = Reader { runEnvReader :: Environment -> a }

type M = EnvReader

instance Show (Environment -> a) => Show (EnvReader a) where
  show (Reader x) = show x

instance Monad EnvReader where
  return x = Reader $ const x
  a >>= f = Reader (\env -> let x = runEnvReader a env in runEnvReader (f x) env)

instance Applicative EnvReader where
  pure = return
  a <*> b = do
    f <- a
    f <$> b

instance Functor EnvReader where
  fmap f a = f <$> a

--- Limbajul si  Interpretorul

showM :: Show a => M a -> String
showM e = show $ runEnvReader e []

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
 show Wrong = "<wrong>"

type Environment = [(Name, Value)]

ask :: EnvReader Environment
ask = Reader id

local :: (Environment -> Environment) -> EnvReader a -> EnvReader a
local f (Reader transf) = Reader (transf . f)

interp :: Term -> M Value
interp (Var n) = do
  env <- ask
  case lookup n env of
    (Just x) -> return x
    _ -> return Wrong
interp (Con x) = return (Num x)
interp (t1 :+: t2) = do
     env <- ask
     v1 <- interp t1
     v2 <- interp t2
     case (v1, v2) of
       (Num x, Num y) -> return (Num (x + y))
       (_, _) -> return Wrong
interp (Lam n t) = do
     env <- ask
     return $ Fun $ \x -> local (const $ (n, x): env) $ interp t
interp (App t1 t2) = do
     env <- ask
     intf <- interp t1
     intv <- interp t2
     case intf of
       Fun f -> f intv
       _ -> return Wrong


test :: Term -> String
test t = showM $ interp t

pgm1:: Term
pgm1 = App
          (Lam "x" (Var "x" :+: Var "x"))
          (Con 10 :+:  Con 11)
-- test pgm
-- test pgm1
