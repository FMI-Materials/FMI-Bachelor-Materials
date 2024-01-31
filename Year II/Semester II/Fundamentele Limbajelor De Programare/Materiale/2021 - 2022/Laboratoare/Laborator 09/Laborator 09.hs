-- Implementare a Lambda calculului fara alpha-echivalanta
-- În acest laborator vom defini lambda-termenii și beta-reducția, urmând definițiile de la curs. 

import Data.List ( nub )
import Data.Maybe ( isJust, fromJust )

type Variable = Char

data Term
  = V Variable
  | App Term Term
  | Lam Variable Term
  deriving (Show)




--  subst u x t   =  [u/x]t
subst :: Term -> Variable -> Term -> Term
subst u x (V y)
  | x == y    = undefined
  | otherwise = undefined
subst u x (App t1 t2) = undefined
subst u x (Lam y t)
  | x == y          = Lam y t
  | y `notElem` (freeVars u) = undefined
  | otherwise       = error "substitutia nu este posibila fara alpha-echivalanta"



freeVars :: Term -> [Variable]
freeVars (V var) = undefined
freeVars (App t1 t2) = undefined
freeVars (Lam var t) = undefined





-- Reducere la forma normala

normalReduceStep :: Term -> Maybe Term
normalReduceStep (App (Lam v t) t2) = Just $ subst t2 v t
normalReduceStep (App t1 t2) = undefined
normalReduceStep (Lam x t) = undefined
normalReduceStep _ = Nothing

normalReduce :: Term -> Term
normalReduce t
  | isJust t' =  normalReduce (fromJust t')
  | otherwise = t
       where 
         t' = normalReduceStep t

reduce :: Term -> Term
reduce = normalReduce

lt1 =  App (Lam 'x' (App (V 'x') (V 'y'))) (V 'z')
lt2 =  App (Lam 'x' (App (V 'x') (V 'y'))) (V 'x')
lt3 =  App (Lam 'x' (App (V 'x') (V 'y'))) (App (V 'x') (V 'z'))
lt4 =  App (Lam 'x' (Lam 'y' (App (V 'x') (V 'y')))) (App (V 'x') (V 'y'))
lt4ae = App (Lam 'x' (Lam 'z' (App (V 'x') (V 'z')))) (App (V 'x') (V 'y')) -- alpha-echivalent cu lt4

