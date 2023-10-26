------------EXPRESII----------
------------------------------
data Expr = Const Int -- integer constant
          | Expr :+: Expr -- addition
          | Expr :*: Expr -- multiplication
           deriving Eq 
--ex1.1
instance Show Expr where
     show (Const n)= show n
     show (e1 :+: e2)= "("++show e1 ++ "+" ++ show e2 ++")"
     show (e1 :*: e2)=  "("++show e1 ++ "*" ++ show e2++")" 

test_ShowExpr :: Bool
test_ShowExpr = show ((Const 2 :+: Const 3) :+: (Const 0 :*: Const 5)) == "((2*3)+(0*5))"

--ex1.2
evalExp :: Expr -> Int
evalExp (Const n) = n
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

--------ARBORI----------------
----------------------------
data Operation = Add | Mult 
               deriving (Eq, Show)
data Tree = Lf Int -- leaf
          | Node Operation Tree Tree -- branch
          deriving (Eq, Show)
--ex 1.3
evalArb :: Tree -> Int
evalArb (Lf x) = x
evalArb (Node Add arb1 arb2) = evalArb arb1 + evalArb arb2
evalArb (Node Mult arb1 arb2) = evalArb arb1 * evalArb arb2

arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)

test21 = evalArb arb1 == 6
test22 = evalArb arb2 == 14
test23 = evalArb arb3 == 13
test24 = evalArb arb4 == 16

--ex1.4
expToArb :: Expr -> Tree
expToArb (Const n) =(Lf n)
expToArb (e1 :+: e2) =(Node Add (expToArb e1)  (expToArb e2))
expToArb (e1 :*: e2) =(Node Mult (expToArb e1)  (expToArb e2))

--ex 1.6
checkExp :: Expr -> Bool
checkExp e = (evalExp e) == evalArb ( expToArb e)
--ex 1.5
class MySmallCheck a where
     smallValues :: [a]
     smallCheck :: ( a -> Bool ) -> Bool
     smallCheck predicat =and [predicat x | x <- smallValues]

instance MySmallCheck Expr where
     smallValues=[exp1, exp2]
--instance MySmallCheck Int where
      --smallValue s = [ 0 , 12 , 3 , 45 , 91 , 100] 
--apel: smallCheck checkExp => True

----------COLLECTION---------------
-------------TYPECLASSES-----------

class Collection c where
      cempty :: c key value
      csingleton :: key -> value -> c key value
      cinsert :: Ord key => key -> value -> c key value -> c key value
      clookup :: Ord key => key -> c key value -> Maybe value
      cdelete :: Ord key => key -> c key value -> c key value
      ckeys :: c key value -> [key]
      ckeys c = [ fst pair | pair <- ctoList c]
      cvalues :: c key value -> [value]
      cvalues c = [ snd pair | pair <- ctoList c]
      ctoList :: c key value -> [(key, value)]
      cfromList :: Ord key => [(key,value)] -> c key value
      cfromList [] = cempty
      cfromList ((k, v) : list )= cinsert k v (cfromList list)
      --cfromList [x] = csingleton (fst x) (snd x)
      
newtype PairList k v = PairList { getPairList :: [(k, v)] }
instance Collection PairList where
      cempty = PairList [] 
      csingleton k v= PairList [(k, v)]
      cinsert k v (PairList l) = if k `elem` ckeys (PairList l) then (PairList l) else (PairList ([(k,v)]++l)) 
      cdelete k (PairList l) = PairList [(key,value) | (key, value) <- l, key /= k]
      ctoList (PairList l) = l
      clookup _ (PairList [])=Nothing
      clookup k (PairList (h:t)) 
            |k == (fst h) = Just (snd h)
            |otherwise= clookup k (PairList t)
           
data SearchTree key value
      = Empty
      | Nodee
            (SearchTree key value) -- elemente cu cheia mai mica
            key -- cheia elementului
            (Maybe value) -- valoarea elementului
            (SearchTree key value) -- elemente cu cheia mai mare  
instance Collection SearchTree where
      cempty = Empty 
      csingleton k v= Nodee Empty k (Just v) Empty
      cinsert k v Empty = csingleton k v 
      cinsert k v ( Nodee arb1 key value arb2) = if (k> key) then Nodee arb1 key value (cinsert k v arb2) else Nodee arb2 key value (cinsert k v arb1) 
      --cdelete k v ( Nodee arb1 key value arb2)= if (k==key) then Nodee arb1 key Nothing arb2 else if (k>key) then Nodee arb1 key (Just value) arb2 (cdelete k v arb2) else Nodee arb1 key (Just value) arb2 (cdelete k v arb1)
      ctoList Empty =[]
      ctoList (Nodee arb1 k Nothing arb2 )=  (ctoList arb1 )++ (ctoList arb2)
      ctoList (Nodee arb1 k  (Just v) arb2) =  (ctoList arb1 )++[(k,v)] ++ (ctoList arb2)
      clookup k Empty = Nothing
      clookup k ( Nodee arb1 key value arb2) = if (k==key)  then value
                                            else if (k>key) then clookup k arb2
                                                else clookup k arb1