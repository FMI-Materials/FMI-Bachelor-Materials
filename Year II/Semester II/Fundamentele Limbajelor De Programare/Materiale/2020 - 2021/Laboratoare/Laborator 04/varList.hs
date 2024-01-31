--- Monada M

-- newtype M a = M { runM :: a }

type M a = [a]
--- Limbajul si  Interpretorul

showM :: Show a => M a -> String
showM = show

type Name = String

data Term = Var Name
          | Con Integer
          | Term :+: Term
          | Lam Name Term
          | App Term Term
          | Fail
          | Amb Term Term
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
interp (Var n) env = case lookup n env of
  (Just x) -> return x
  _ -> []
interp (Con x) _ = return (Num x)
interp (t1 :+: t2) env = do
     v1 <- interp t1 env
     v2 <- interp t2 env
     case (v1, v2) of
       (Num x, Num y) -> return (Num (x + y))
       (_, _) -> []
interp (Lam n t) env = return $ Fun (\x -> interp t ((n, x) : env))
interp (App t1 t2) env = do
     intf <- interp t1 env
     intv <- interp t2 env
     case intf of
       Fun f -> f intv
       _ -> []
interp Fail _ = []
interp (Amb a b) env = do
  v1 <- interp a env
  v2 <- interp b env
  v1 : [v2]


test :: Term -> String
test t = showM $ interp t []

pgm1:: Term
pgm1 = App
          (Lam "x" (Var "x" :+: Var "x"))
          (Con 10 :+:  Con 11)
pgm2 :: Term
pgm2 = App (Lam "x" (Var "x" :+: Var "x")) (Amb (Con 1) (Con 2))
-- test pgm
-- test pgm1
