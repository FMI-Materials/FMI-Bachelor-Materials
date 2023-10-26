
data Expr = Const Int -- integer constant
          | Expr :+: Expr -- addition
          | Expr :*: Expr -- multiplication
           deriving (Eq)

data Operation = Add | Mult deriving (Eq, Show)

data Tree = Lf Int -- leaf
          | Node Operation Tree Tree -- branch
           deriving (Eq, Show)


par :: Expr -> String 
par (Const x) = showE (Const  x)
par e = "(" ++ showE e ++ ")"

showE :: Expr -> String 
showE (Const  x) = show  x
showE (e1 :+: e2) = par e1 ++ " + " ++ par e2
showE (e1 :*: e2) = par e1 ++ " * " ++ par e2

instance Show Expr where
    show = showE

evalExp :: Expr -> Int
evalExp (Const x) = x
evalExp (e1 :+: e2) = (evalExp e1) + (evalExp e2)
evalExp (e1 :*: e2) = (evalExp e1) * (evalExp e2)

exp1 = ((Const 2 :*: Const 3) :+: (Const 0 :*: Const 5))
exp2 = (Const 2 :*: (Const 3 :+: Const 4))
exp3 = (Const 4 :+: (Const 3 :*: Const 3))
exp4 = (((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2)
test11 = evalExp exp1 == 6
test12 = evalExp exp2 == 14
test13 = evalExp exp3 == 13
test14 = evalExp exp4 == 16

evalArb :: Tree -> Int
evalArb (Lf x) = x
evalArb (Node Add t1 t2) =  evalArb t1 + evalArb t2
evalArb (Node Mult t1 t2) =  evalArb t1 * evalArb t2

expToArb :: Expr -> Tree
expToArb (Const x) = Lf x 
expToArb (e1 :+: e2) = Node Add (expToArb e1) (expToArb e2)
expToArb (e1 :*: e2) = Node Mult (expToArb e1) (expToArb e2)

arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)

test21 = evalArb arb1 == 6
test22 = evalArb arb2 == 14
test23 = evalArb arb3 == 13
test24 = evalArb arb4 == 16

class Collection c where
    empty :: c key value
    singleton :: key -> value -> c key value
    insert:: Ord key => key -> value -> c key value -> c key value
    clookup:: Ord key => key -> c key value -> Maybe value
    delete :: Ord key => key -> c key value -> c key value
    keys :: c key value -> [key]
    keys collection = [fst x | x<- toList collection]
    values :: c key value -> [value]
    values collection = [snd x | x<- toList collection] 
    toList :: c key value -> [(key, value)]
    fromList :: Ord key => [(key, value)] -> c key value
    fromList = foldr (uncurry insert) empty

newtype PairList k v
  = PairList { getPairList :: [(k, v)] }
  deriving Show

instance Collection PairList where
    empty = PairList []
    singleton a b = PairList [(a, b)]
    insert a b (PairList []) = PairList [(a, b)]
    insert a b (PairList ((k, v) : xs)) 
      | a < k = PairList ((a, b) : (k, v) : xs)
      | a == k = PairList( (a, b) : xs)
      | a > k = let PairList lista = insert a b (PairList xs) in PairList ((k, v) : lista)
    clookup a b = find a (getPairList b)
      where
          find _ [] = Nothing 
          find a (x : xs) =
              if fst x == a 
                  then Just (snd x)
                else
                    find a xs
    delete a (PairList []) = empty 
    delete a (PairList ((k, v) : xs)) 
            | k == a = delete a (PairList xs)
            | otherwise = let PairList lista = delete a (PairList xs) in PairList ((k, v) : lista)
    toList = getPairList
test = PairList {getPairList = [('a',5),('c',5),('b', 7)]}

data SearchTree key value
  = Empty
  | BNode
      (SearchTree key value) -- elemente cu cheia mai mica
      key                    -- cheia elementului
      (Maybe value)          -- valoarea elementului
      (SearchTree key value) -- elemente cu cheia mai mare
      deriving Show

instance Collection SearchTree where
  empty = Empty
  singleton a b = BNode Empty a (Just b) Empty
  insert a b (BNode l key value r ) 
    | a < key = BNode (insert a b l) key value r
    | a > key = BNode l key value (insert a b r) 
    | a == key = BNode l key (Just b) r
  insert a b Empty = singleton a b
  clookup _ Empty = Nothing
  clookup k (BNode l key o r ) 
    | k == key = o
    | k < key = clookup k l
    | k > key = clookup k r
  delete k (BNode l key value r) 
    | k == key = BNode l key Nothing r
    | k < key = BNode (delete k l) key value r 
    | k > key = BNode l key value (delete k r)
  toList Empty = []
  toList (BNode l key (Just value) r ) = toList l ++ [(key,value)] ++ toList r
  toList (BNode l _ Nothing r ) = toList l++ toList r  


test1=BNode (BNode Empty 1 (Just 5) Empty) 2 (Just 6) (BNode Empty 3 (Just 1) Empty) 


