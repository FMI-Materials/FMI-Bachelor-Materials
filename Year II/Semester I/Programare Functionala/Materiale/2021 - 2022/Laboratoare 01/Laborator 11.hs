import Data.Maybe

type Name = String

data  Value  =  VBool Bool
     |VInt Int
     |VFun (Value -> Value)
     |VError

data  Hask  = HTrue | HFalse
     |HIf Hask Hask Hask
     |HLit Int
     |Hask :==: Hask
     |Hask :+:  Hask
     |HVar Name
     |HLam Name Hask
     |Hask :$: Hask
     |Hask :*: Hask

infix 4 :==:
infixl 6 :+:
infixl 9 :$:
infixl 7 :*:

type  HEnv  =  [(Name, Value)]


instance Show Value where
     show (VBool x) = show x
     show (VInt x) = show x
     show VError = "eroare"
     show _ = "functie"



instance Eq Value where
     (VBool x) == (VBool y) = x == y
     (VInt x) == (VInt y) = x == y
     VFun x == _ = error "functiile nu se pot compara"
     _ == VFun x = error "functiile nu se pot compara"
     VError == _ = error "erorile nu se pot compara"
     _ == VError = error "erorile nu se pot compara"
     VBool x == _ = error "tipuri de date diferite"
     VInt x == _ = error "tipuri de date diferite"



hEval :: Hask -> HEnv -> Value
hEval HTrue r      =  VBool True
hEval HFalse r        =  VBool False
hEval (HIf c d e) r   = hif (hEval c r) (hEval d r) (hEval e r)
  where  hif (VBool b) v w  =  if b then v else w
         hif _ _ _ = VError
hEval (HLit x) r = VInt x
hEval ( x :==: y ) r = VBool (hEval x r == hEval y r)
hEval ( x :+: y ) r =
     case (hEval x r, hEval y r) of
          (VInt int1, VInt int2) -> VInt (int1 + int2)
          _ -> error "+ se face doar pe intregi"
hEval ( x :*: y ) r =
     case (hEval x r, hEval y r) of
          (VInt int1, VInt int2) -> VInt (int1 * int2)
          _ -> error "* se face doar pe intregi"
hEval ( HVar x ) r =
    if isNothing (lookup x r)
        then VError
        else v where Just v = lookup x r
hEval ( HLam x y) r = VFun (\val -> hEval y ((x, val) : r) )
hEval ( f :$: h ) r = 
     case hEval f r of
          VFun f' -> f' (hEval h r )
          _ -> VError

run :: Hask -> String
run pg = show (hEval pg [])

test :: Value
test = hEval (HLam "varA" (HLit 1 :+: HVar "varA") :$: HLit 5) []
pg1, pg2, pg3 :: Hask
pg1 =  (HLit 5 :+: HLit 2 :==: HLit 7) :==: HTrue
pg2 = HLam "varA" (HVar "varA" :+: HLit 5 :*: HLit 3) :$: HIf pg1 (HLit 0) (HLit 1)
pg3 = HFalse :+: HTrue