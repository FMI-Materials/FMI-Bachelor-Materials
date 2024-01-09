data Expr = Const Int
          | Expr :+: Expr
          | Expr :*: Expr
          deriving Eq

data Operation = Add | Mult
               deriving (Eq, Show)

data Tree = Lf Int
          | Node Operation Tree Tree
          deriving (Eq, Show)

data IntSearchTree value = Empty
                         | BNode 
                            (IntSearchTree value)
                            Int 
                            (Maybe value)
                            (IntSearchTree value)
                         deriving (Eq, Show)


instance Show Expr where
    show (Const x) = show x
    show (e1 :+: e2) = "(" ++ show e1 ++ " + " ++ show e2 ++ ")"
    show (e1 :*: e2) = "(" ++ show e1 ++ " * " ++ show e2 ++ ")"

exp1 = ((Const 2 :*: Const 3) :+: (Const 0 :*: Const 5))
exp2 = (Const 2 :*: (Const 3 :+: Const 4))
exp3 = (Const 4 :+: (Const 3 :*: Const 3))
exp4 = (((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2)

arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)

myTree = BNode (BNode Empty 1 (Just "one") Empty) 2 (Just "two") (BNode Empty 3 (Just "three") Empty)

-- 1
evalExpr :: Expr -> Int
evalExpr (Const x) = x
evalExpr (e1 :+: e2) = evalExpr e1 + evalExpr e2
evalExpr (e1 :*: e2) = evalExpr e1 * evalExpr e2

-- 2
evalArb :: Tree -> Int
evalArb (Lf x) = x
evalArb (Node Add x y) = evalArb x + evalArb y
evalArb (Node Mult x y) = evalArb x * evalArb y

-- 3
expToArb :: Expr -> Tree
expToArb (Const x) = Lf x
expToArb (el :+: e2) = Node Add (expToArb el) (expToArb e2)
expToArb (el :*: e2) = Node Mult (expToArb el) (expToArb e2)

-- 4
lookup' :: Int -> IntSearchTree value -> Maybe value
lookup' _ Empty = Nothing
lookup' x (BNode left key value right)
    | x == key = value
    | x < key = lookup' x left
    | otherwise = lookup' x right

-- 5
keys :: IntSearchTree value -> [Int]
keys Empty = []
keys (BNode left key Nothing right) = keys left ++ keys right
keys (BNode left key value right) = keys left ++ [key] ++ keys right

-- 6
values :: IntSearchTree value -> [value]
values Empty = []
values (BNode left key Nothing right) = values left ++ values right
values (BNode left key value right) = values left ++ [val] ++ values right
    where Just val = value

-- 7
insert :: Int -> value -> IntSearchTree value -> IntSearchTree value
insert x val Empty = BNode Empty x (Just val) Empty
insert x val (BNode left key value right)
    | x == key = BNode left key (Just val) right
    | x < key = BNode (insert x val left) key value right
    | otherwise = BNode left key value (insert x val right)

-- 8
delete :: Int -> IntSearchTree value -> IntSearchTree value
delete x Empty = Empty
delete x (BNode left key value right)
    | x == key = BNode left key Nothing right
    | x < key = BNode (delete x left) key value right
    | otherwise = BNode left key value (delete x right)

-- 9
toList :: IntSearchTree value -> [(Int, value)]
toList Empty = []
toList (BNode left key Nothing right) = toList left ++ toList right
toList (BNode left key value right) = toList left ++ [(key, val)] ++ toList right
    where Just val = value

-- 10
fromList :: [(Int, value)] -> IntSearchTree value
fromList [] = Empty
fromList ((key, val):xs) = insert key val (fromList xs)

-- 11
printTree :: IntSearchTree value -> String
printTree Empty = ""
printTree (BNode left key Nothing right) = printTree left ++ printTree right
printTree (BNode left key (Just val) right) = "(" ++ printTree left ++ show key ++ printTree right ++ ")"