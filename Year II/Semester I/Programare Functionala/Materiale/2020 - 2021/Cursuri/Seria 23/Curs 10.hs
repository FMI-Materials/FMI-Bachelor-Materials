


((->) t)

Obiecte:  (->) t a, adică t -> a
Sageți :  t -> a
               |          
               v
          t -> b




(+) : Int -> (Int -> Int)

Maybe Int -> Maybe Int -> Maybe Int


fmap (+) : Maybe Int -> Maybe (Int -> Int)


fmap  :        Int -> Int  -> (Maybe Int -> Maybe Int)
(<*>) : Maybe (Int -> Int) -> (Maybe Int -> Maybe Int)


pure :: a -> m a

pure :: (a -> b) -> m (a -> b)

(<*>) :: m (a -> b) -> (m a -> m b)

fmap :: (a -> b) -> (m a -> m b)

f :: a -> b
x :: m a

fmap = (<*>) . pure

pure f <*> ca1 <*> ... <*> can === f <$> ca1 <*> ... <*> can


