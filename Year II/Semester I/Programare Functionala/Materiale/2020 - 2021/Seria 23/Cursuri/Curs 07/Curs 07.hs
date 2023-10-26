
f :: Either Int String -> Int
f (Left x) = x


sum (map f l)

data Erori = DivZero | FactorialNegativ

divide :: Int -> Int -> Either Erori Int
x `divide` 0 = Left DivZero
x `divide` y = Right (x `div` y)

fact :: Int -> Either Erori Int
fact x
  | x < 0 = Left FactorialNegativ
  | otherwise = Right (x * fact (x - 1))


expresie :: Either Erori Int


case expresie of
  Left err => error (show err)
  Right i => i







class RandomGen g where
  next :: g −> ( Int , g)



class Random a where
  random :: RandomGen g => g −> ( a , g )
  randoms :: RandomGen g => g −> [ a ]
  randoms g = x :: randoms g'
    where (x, g') = random g
  randomRs :: (Ord a, RandomGen g) => ( a , a ) −> g −> [ a ]
  randomRs (a, b) g = [x | x <- randoms g, x >= a, x <= b]
  

instance Random Int where
  random = next















