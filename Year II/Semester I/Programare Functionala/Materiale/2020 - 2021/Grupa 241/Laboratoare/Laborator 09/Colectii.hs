type Key = Int
type Value = String

class Collection c where
  cempty :: c 
  csingleton :: Key ->  Value -> c 
  cinsert:: Key -> Value -> c  -> c 
  cdelete :: Key -> c  -> c 
  clookup :: Key -> c -> Maybe Value
  ctoList :: c  -> [(Key, Value)]
  ckeys :: c  -> [Key]
  cvalues :: c  -> [Value]
  cfromList :: [(Key,Value)] -> c

newtype  PairList 
  = PairList { getPairList :: [(Key,Value)] }


data SearchTree 
  = Empty
  | Node
      SearchTree  -- elemente cu cheia mai mica 
      Key                    -- cheia elementului
      (Maybe Value)          -- valoarea elementului
      SearchTree  -- elemente cu cheia mai mare
   deriving Show   


