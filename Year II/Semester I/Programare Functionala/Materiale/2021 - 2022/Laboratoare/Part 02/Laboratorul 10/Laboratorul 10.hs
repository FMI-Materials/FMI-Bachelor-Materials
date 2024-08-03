-- EXPRESII SI ARBORI

data Expr = Const Int -- integer constant
    | Expr :+: Expr -- addition
    | Expr :*: Expr -- multiplication
    deriving Eq

-- 1.1 sa se instantieze clasa Show pentru tipul Expr

instance Show Expr where
    show (Const n) = show n
    show (e1 :+: e2) = "(" ++ show e1 ++ "+" ++ show e1 ++ ")"
    show (e1 :*: e2) = "(" ++ show e1 ++ "*" ++ show e1 ++ ")"

-- 1.2 sa se scrie o functie care evalueaza o
-- expresie calculand valoarea acesteia

evalExpr :: Expr -> Int
evalExpr (Const n) = n
evalExpr (e1 :+: e2) = evalExpr e1 + evalExpr e2
evalExpr (e1 :*: e2) = evalExpr e1 * evalExpr e2

exp1 = (Const 2 :*: Const 3) :+: (Const 0 :*: Const 5)
exp2 = Const 2 :*: (Const 3 :+: Const 4)
exp3 = Const 4 :+: (Const 3 :*: Const 3)
exp4 = ((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2

---

data Operation = Add | Mult
    deriving (Eq, Show)

data Tree = Lf Int -- leaf
    | Node Operation Tree Tree -- branch
    deriving (Eq, Show)

-- 1.3 sa se scrie o functie ce evalueaza
-- un arbore afland valoarea acestuia

evalArb :: Tree -> Int
evalArb (Lf n) = n
evalArb (Node Add t1 t2) = evalArb t1 + evalArb t2
evalArb (Node Mult t1 t2) = evalArb t1 * evalArb t2

-- 1.4 functie care transforma o expresie in arbore

expToArb :: Expr -> Tree
expToArb (Const n) = Lf n
expToArb (e1 :+: e2) = Node Add (expToArb e1) (expToArb e2)
expToArb (e1 :*: e2) = Node Mult (expToArb e1) (expToArb e2)

arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)