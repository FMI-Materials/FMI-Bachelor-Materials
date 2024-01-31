--- Define data
import Data.Maybe
import Data.List

type Name = String
data  Pgm  = Pgm [Name] Stmt
        deriving (Read, Show)
data Stmt = Skip | Stmt ::: Stmt | If BExp Stmt Stmt | While BExp Stmt | Name := AExp | Break
        deriving (Read, Show)
data AExp = Lit Integer | AExp :+: AExp | AExp :*: AExp | Var Name | Inc Name | Dec Name
        deriving (Read, Show)
data BExp = BTrue | BFalse | AExp :==: AExp | Not BExp
        deriving (Read, Show)

infixr 2 :::
infix 3 :=
infix 4 :==:
infixl 6 :+:
infixl 7 :*:


type Env = [(Name, Integer)]

--- Testing
factStmt :: Stmt
factStmt =
  "p" := Lit 1 ::: "n" := Lit 3 :::
  While (Not (Var "n" :==: Lit 0))
    ( "p" := Var "p" :*: Var "n" :::
      "n" := Var "n" :+: Lit (-1)
    )
pg1 = Pgm [] factStmt


--- Implementation
pEval :: Pgm -> Env
pEval (Pgm vars stmt) = let env = [(n, 0) | n <- vars] in
      sEval stmt env

updateEnv :: Name -> Integer -> Env -> Env
updateEnv name val [] = [(name, val)]
updateEnv name val (h:t)
   | fst h == name = (name, val):t
   | otherwise = updateEnv name val t ++ [h]

sEval :: Stmt -> Env -> Env
sEval Skip env = env
sEval (s1 ::: s2) env = let env1 = sEval s1 env in
                        sEval s2 env1
sEval (If exp s1 s2) env = if bEval exp env 
                           then sEval s1 env 
                           else sEval s2 env
sEval (While exp s) env = if bEval exp env
                          then let env2 = sEval s env in
                            sEval (While exp s) env2
                          else
                            env
sEval (n := exp) env = let val = aEval exp env in
                       updateEnv n val env
sEval _ env = env

bEval :: BExp -> Env -> Bool
bEval BTrue _ = True 
bEval BFalse _ = False 
bEval (exp1 :==: exp2) env = do
    let v1 :: Integer
        v1 = aEval exp1 env
        v2 :: Integer
        v2 = aEval exp2 env in
        v1 == v2
bEval (Not exp) env = let v = bEval exp env in
    not v

aEval :: AExp -> Env -> Integer
aEval (Lit n) _ = n
aEval (exp1 :+: exp2) env = 
    let v1 :: Integer
        v1 = aEval exp1 env 
        v2 :: Integer
        v2 = aEval exp2 env in
    v1 + v2
aEval (exp1 :*: exp2) env = 
    let v1 :: Integer
        v1 = aEval exp1 env 
        v2 :: Integer
        v2 = aEval exp2 env in
    v1 * v2
aEval (Var n) env =  case lookup n env of
    Nothing -> 0
    (Just x) -> x
aEval _ _ = 0


