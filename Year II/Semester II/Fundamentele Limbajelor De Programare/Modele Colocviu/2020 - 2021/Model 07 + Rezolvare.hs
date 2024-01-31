{-
Finalizati definitia functiilor de interpretare.
Adaugati expresia `If e e1 e2` care se evaluează `e1` daca `e` are valoarea `0` si la `e2` in caz contrar.
-}
data Prog  = On [Stmt] 

data Stmt =
     Save Expr     -- evalueaza expresia și salvează rezultatul in Mem
   | NoSave Expr   -- evalueaza expresia, fără a modifica Mem 

data Expr  =  Mem 
      | V Int 
      | Expr :+ Expr 
      | If Expr Expr Expr

infixl 6 :+

type Env = Int   -- valoarea curentă a celulei de memorie

expr ::  Expr -> Env -> Int
expr (e1 :+  e2) m = expr e1 m + expr e2 m
expr (V n) m = n 
expr Mem m = m
expr (If e e1 e2) m = if expr e m == 0 then expr e1 m else expr e2 m 

stmt :: Stmt -> Env -> Env
stmt (Save exp) m = expr exp m  
stmt (NoSave exp) m = m

stmts :: [Stmt] -> Env -> Env
stmts [x] m = stmt x m
stmts (h:t) m = stmts t m 

prog :: Prog -> Env
prog (On ss) = stmts ss 0

test1 = On [Save (V 3), NoSave (Mem :+ (V 5))] -- 3
test2 = On [NoSave (V 3 :+  V 3)] --0
test3 = On [Save (V 3)] -- 3
test4 = On [Save (If ((V 6) :+ (V 5)) ((V 1) :+ (V 2)) ((V 3) :+ (V 4)))] -- 7
test5 = On [Save (V 3 :+  V 3), Save (V 1 :+ V 2)] -- 3
{-
Definiti interpretarea  limbajului extins modificand functiile de interpretare astfel incat 
executia unui program sa intoarca starea memoriei si lista valorilor calculate.
-}
newtype StringWriter a = StringWriter { runStringWriter :: (a, String) }

instance  Monad StringWriter where
  return va = StringWriter (va, "")
  ma >>= k = let (va, log1) = runStringWriter ma
                 (vb, log2) = runStringWriter (k va)
             in  StringWriter (vb, log1 ++ log2)


instance  Applicative StringWriter where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance  Functor StringWriter where              
  fmap f ma = pure f <*> ma 

--- Limbajul si  Interpretorul

type M = StringWriter 

showM :: Show a => M a -> String
showM (StringWriter (val, env))
    | null env  = "Stare memorie: " ++ show val
    | otherwise = "Valori calculate: " ++ env ++ "Stare memorie: " ++ show val

tell:: String -> StringWriter ()  -- functie auxiliara
tell mesaj = StringWriter ((), mesaj)

interExpr ::  Expr -> Env -> M Int
interExpr (e1 :+  e2) m = do
      x <- interExpr e1 m 
      y <- interExpr e2 m
      return (x+y)
interExpr (V n) m = return n 
interExpr Mem m = return m
interExpr (If e e1 e2) m = do
      x <- interExpr e m
      if x == 0 then interExpr e1 m else interExpr e2 m 


interStmt :: Stmt -> Env -> M Env
interStmt (Save exp) m = do
      x <- interExpr exp m 
      tell (show x ++ "; ") 
      return x
interStmt (NoSave exp) m = do
      x <- interExpr exp m 
      tell (show x ++ "; ") 
      return m

interStmts :: [Stmt] -> Env -> M Env
interStmts [x] m = interStmt x m
interStmts (h:t) m = do
      x <- interStmt h m
      interStmts t x


interProg :: Prog -> M Env
interProg (On ss) = interStmts ss 0


test :: Prog -> String
test t = showM $ interProg t 

term0 = On [Save (V 3), NoSave (Mem :+ (V 5))] -- "Valori calculate: 3; 8; Stare memorie: 3"
term1 = On [Save (V 3 :+  V 3), Save (V 1 :+ V 2)] -- "Valori calculate: 6; 3; Stare memorie: 3"
term2 = On [Save (V 3 :+  V 3)] -- "Valori calculate: 6; Stare memorie: 6"
