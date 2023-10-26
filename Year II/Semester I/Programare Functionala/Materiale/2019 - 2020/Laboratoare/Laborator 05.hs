import Data.Char ( isAlphaNum, toUpper )
import Data.List (find)
import Data.Maybe (fromMaybe)


rotate :: Int -> [Char] -> [Char]
rotate n str
    | n < 0 = error "n must be a positive integer"
    | n > length str = error "n is greater than the lenght of the given string"
    | otherwise = drop n str ++ take n str


prop_rotate :: Int -> String -> Bool
prop_rotate k str = rotate (l - m) (rotate m str) == str
                        where l = length str
                              m = if l == 0 then 0 else k `mod` l


alphabet :: [Char]
alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
makeKey :: Int -> [(Char, Char)]
makeKey n = zip alphabet (rotate n alphabet)


lookUp :: Char -> [(Char, Char)] -> Char
lookUp ch [] = ch
lookUp ch ((c1,c2):xs)
    | ch == c1 = c2
    | otherwise = lookUp ch xs

lookUp' :: Char -> [(Char, Char)] -> Char
lookUp' ch [] = ch
lookUp' ch ((a,b):xs) = if ch == a then b else lookUp ch xs

lookUp2 :: Char -> [(Char, Char)] -> Char
lookUp2 ch keys =  maybe ch snd (find (\ (x, _) -> x == ch) keys)


enchiper :: Int -> Char -> Char
enchiper n ch = lookUp ch $ makeKey n

normalize :: String -> String
normalize str  = filter isAlphaNum $ map toUpper str

enchiperStr :: Int -> String -> String
enchiperStr n  str = map (enchiper n) (normalize str)

reverseKey :: [(Char, Char)] -> [(Char, Char)]
reverseKey = map(\(x,y) -> (y,x))

dechiper :: Int -> Char -> Char
dechiper n ch = lookUp ch (reverseKey (makeKey n))

dechiperStr :: Int -> String -> String 
dechiperStr n  = map(dechiper n) 