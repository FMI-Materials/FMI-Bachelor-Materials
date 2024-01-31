{-
----- Ex 1 si 2 ---------
- finalizati definitia functiilor de interpretare.
- adaugati expresiile `If1 e1 e2` si `If2 e1 e2`  care evaluează  `e1` daca `Mem1`, 
respectiv `Mem2`, este nenula si`e2` in caz contrar.
-}

type Env = (Int,Int)   -- corespunzator celor doua celule de memorie

data Prog  = On Env Stmt  -- Env reprezinta valorile initiale ale celulelor de memorie 

data Stmt
    = Off
    | Expr :<< Stmt -- evalueaza Expr, pune rezultatul in Mem1, apoi executa Stmt
    | Expr :< Stmt  -- evalueaza Expr, pune rezultatul in Mem2, apoi executa Stmt

data Mem = Mem1 | Mem2 

data Expr  =  M Mem 
  | V Int 
  | Expr :+ Expr 
  | If1 Expr Expr 
  | If2 Expr Expr

infixl 6 :+
infixr 2 :<
infixr 2 :<<

expr ::  Expr -> Env -> Int -- Expr -> (Int, Int) -> Int
expr (M Mem1) (e1,e2) = e1
expr (M Mem2) (e1,e2) = e2
expr (V n) env = n
expr (exp1 :+ exp2) env = (expr exp1 env) + (expr exp2 env)

expr (If1 exp1 exp2) (e1, e2) = if e1 /= 0 then expr exp1 (e1, e2) else expr exp2 (e1, e2)
expr (If2 exp1 exp2) (e1, e2) = if e2 /= 0 then expr exp2 (e1, e2) else expr exp1 (e1, e2)


stmt :: Stmt -> Env -> Env
stmt Off env = env
stmt (exp :<< st) (e1, e2) = let 
                                valExp = expr exp (e1,e2)
                                envNou = (valExp, e2) 
                              in
                                stmt st envNou
stmt (exp :< st) (e1, e2) = let 
                                valExp = expr exp (e1,e2)
                                envNou = (e1, valExp) 
                            in
                                stmt st envNou

prog :: Prog -> Env
prog (On env st) = stmt st env 

test1 = On (1,2) (V 3 :< M Mem1 :+ V 5 :<< Off) -- (6,3)
test2 = On (0,0) (V 3 :< Off) -- (0,3)
test3 = On (0,0) (V 3 :<< Off) --(3,0)
test4 = On (0,1) (V 3 :<< V 4 :< M Mem1 :+ M Mem2 :+ (V 5) :< Off) --(3,12)

{-
 Definiti interpretarea  limbajului extins  astfel incat executia unui program  sa calculeze memoria finala,
  si numărul de accesări (scrieri și citiri) ale memoriilor `Mem1` si `Mem2` (se va calcula o singura
  valoare, insumand accesarile ambelor memorii, fara a lua in considerare initializarea). 
   
-}
newtype InState  a = State {runState :: Integer -> (a, Integer)}

instance Monad InState where
  return va = State ( \s -> (va,s))
  ma >>= k = State g
              where
                g s = let (va, news)=(runState ma s ) in (runState (k va) news) 

instance Applicative InState where
  pure = return
  mf <*> ma = do
              f <-mf
              a <-ma
              return (f a)

instance Functor InState where
  fmap f ma = pure f <*> ma

get :: InState Integer 
get = State ( \s -> (s,s)) 


-- NU trebuie sa adaug vreun constructor Count
modify :: (Integer -> Integer) -> InState () 
modify f = State (\s -> ((), f s)) 

--- Limbajul si  Interpretorul

type M = InState

showM :: Show a => M a -> String
showM ma = let (va, s)=(runState ma 0 ) in ("Memorie finala:" ++ (show va) ++" Nr accesari:" ++ (show s))

interExpr ::  Expr -> Env -> M Int -- Expr -> (Int, Int) -> M Int
interExpr (M Mem1) (e1,e2) = modify (+1) >> return e1
interExpr (M Mem2) (e1,e2) = modify (+1) >> return e2
interExpr (V n) env = return n
interExpr (exp1 :+ exp2) env = do
  x <- interExpr exp1 env 
  y <- interExpr exp2 env
  return (x+y)
interExpr (If1 exp1 exp2) (e1, e2) = modify (+1) >> if e1 /= 0 then interExpr exp1 (e1, e2) else interExpr exp2 (e1, e2)
interExpr (If2 exp1 exp2) (e1, e2) = modify (+1) >> if e2 /= 0 then interExpr exp2 (e1, e2) else interExpr exp1 (e1, e2)

interStmt :: Stmt -> Env -> M Env -- Stmt -> (Int, Int) -> M (Int, Int)
interStmt Off env = return env
interStmt (exp :<< st) (e1, e2) = do 
                                valExp <- interExpr exp (e1,e2)
                                modify (+1)
                                interStmt st (valExp, e2)
interStmt (exp :< st) (e1, e2) = do 
                                valExp <- interExpr exp (e1,e2)
                                modify (+1) 
                                interStmt st (e1, valExp)
interProg :: Prog -> M Env
interProg (On env st) = interStmt st env 

test :: Prog -> String
test t = showM $ interProg t --scot environmentul de aici

term0 :: Prog
term0 = On (1,2) (V 3 :< M Mem1 :+ V 5 :<< Off)
-- test term0 => "Memorie finala:(6,3) Nr accesari:3"
