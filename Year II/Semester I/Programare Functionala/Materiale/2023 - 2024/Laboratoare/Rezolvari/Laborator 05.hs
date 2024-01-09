-- 1
sumaPatrateImpare :: [Int] -> Int
sumaPatrateImpare l = 
    sum [x^2 | x <- l, odd x]

-- 2
allTrue :: [Bool] -> Bool
allTrue l = foldr (&&) True l

-- 3
allVerifies :: (Int -> Bool) -> [Int] -> Bool
allVerifies expr l = allTrue (map (expr) l)

-- 4 
anyVerifies :: (Int -> Bool) -> [Int] -> Bool
anyVerifies expr l = foldr (||) False (map (expr) l)

-- 5
mapFoldr :: (a -> b) -> [a] -> [b]
mapFoldr expr l = foldr (\x l -> expr x : l) [] l

filterFoldr :: (a -> Bool) -> [a] -> [a]
filterFoldr expr l = foldr (\x l -> if expr x then x : l else l) [] l

-- 6
listToInt :: [Integer] -> Integer
listToInt l = foldl (\x cif -> x * 10 + cif) 0 l

-- 7
-- a
rmChar :: Char -> String -> String
rmChar c s = foldr (\x l -> if x == c then l else x : l) [] s

-- b
rmCharsRec :: String -> String -> String
rmCharsRec [] s2 = s2
rmCharsRec (c1 : s1) s2 = rmCharsRec s1 (rmChar c1 s2)

-- c
rmCharsFold :: String -> String -> String
rmCharsFold s1 s2 = foldr (\c l -> rmChar c l) s2 s1

-- 8
myReverse :: [Int] -> [Int]
myReverse l = foldl (\l x -> x : l) [] l

-- 9
myElem :: Int -> [Int] -> Bool
myElem x l = foldr (||) False (map (== x) l)

-- 10
myUnzip :: [(a, b)] -> ([a], [b])
myUnzip l = foldr (\(x, y) (xs, ys) -> (x : xs, y : ys)) ([], []) l

-- 11
union :: [Int] -> [Int] -> [Int]
union l1 l2 = foldr (\x y -> if (myElem x y) then y else x : y) l1 l2

-- 12
intersect :: [Int] -> [Int] -> [Int]
intersect l1 l2 = foldr (\x y -> if (myElem x l1) then x : y else y) [] l2

-- 13
pozitioneazaPesteTot :: Int -> [Int] -> [[Int]]
pozitioneazaPesteTot x l = foldr (\a y -> ((take a l) ++ (x : (reverse . take (length l - a) . reverse $ l))):y) [] [0..(length l)]

permutations :: [Int] -> [[Int]]
permutations [] = [[]]
permutations (p:ps) = foldr (\x y -> (pozitioneazaPesteTot p x) ++ y) [] (permutations ps)