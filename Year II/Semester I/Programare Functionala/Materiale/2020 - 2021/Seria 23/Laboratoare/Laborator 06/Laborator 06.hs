import Data.Char
import Data.List


-- 1.
rotate :: Int -> [Char] -> [Char]
rotate n l 
   | n >= 0, n < (length l) = a ++ b
   where (b, a) = splitAt n l
rotate _ _ = error "Eroare!"

-- 2.
prop_rotate :: Int -> String -> Bool
prop_rotate k str = rotate (l - m) (rotate m str) == str
                        where l = length str
                              m = if l == 0 then 0 else k `mod` l

-- 3.
makeKey :: Int -> [(Char, Char)]
makeKey k = zip alphabet (rotate k alphabet)
   where
     alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

-- 4.
lookUp :: Char -> [(Char, Char)] -> Char
lookUp k [] = k
lookUp k (h:t) = if (fst h) == k then (snd h) else lookUp k t

-- 5.
encipher :: Int -> Char -> Char
encipher k c = lookUp c (makeKey k)

-- 6.
normalize :: String -> String
normalize "" = ""
normalize (h:t) = if isLetter h then
                  if isLower h then
                     (toUpper h):(normalize t)
                  else
                      h:(normalize t)
                  else
                  if isNumber h then
                      h:(normalize t)
                  else
                      normalize t

-- 7.
encipherStr :: Int -> String -> String
encipherStr k str = [encipher k c | c<-(normalize str)]


-- 8.
reverseKey :: [(Char, Char)] -> [(Char, Char)]
reverseKey key = [(b, a) | (a, b)<-key]

-- 9.
decipher :: Int -> Char -> Char
decipher k c = lookUp c (reverseKey (makeKey k))

decipherStr :: Int -> String -> String
decipherStr k str = [if isNumber c then c else decipher k c | c <- str, ((isNumber c) || (isLetter c && isUpper c))]

-- 10
data Fruct = Mar String Bool | Portocala String Int
listaFructe = [Mar "Ionatan" False, Portocala "Sanguinello" 10, Mar "Ceva" True]

-- a
ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Portocala "Tarocco" _) = True
ePortocalaDeSicilia (Portocala "Moro" _) = True
ePortocalaDeSicilia (Portocala "Sanguinello" _) = True
ePortocalaDeSicilia _ = False

-- b
nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia [] = 0
nrFeliiSicilia (h:t) = if ePortocalaDeSicilia h then
                           let (Portocala _ f) = h in f + (nrFeliiSicilia t) 
                       else
                           nrFeliiSicilia t

--c 
nrMereViermi :: [Fruct] -> Int
eMar :: Fruct -> Bool

eMar (Mar _ _) = True
eMar _ = False

nrMereViermi [] = 0
nrMereViermi (h:t) = if eMar h then
                        let (Mar _ v) = h in 
                        let b_i = (\v -> if v == True then 1 else 0) in
                        (b_i v) + (nrMereViermi t)
                     else
                         nrMereViermi t

-- 11
data Linie = L [Int]
data Matrice = M [Linie]

-- a
verifica :: Matrice -> Int -> Bool
verifica (M []) _  = False
verifica (M (h:t)) n = let (L nums) = h in 
                     let sum = foldr (+) 0 nums in
                     sum == n

-- b
instance Show Linie where
   show (L linie) = intercalate " " (map show linie)
instance Show Matrice where
   show (M linii) = intercalate "\n" (map show linii)

-- c
doarPozN :: Matrice -> Int -> Bool
doarPozN (M linii) n = and [all (>0) l | L l <- linii, length l == n] 

main = undefined
