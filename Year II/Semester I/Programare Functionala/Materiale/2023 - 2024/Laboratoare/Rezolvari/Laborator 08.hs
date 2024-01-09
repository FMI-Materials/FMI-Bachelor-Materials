class Collection c where
    empty :: c key value
    singleton :: key -> value -> c key value
    insert
        :: Ord key
        => key -> value -> c key value -> c key value
    lookup :: Ord key => key -> c key value -> Maybe value
    delete :: Ord key => key -> c key value -> c key value
    keys :: c key value -> [key]
    values :: c key value -> [value]
    toList :: c key value -> [(key, value)]
    fromList :: Ord key => [(key,value)] -> c key value

    -- 1
    keys = map fst . toList
    values = map snd . toList
    fromList = foldr (\(k, v) acc -> insert k v acc) empty


-- 2
newtype PairList k v = PairList { getPairList :: [(k, v)] } deriving (Show)

instance Collection PairList where
    empty = PairList []
    singleton k v = PairList [(k, v)]
    insert k v (PairList pairs) = PairList $ (k, v) : filter (\(key, _) -> key /= k) pairs
    lookup k (PairList pairs) = lookupKey k pairs where 
                                lookupKey _ [] = Nothing
                                lookupKey key ((k',v):xs)
                                    | key == k' = Just v
                                    | otherwise = lookupKey key xs
    delete k (PairList pairs) = PairList $ filter (\(key, _) -> key /= k) pairs
    toList = getPairList

myPairList :: PairList String Int
myPairList = PairList [("a", 1), ("b", 2), ("c", 3)]

-- 3
data SearchTree key value
    = Empty
    | BNode
        (SearchTree key value)
        key
        (Maybe value)
        (SearchTree key value)
    deriving Show

instance Collection SearchTree where
    empty = Empty
    singleton k v = BNode Empty k (Just v) Empty
    insert k v tree = insertElement k v tree where
                      insertElement k v Empty = singleton k v
                      insertElement k v (BNode left key value right)
                          | k == key = BNode left key (Just v) right
                          | k < key = BNode (insertElement k v left) key value right
                          | otherwise = BNode left key value (insertElement k v right)
    lookup k tree = lookupKey k tree where
                    lookupKey _ Empty = Nothing
                    lookupKey k (BNode left key value right)
                        | k == key = value
                        | k < key = lookupKey k left
                        | otherwise = lookupKey k right
    delete k tree = deleteKey k tree where
                    deleteKey _ Empty = Empty
                    deleteKey k (BNode left key value right)
                        | k == key = BNode left key Nothing right
                        | k < key = BNode (deleteKey k left) key value right
                        | otherwise = BNode left key value (deleteKey k right)
    toList tree = toList' tree where
                  toList' Empty = []
                  toList' (BNode left key Nothing right) = toList left ++ toList right
                  toList' (BNode left key value right) = toList left ++ [(key, val)] ++ toList right where Just val = value

mySearchTree :: SearchTree String Int
mySearchTree = BNode (BNode Empty "a" (Just 1) Empty) "b" (Just 2) (BNode Empty "c" (Just 3) Empty)


data Punct = Pt [Int]

data Arb = Vid | F Int | N Arb Arb
    deriving Show

class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a

-- 4
instance Show Punct where
    show (Pt []) = show ()
    show (Pt (x:xs)) = "(" ++ show x ++ show' xs where
                       show' [] = ")"
                       show' (x:xs) = "," ++ show x ++ show' xs

-- 5
instance ToFromArb Punct where
    toArb (Pt l) = toArb' l where
                   toArb' [] = Vid
                   toArb' (x:xs) = N (F x) (toArb' xs)
    fromArb arb = fromArb' arb where
                  fromArb' Vid = Pt []
                  fromArb' (F x) = Pt [x]
                  fromArb' (N left right) = Pt ((justList $ fromArb' left) ++ (justList $ fromArb' right)) where
                                            justList (Pt l) = l


data Geo a = Square a | Rectangle a a | Circle a
     deriving Show

class GeoOps g where
    perimeter :: (Floating a) => g a -> a
    area :: (Floating a) => g a -> a

-- 6
instance GeoOps Geo where
    perimeter figure = perimeter' figure where
                       perimeter' (Square a) = 4 * a
                       perimeter' (Rectangle a b) = 2 * (a + b)
                       perimeter' (Circle r) = 2 * pi * r
    area figure = area' figure where
                  area' (Square a) = a * a
                  area' (Rectangle a b) = a * b
                  area' (Circle r) = pi * r * r

-- 7
instance (Eq a, Floating a) => Eq (Geo a) where
    (==) figure1 figure2 = perimeter figure1 == perimeter figure2