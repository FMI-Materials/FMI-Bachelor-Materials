import Data.Char
import Text.Parsec

-- Cifrul lui Cezar

-- 1.
rotate :: Int -> [Char] -> [Char]
rotate _ [] = error "lista e goala"
rotate n l =
    if n <= 0 || n >= length l
        then error "n e negativ sau e prea mare" 
        else reverse (take (length l + (-n)) (reverse l)) ++ take n l


rotate1 :: Int -> [Char] -> [Char]
rotate1 n l
  | n <= 0 = error "Negativ!"
  | n >= length l = error "Prea Mare!"
  | otherwise = second ++ first
  where
      first = take n l
      second = drop n l

-- 2.
prop_rotate :: Int -> String -> Bool
prop_rotate k str = rotate (l - m) (rotate m str) == str
                        where l = length str
                              m = if l == 0 then 0 else k `mod` l
-- intoarce True daca ajungem inapoi la sirul initial sau False in caz contrar
-- prop_rotate 17 "asdasndjasdasdkadald" = True
-- prop_rotate (-17) "asdasndjasdasdkadald" = True


-- 3.
makeKey :: Int -> [(Char, Char)]
makeKey x = zip ['A'..'Z'] (rotate x ['A'..'Z'])

-- 4.
lookUp :: Char -> [(Char, Char)] -> Char
lookUp x [] = x
lookUp car (ls:l) =
    if car == fst ls
        then snd ls
        else lookUp car l

-- 5.
encipher :: Int -> Char -> Char
encipher nr car = lookUp car (makeKey nr)

-- 6.
normalize :: String -> String
normalize "" = ""
normalize (xs : x)
  | isDigit xs = xs : normalize x
  | isAlpha xs = toUpper xs : normalize x
  | otherwise = normalize x

-- 7.
encipherStr :: Int -> String -> String
encipherStr nr = map (encipher nr) . normalize

-- 8.
reverseKey :: [(Char, Char)] -> [(Char, Char)]
reverseKey = map (\(x,y) -> (y,x))

-- 9.
decipher :: Int -> Char -> Char
decipher n c = lookUp c (reverseKey (makeKey n))

decipherStr :: Int -> String -> String
decipherStr = map . decipher

