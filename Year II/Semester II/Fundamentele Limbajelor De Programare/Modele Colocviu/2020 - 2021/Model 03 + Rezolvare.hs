{-
Finalizati definitia functiilor de interpretare.
Adaugati instructiunea While BExp Stmt si interpretarea ei.
-}
import Data.Maybe
import Data.List

type Name = String

data Pgm  = Pgm [Name] Stmt
        deriving (Read, Show)

data BExp = BTrue 
  | BFalse 
  | AExp :==: AExp 
  | Not BExp
  deriving (Read, Show)

data Stmt = Skip 
  | Stmt ::: Stmt 
  | If BExp Stmt Stmt
  | Name := AExp
  | While BExp Stmt
  deriving (Read, Show)

data AExp = Lit Integer 
  | AExp :+: AExp 
  | AExp :*: AExp 
  | Var Name
  deriving (Read, Show)

infixr 2 :::
infix 3 :=
infix 4 :==:
infixl 6 :+:
infixl 7 :*:


type Env = [(Name, Integer)] -- [(String, Integer)]

aEval :: AExp -> Env -> Integer
aEval (Lit n) _ = n
aEval (aexp1 :+: aexp2) env = (aEval aexp1 env) + (aEval aexp2 env)
aEval (aexp1 :*: aexp2) env = (aEval aexp1 env) * (aEval aexp2 env)
aEval (Var string) env = aux (lookup string env)
  where
    aux (Just n) = n 
    aux Nothing = error "Eroare lookup"

bEval :: BExp -> Env -> Bool
bEval BTrue env = True
bEval BFalse env = False
bEval (aexp1 :==: aexp2) env = (aEval aexp1 env) == (aEval aexp2 env)
bEval (Not bexp) env = not (bEval bexp env)

sEval :: Stmt -> Env -> Env
sEval Skip env = env
sEval (st1 ::: st2) env = (sEval st1 env) ++ (sEval st2 env)
sEval (If b st1 st2) env =  if (bEval b env) then (sEval st1 env) else (sEval st2 env) 
sEval (string := aexp) env = (string, aEval aexp env) : [(x, value) | (x, value) <- env, x /= string ]
sEval (While bexp st) env = if bEval bexp env then sEval (st ::: While bexp st) env else sEval Skip env


pEval :: Pgm -> Env
pEval (Pgm lvar st) = sEval st [(x,0) | x<- lvar] --  initializate memorie cu 0 


 
factStmt :: Stmt
factStmt =
  "p" := Lit 1 ::: "n" := Lit 3 :::
  While (Not (Var "n" :==: Lit 0))
    ( "p" := Var "p" :*: Var "n" :::
      "n" := Var "n" :+: Lit (-1)
    )
test2 = Pgm ["p", "n"] ("p" := Var "p" :*: Var "n" :::"n" := Var "n" :+: Lit (-1))
-- [("p",0),("n",0),("n",-1),("p",0)]

test1 = Pgm ["p", "n"] factStmt 
-- [("p",1),("n",0),("n",3),("p",0),("p",0),("n",0)] 

{-
Definiti interpretarea limbajului astfel incat programele sa se execute dintr-o stare 
initiala data, iar  pEval  sa afiseze starea initiala si starea finala.
Definiti teste pentru verificarea solutiilor si indicati raspunsurile primite. 
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

tell:: String -> StringWriter ()  
tell mesaj = StringWriter ((), mesaj)

showM :: Show a => M a -> String
showM (StringWriter (val, env))
    | null env  = "Stare finala: " ++ show val
    | otherwise = "Stare initiala: " ++ env ++ "Stare finala: " ++ show val

interAEval :: AExp -> Env -> M Integer
interAEval (Lit n) _ = return n
interAEval (aexp1 :+: aexp2) env = do
      x <- interAEval aexp1 env 
      y <- interAEval aexp2 env
      return (x+y)
interAEval (aexp1 :*: aexp2) env = do
      x <- interAEval aexp1 env
      y <- interAEval aexp2 env
      return (x*y)
interAEval (Var string) env = aux (lookup string env)
  where
    aux (Just n) = return n 
    aux Nothing = error "Eroare lookup"

interBEval :: BExp -> Env -> M Bool
interBEval BTrue env = return True
interBEval BFalse env = return False
interBEval (aexp1 :==: aexp2) env = do
      x <- interAEval aexp1 env
      y <- interAEval aexp2 env
      return (x==y)
interBEval (Not bexp) env = do
       x <- interBEval bexp env
       return ( not x)

interSEval :: Stmt -> Env -> M Env
interSEval Skip env = return env
interSEval (st1 ::: st2) env = do
      x <- interSEval st1 env
      y <- interSEval st2 env
      return (x++y)
interSEval (If b st1 st2) env =  do
      bool <- interBEval b env
      if bool then interSEval st1 env else interSEval st2 env 
interSEval (string := aexp) env = do
      aEv <- interAEval aexp env
      return ((string, aEv) : [(x, value) | (x, value) <- env, x /= string ])
interSEval (While bexp st) env = do
      bool <- interBEval bexp env 
      if bool then interSEval (st ::: While bexp st) env else interSEval Skip env


interPEval :: Pgm -> M Env
interPEval (Pgm lvar st) = do
      tell (show [(x,0) | x<- lvar] ++ "; ")
      interSEval st [(x,0) | x<- lvar] --  initializate memorie cu 0 

test :: Pgm -> String
test t = showM $ interPEval t

term0 = Pgm ["p", "n"] ("p" := Var "p" :*: Var "n" :::"n" := Var "n" :+: Lit (-1))
-- "Stare initiala: [(\"p\",0),(\"n\",0)]; Stare finala: [(\"p\",0),(\"n\",0),(\"n\",-1),(\"p\",0)]"
