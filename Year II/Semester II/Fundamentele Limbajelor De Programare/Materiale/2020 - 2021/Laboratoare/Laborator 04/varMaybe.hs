--- Monada M

-- newtype M a = M { runM :: a }

type M = Maybe
--- Limbajul si  Interpretorul

showM :: Show a => M a -> String
showM = show

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

instance Show Value where
 show (Num x) = show x
 show (Fun _) = "<function>"

type Environment = [(Name, Value)]

interp :: Term -> Environment -> M Value
interp (Var n) env = lookup n env
interp (Con x) _ = return (Num x)
interp (t1 :+: t2) env = do
     v1 <- interp t1 env
     v2 <- interp t2 env
     case (v1, v2) of
       (Num x, Num y) -> return (Num (x + y))
       (_, _) -> Nothing
interp (Lam n t) env = return $ Fun (\x -> interp t ((n, x) : env))
interp (App t1 t2) env = case (interp t1 env, interp t2 env) of
     (Just (Fun f), Just x) -> f x
     (_, _) -> Nothing

test :: Term -> String
test t = showM $ interp t []

pgm1:: Term
pgm1 = App
          (Lam "x" ((Var "x") :+: (Var "x")))
          ((Con 10) :+:  (Con 11))
-- test pgm
-- test pgm1
