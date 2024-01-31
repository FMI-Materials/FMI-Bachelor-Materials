{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
----------- Ex 1
data Prog = On Instr
data Instr = Off | Expr :> Instr
data Expr = Mem | V Int | Expr :+ Expr
type Env = Int -- valoarea celulei de memorie
type DomProg = [Int]
type DomInstr = Env -> [Int]
type DomExpr = Env -> Int

-- On ((V 3) :> ((Mem :+ (V 5)) :> Off)) -> [3, 8]

prog :: Prog -> DomProg
prog (On i) = stmt i 0

stmt :: Instr -> DomInstr
stmt i = stmt' i
   where stmt' Off l = []
         stmt' (e :> i) l = let eval = expr e l in
                            eval : stmt' i eval

expr :: Expr -> DomExpr
expr = expr'
   where expr' Mem l = l
         expr' (V val) l = val
         expr' (e1 :+ e2) l = expr' e1 l + expr' e2 l


p1 = On ((V 3) :> ((Mem :+ (V 5)):> Off))

----------------- Ex 2

type Name = String
data Hask = HTrue
 | HFalse
 | HLit Int
 | HIf Hask Hask Hask
 | Hask :==: Hask
 | Hask :+: Hask
 | HVar Name
 | HLam Name Hask
 | Hask :$: Hask
  deriving (Read, Show)
infix 4 :==:
infixl 6 :+:
infixl 9 :$:


data Value = VBool Bool
 | VInt Int
 | VFun (Value -> Value)
 | VError -- pentru reprezentarea erorilor
type HEnv = [(Name, Value)]
type DomHask = HEnv -> Value

--- a
instance Show Value where
    show (VBool i) = show i
    show (VInt i) = show i
    show (VFun _) = "<function>"
    show VError = "<error>"

--- b 
instance Eq Value where
    (VInt a) == (VInt b) = a == b
    (VBool a) == (VBool b) = a == b
    _ == _ = error "Nu se pot compara"

--- c
isError :: Value -> Bool
isError VError = True
isError _ = False

hEval :: Hask -> DomHask
hEval HTrue _ = VBool True
hEval HFalse _ = VBool False
hEval (HLit x) _ = VInt x
hEval (HIf h1 h2 h3) env = checkIf' (hEval h1 env) h2 h3 env
    where checkIf' (VBool True) h2 h3 env = hEval h2 env
          checkIf' (VBool False) h2 h3 env = hEval h3 env
          checkIf' _ _ _ _ = VError

hEval (h1 :==: h2) env = let v1 = hEval h1 env in
                         let v2 = hEval h2 env in
                         if isError v1 || isError v2 then
                             VError
                         else
                             VBool (v1 == v2)
hEval (h1 :+: h2) env = let v1 = hEval h1 env in
                        let v2 = hEval h2 env in
                        case (v1, v2) of 
                            (VInt v1, VInt v2) -> VInt (v1 + v2)
                            (_, _) -> VError
hEval (HVar n) env = let rez = lookup n env in
                     case rez of
                         Nothing -> VError
                         Just exp -> exp
hEval (HLam n exp) env =
    VFun (\x ->
        let new_entry = (n, x)
            new_env =
                if lookup n env == Nothing then
                    new_entry : env
                else
                    map (\(name, val) ->
                        if name == n then
                            new_entry
                        else
                            (name, val)) env in
        hEval exp new_env)
hEval (a :$: b) env =
    let fun = hEval a env
        val = hEval b env in
    case fun of
        VError -> VError
        VFun f -> f val

lambdaExp :: Hask
lambdaExp = HLam "X" (HVar "X" :+: HVar "X") :$: HLit 10

main = undefined 

