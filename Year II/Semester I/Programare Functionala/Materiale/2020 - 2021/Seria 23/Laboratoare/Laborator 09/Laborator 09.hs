
import Prelude hiding (lookup)
import qualified Data.List as List

class Collection c where
  empty :: c key value
  singleton :: key -> value -> c key value
  insert :: Ord key => key -> value -> c key value -> c key value
  lookup :: Ord key => key -> c key value -> Maybe value
  delete :: Ord key => key -> c key value -> c key value
  keys :: c key value -> [key]
  values :: c key value -> [value]
  toList :: c key value -> [(key, value)]
  fromList :: Ord key => [(key,value)] -> c key value
  --- Declared default
  keys collection = [fst x | x<-toList collection]
  values collection = [snd x | x<-toList collection]
  fromList = fromList'
     where
       fromList' [] = empty
       fromList' (h:t) = insert (fst h) (snd h) (fromList' t)


data PairList key value = PairList { getPairList :: [(key, value)] } deriving (Show)

instance Collection PairList where
  empty = PairList []
  singleton key value = PairList [(key, value)]
  insert key value (PairList l) = PairList (l ++ [(key,value)])
  lookup key (PairList []) = Nothing
  lookup key (PairList (h:t))
     | fst h == key = Just (snd h)
     | otherwise = lookup key (PairList t)
  delete key c = PairList (delete' key (getPairList c))
     where
       delete' _ [] = []
       delete' key (h:t)
         | key == fst h = t
         | otherwise = h:(delete' key t)
  toList (PairList l) = l


data SearchTree key value = Empty
  | Node 
    (SearchTree key value) -- elemente cu cheia mai mica 
    key                    -- cheia elementului
    (Maybe value)          -- valoarea elementului
    (SearchTree key value) -- elemente cu cheia mai mare
  deriving (Show)

instance Collection SearchTree where
  empty = Empty
  singleton key value = Node Empty key (Just value) Empty
  insert key value Empty = singleton key value
  insert key value (Node l key1 value1 r)
    | key < key1 = Node (insert key value l) key1 value1 r
    | otherwise = Node l key1 value1 (insert key value r)
  lookup _ Empty = Nothing
  lookup key (Node l key1 value1 r)
    | key == key1 = value1
    | key < key1 = lookup key l
    | otherwise = lookup key r
  delete key (Node l key1 value1 r)
    | key == key1 = Node l key Nothing r
    | key < key1 = Node (delete key l) key1 value1 r
    | otherwise = Node l key1 value1 (delete key r)
  toList Empty = []  
  toList (Node l key (Just value) r) = toList l ++ [(key, value)] ++ toList r
  toList (Node l key Nothing r) = toList l ++ toList r

order = 1

data Element k v = Element k (Maybe v) | OverLimit

data BTree key value = BEmpty | BNode [(BTree key value, Element key value)]

main = undefined
