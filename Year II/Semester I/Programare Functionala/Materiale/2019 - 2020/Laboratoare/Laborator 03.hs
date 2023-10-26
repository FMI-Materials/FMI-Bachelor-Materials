import Data.List ()

-- [Denirea listelor prin comprehensiune]
list1 = [ x ^ 2 | x <- [1..10], x `rem` 3 == 2 ] 
list2 = [ (x,y) | x <- [1..5], y <- [x..(x+2)]] 
list3 = [ (x,y) | x <- [1..3], let k = x ^ 2,  y <- [1..k]] 
list4 = [ x | x <- " Facultatea de Matematica si Informatica " , x `elem`  ['A'..'Z'] ] 
list5 = [ [x,y] | x <- [1..5], y <- [1..5], x < y ]



factori :: Int -> [Int]
factori n = [ x | x <- [1..n] , n `mod` x == 0]

prim :: Int -> Bool
prim n = length ( factori n ) == 2

numerePrime :: Int -> [Int]
numerePrime n = [ x | x <- [2..n], prim x]


myzip3 :: [Integer] -> [Integer] -> [Integer] -> [(Integer, Integer, Integer)]
myzip3 _ _ [] = []
myzip3 _ [] _ = []
myzip3 [] _ _ = []
myzip3 (x:xs) (y:ys) (z:zs) = (x,y,z) : myzip3 xs ys zs


myZip3 :: [a] -> [b] -> [c] -> [(a, b, c)]
myZip3 l1 l2 = myzipAux ( zip l1 l2 )
    where 
        myzipAux _ [] = []
        myzipAux [] _ = []
        myzipAux ((x,y):xys) (z:zs) = (x,y,z) : myzipAux xys zs


----------------------------------------------------------------------
----------------------- FUNCTII DE NIVEL INALT -----------------------
----------------------------------------------------------------------

aplica2 :: (a -> a) -> a -> a
-- aplica2 f x =  f $ f x
aplica2 f x = f (f x)
-- aplica2 f = f . f
--aplica2 f = \x -> f (f x)
--aplica2  = \f x -> f (f x)


firstEl :: [(a,b)] -> [a]
firstEl = map fst

secondEl :: [(a,b)] -> [b]
secondEl = map snd

thirdEl :: [(a,b,c)] -> [c]
thirdEl = map(\(_,_,c) -> c)


sumList :: [[Integer]] -> [Integer]
sumList = map sum


prel2 :: [Integer] -> [Integer]
prel2 =  map prelucreaza
    where
        prelucreaza x
            | even x = x `div` 2
            | otherwise = x * 2


prel2' :: [Integer] -> [Integer]
prel2' = map (\x -> if even x then x `div` 2 else x * 2)

prel2Comp :: Integral a => [a] -> [a]
prel2Comp l = [k | x <- l, let k = if even x then x `div` 2 else x * 2]


filtrareSir :: Char -> [String] -> [String]
filtrareSir ch =  filter (elem ch)


numereImpare :: [Integer] -> [Integer]
numereImpare = map (^2) . filter odd 


pozitiiImpare :: [Integer] -> [Integer]
pozitiiImpare = map ((^2) . snd ) . filter(odd . fst) . zip [0..] 


numaiVocale :: [[Char]] -> [[Char]]
numaiVocale = map $ filter( `elem` "aeiouAEIOU") 


mymap :: (a -> b) -> [a] -> [b]
mymap f l = [ f x | x <- l]

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter _ [] = []
myfilter f (x:xs) = if f x then x : myfilter f xs else myfilter f xs


eratostheneSieve :: Int -> [Int]
eratostheneSieve n = eratostheneSieveAux [2..n]
    where 
        eratostheneSieveAux [] = []
        eratostheneSieveAux (p:xs) = p : eratostheneSieveAux [x | x <- xs, x `rem` p /= 0]


and' l = foldr (&&) True l

ordonataNat :: [Int] -> Bool
ordonataNat [] = True
ordonataNat [_] = True
ordonataNat (x:y:xs) = x < y && ordonataNat xs

ordonataNat' :: Ord a => [a] -> Bool
ordonataNat' l = and [ x < y | (x,y) <- zip l (tail l) ]

ordonata :: [t] -> (t -> t -> Bool) -> Bool
ordonata [] _ = True
ordonata l p = and' [ p x y | (x,y) <- zip l (tail l) ]

(*<*) :: (Integer, Integer) -> (Integer, Integer) -> Bool
(*<*) (a,b) (c,d) = a < d && b < c 


compuneList :: (b -> c) -> [a -> b] -> [a -> c]
compuneList f  =  map ( f . )

aplicaList :: t -> [t -> b] -> [b]
aplicaList arg l = map(\f ->  f arg) l