{- 
Calculatorul are doua celule de memorie, care au valoarea initiala 0. 
Expresia `Mem := Expr` are urmatoarea semantica: 
`Expr` este evaluata, iar valoarea este pusa in `Mem`.  
Un program este o expresie de tip `Prog` iar rezultatul executiei este dat de valorile finale ale celulelor de memorie.
Testare se face apeland `run test`.
------- Ex 1 si 2 ------------ 
- Finalizati definitia functiilor de interpretare.
- Adaugati expresia `e1 :/ e2` care evaluează expresiile e1 și e2, apoi
  - dacă valoarea lui e2 e diferită de 0, se evaluează la câtul împărțirii lui e1 la e2;
  - în caz contrar va afișa eroarea "împarțire la 0" și va încheia execuția.
-}

data Prog  = Stmt ::: Prog 
  | Off

data Stmt  = Mem := Expr

data Expr  =  M Mem 
  | V Int 
  | Expr :+ Expr
  | Expr :/ Expr

data Mem = Mem1 | Mem2 

infixl 6 :+
infix 3 :=
infixr 2 :::

type Env = (Int,Int)   -- corespunzator celor doua celule de memorie (Mem1, Mem2)

expr ::  Expr -> Env -> Int
expr (M Mem1) (m1, m2) = m1
expr (M Mem2) (m1, m2) = m2
expr (V n) m = n 
expr (e1 :+  e2) m = (expr e1 m) + (expr e2 m)
expr (e1 :/  e2) m = let ex1 = expr e1 m 
                         ex2 = expr e2 m
                     in if ex2 /= 0 
                          then ex1 `div` ex2  
                            else error "impartire la 0"

stmt :: Stmt -> Env -> Env
stmt (Mem1 := exp) (m1,m2) = let eval = expr exp (m1, m2) in (eval, m2)
stmt (Mem2 := exp) (m1,m2) = let eval = expr exp (m1, m2) in (m1, eval)

prog :: Prog -> Env -> Env
prog Off m = m
prog (st ::: p) m = prog p (stmt st m)

run :: Prog -> Env
run p = prog p (0, 0)

test1 = Mem1 := V 3 ::: Mem2 := M Mem1 :+ V 5 ::: Off --(3,8)
test2 = Mem2 := V 3 ::: Mem1 := V 4 ::: Mem2 := (M Mem1 :+ M Mem2) :+ V 5 ::: Off --(4,12)
test3 = Mem1 := V 3 :+  V 3 ::: Off --(6,0)
test4 = Mem1 := V 3 :/  V 0 ::: Off --0 "impartire la 0"

{-
Definiti interpretarea  limbajului extins astfel incat executia unui program fara erori sa intoarca valoarea finala si un mesaj
   care retine toate modificarile celulelor de memorie (pentru fiecare instructiune `m := v` se adauga 
   mesajul final `Celula m a fost modificata cu valoarea v`), mesajele pastrand ordine de efectuare a instructiunilor.  
-}
newtype StringWriter a = StringWriter { runStringWriter :: (a, String) }

instance  Monad StringWriter where
  return va = StringWriter ( va, "")
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

tell:: String -> StringWriter ()  -- NOU: afiseaza valoarea data ca argument
tell mesaj = StringWriter ((), mesaj)

interExpr ::  Expr -> Env -> M Int
interExpr (M Mem1) (m1, m2) = return m1
interExpr (M Mem2) (m1, m2) = return m2
interExpr (V n) m = return n 
interExpr (e1 :+  e2) m =do
  x <- interExpr e1 m 
  y <- interExpr e2 m
  return (x+y)
interExpr (e1 :/  e2) m = do
   ex1 <- interExpr e1 m 
   ex2 <- interExpr e2 m
   if ex2 /= 0 
      then return (ex1 `div` ex2) 
        else error "impartire la 0"

interStmt :: Stmt -> Env -> M Env
interStmt (Mem1 := exp) (m1,m2) = do
  eval <- interExpr exp (m1, m2) 
  tell ("Celula 1 a fost moddificata cu valoarea"++ show eval ++ ";") 
  return (eval, m2)
interStmt (Mem2 := exp) (m1,m2) = do
   eval <- interExpr exp (m1, m2) 
   tell ("Celula 2 a fost moddificata cu valoarea"++ show eval ++ "; ")
   return (m1, eval)

interProg :: Prog -> Env -> M Env
interProg Off m = return m
interProg (st ::: p) m = do
  eval <- interStmt st m
  interProg p eval

interRun :: Prog -> M Env
interRun p = interProg p (0, 0)

showM :: Show a => M a -> String
showM (StringWriter (val, env))
    | null env  = "Valoare finala: " ++ show val
    | otherwise = "" ++ env ++ "Valoare finala: " ++ show val

test :: Prog -> String
test t = showM $ interRun t

term0 :: Prog
term0 = (Mem1 := V 3 ::: Mem2 := M Mem1 :+ V 5 ::: Off)
-- test term0 => "Celula 1 a fost moddificata cu valoarea3; Celula 2 a fost moddificata cu valoarea8; Valoare finala: (3,8)"
