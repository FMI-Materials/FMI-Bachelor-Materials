{-
Gasiti mai jos limbajul unui minicalculator si o interpretare partiala.
Calculatorul are o celulă de memorie, care are valoarea initiala  0.

Un program este o expresie de tip `Prog`iar rezultatul executiei este lista valorilor calculate.
Testare se face apeland `prog test`.
Finalizati definitia functiilor de interpretare.
Adaugati expresia `If e1 e2` care se evaluează `e1` daca `Mem` are valoarea `0` si la `e2` in caz contrar.
-}
data Prog = On Stmt
 
data Stmt
  = Off
  | Save Expr Stmt -- evalueaza expresia și salvează rezultatul in Mem, apoi evalueaza Stmt
  | NoSave Expr Stmt -- evalueaza expresia, fără a modifica Mem, apoi evaluează Stmt
 
data Expr = Mem 
  | V Int 
  | Expr :+ Expr 
  | Expr :* Expr 
  | If Expr Expr
 
infixl 6 :+
infixl 7 :*

type Env = Int -- valoarea curentă a celulei de memorie
 
expr :: Expr -> Env -> Int 
expr Mem env = env
expr (V n) env = n 
expr (exp1 :+ exp2) env = (expr exp1 env) + (expr exp2 env)
expr (exp1 :* exp2) env = (expr exp1 env) * (expr exp2 env)
expr (If exp1 exp2) env = if env ==0 then expr exp1 env else expr exp2 env

stmt :: Stmt -> Env -> [Int]
stmt Off env = [env]
stmt (Save exp st) env = let mem_noua = expr exp env in stmt st mem_noua
stmt (NoSave exp st) env = let mem_noua = expr exp env in stmt st env
 
prog :: Prog -> [Int]
prog (On s) = stmt s 0

test1 = On (Save (V 3) (NoSave (Mem :+ V 5) Off)) --[3]
test2 = On (NoSave (V 3 :+ V 3) Off) --[0]
test3 = On (Save (If (V 1) (V 2)) Off) -- [1]
test4 = On (Save (V 3 :+ V 3) Off) --[6]
 
{-
Definiti interpretarea  limbajului extins astfel incat executia unui program sa calculează valoarea finala,
numarul de adunari si numarul de inmultiri efectuate. 
-}

--- Monada State
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

get :: InState Integer -- NOU
get = State ( \s -> (s,s)) 
-- functie asemanatoare cu ask
-- folosit la numararea operatiilor prin Count ca altfel ramane 0

modify :: (Integer -> Integer) -> InState () -- NOU
modify f = State (\s -> ((), f s)) -- primeste o stare si schimba starea prin aplicarea lui f

--- Limbajul si  Interpretorul

type M = InState

interExpr :: Expr -> Env -> M Int 
interExpr Mem env = return env
interExpr (V n) env = return n 
interExpr (exp1 :+ exp2) env = do
   modify(+1) 
   x <- interExpr exp1 env 
   y <- interExpr exp2 env
   return (x+y)
interExpr (exp1 :* exp2) env =  do
   modify(+1) 
   x <- interExpr exp1 env 
   y <- interExpr exp2 env
   return (x*y)
interExpr (If exp1 exp2) env = if env ==0 then interExpr exp1 env else interExpr exp2 env

interStmt :: Stmt -> Env -> M [Int]
interStmt Off env = return [env]
interStmt (Save exp st) env = do
   mem_noua <- interExpr exp env 
   interStmt st mem_noua
interStmt (NoSave exp st) env = let
   mem_noua = interExpr exp env 
   in interStmt st env

interProg :: Prog -> M [Int]
interProg (On s) = interStmt s 0

showM :: Show a => M a -> String 
showM ma = let (va, s)=(runState ma 0 ) in ("Valoare finala: " ++ (show va) ++" Inmultiri si adunari efectuate: " ++ (show s))

test :: Prog -> String
test t = showM $ interProg t 

term0 =  On (Save (V 3 :+ V 3) Off)
-- test term0 => "Valoare finala: [6] Inmultiri si adunari efectuate: 1"
