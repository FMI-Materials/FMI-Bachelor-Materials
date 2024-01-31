{-
Gasiti mai jos limbajul unui minicalculator si o interpretare partiala. 
Calculatorul are o celulă de memorie, care are valoarea initiala  0.
Interpretarea instructiunilor este data mai jos.

Un program este o expresie de tip `Prog`iar rezultatul executiei este starea finala a memoriei. 
Testare se face apeland `prog test`. 
-}

data Prog  = On [Stmt]
data Stmt =
     Save Expr     -- evalueaza expresia și salvează rezultatul in Mem
   | NoSave Expr   -- evalueaza expresia, fără a modifica Mem 
data Expr =  Mem
   | V Int
   | Expr :+ Expr
   | If Expr Expr Expr

infixl 6 :+

type Env = Int   -- valoarea curentă a celulei de memorie

expr ::  Expr -> Env -> Int
expr Mem env = env
expr (V x) _ = x
expr (e1 :+ e2) env = let v1 = expr e1 env in
                      let v2 = expr e2 env in
                        v1 + v2
expr (If cond e1 e2) env =
  let v1 = expr cond env in
  let v2 = expr e1 env in
  let v3 = expr e2 env in
  if v1 == 0 then
    v3
  else
    v2

stmt :: Stmt -> Env -> Env
stmt (Save e) env = let env1 = expr e env in
                    env1
stmt (NoSave e) env = let _ = expr e env in
                    env

stmts :: [Stmt] -> Env -> Env
stmts si env = foldl (flip stmt) env si

prog :: Prog -> Env
prog (On ss) = stmts ss 0


test1 :: Prog
test1 = On [Save (V 3), NoSave (Mem :+ (V 5))]
test2 :: Prog
test2 = On [NoSave (V 3 :+ V 3)]

-- Teste pentru cerinta 1
test3 :: Prog
test3 = On [Save (V 3), Save (V 4)]
test4 :: Prog
test4 = On [NoSave (V 3), NoSave (Mem :+ V 5)]

-- Teste pentru cerinta 2
test5 :: Prog
test5 = On [Save (If (V 0) (V 1) (V 2))]
test6 :: Prog
test6 = On [Save (If (V 1) (V 1) (V 2)), NoSave (V 5)]


{-CERINTE

1) (10pct) Finalizati definitia functiilor de interpretare.
2) (10 pct) Adaugati expresia `If e e1 e2` care se evaluează `e1` daca `e` are valoarea `0` si la `e2` in caz contrar.
3) (20pct)Definiti interpretarea  limbajului extins modificand functiile de interpretare astfel incat executia unui program
 sa intoarca starea memoriei si  lista valorilor calculate. 
Rezolvați subiectul 3) în același fișier redenumind funcțiile de interpretare.     


Indicati testele pe care le-ati folosit in verificarea solutiilor. 

-}

-- Ex 3
newtype StringWriter a = StringWriter {runStringWriter :: (a, [Int])}

instance Show a => Show (StringWriter a) where
  show sw = let (a, b) = runStringWriter sw in
    "Calculate: " ++ show b ++ " Value: " ++ show a

instance Monad StringWriter where
  return x = StringWriter (x, [])
  sw >>= f = let (a, b) = runStringWriter sw in
             let (StringWriter (a1, b1)) = f a in
               StringWriter (a1, b1)

instance Applicative StringWriter where
  pure = return
  a <*> b = do
    f <- a
    f <$> b

instance Functor StringWriter where
  fmap f a = f <$> a

type EnvS = StringWriter Int

exprS ::  Expr -> EnvS -> EnvS
exprS Mem env = env
exprS (V x) _ = return x

exprS (e1 :+ e2) env = do
     v1 <- exprS e1 env
     v2 <- exprS e2 env
     return $ v1 + v2
exprS (If cond e1 e2) env = do
     v1 <- exprS cond env
     v2 <- exprS e1 env
     v3 <- exprS e2 env
     if v1 == 0 then
       return v3
     else
       return v2

stmtS :: Stmt -> EnvS -> EnvS
stmtS (Save e) env = do
     env2 <- exprS e env
     let (env1, vals) = runStringWriter env in
       StringWriter (env2, env2 : vals)
stmtS (NoSave e) env = do
     env2 <- exprS e env
     let (env1, vals) = runStringWriter env in
       StringWriter (env1, env2 : vals)

stmtsS :: [Stmt] -> EnvS -> EnvS
stmtsS si env = foldl (flip stmtS) env si

progS :: Prog -> EnvS
progS (On ss) = stmtsS ss (return 0)


