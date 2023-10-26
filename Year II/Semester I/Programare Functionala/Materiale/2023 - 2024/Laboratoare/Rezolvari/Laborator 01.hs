myInt :: Integer
myInt = 31415926535897932384626433832795028841971693993751058209749445923

double :: Integer -> Integer
double x =
    x + x

triple :: Integer -> Integer
triple x =
    x + double x

maxim :: Integer -> Integer -> Integer
maxim x y
    | x > y = x
    | otherwise = y

maxim3 :: Integer -> Integer -> Integer -> Integer
maxim3 x y z
    | x > y && x > z = x
    | y > z = y
    | otherwise = z

maxim4 :: Integer -> Integer -> Integer -> Integer -> Integer
maxim4 x y z t =
    let 
        u = maxim x y 
    in 
        let
            v = maxim u z 
        in 
            maxim v t

checkMaxim4 :: Integer -> Integer -> Integer -> Integer -> Bool
checkMaxim4 x y z t =
    let
        u = maxim4 x y z t 
    in 
        u >= x && u >= y && u >= z && u >= t

sumaPatrate :: Integer -> Integer -> Integer
sumaPatrate x y =
    x * x + y * y

parImpar :: Integer -> String
parImpar x
    | mod x 2 == 0 = "par" 
    | otherwise = "impar"

factorial :: Integer -> Integer
factorial x
    | x == 0 = 1 
    | otherwise = x * factorial (x - 1)

verificare :: Integer -> Integer -> Bool
verificare x y =
    x > double y

maxList :: Ord a => [a] -> a
maxList [x] =
    x
maxList (x:y:xs)
    | x > maxList (y:xs) = x
    | otherwise = maxList (y:xs)

