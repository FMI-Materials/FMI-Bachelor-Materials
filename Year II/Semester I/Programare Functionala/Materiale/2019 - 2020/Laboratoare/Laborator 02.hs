import Data.Char (isDigit, digitToInt)

--------------------------------------------------------------------------------
------------------------------------RECURSIE------------------------------------
--------------------------------------------------------------------------------
fibonacciCazuri :: Integer -> Integer
fibonacciCazuri n
    | n < 0 = error "n must be positive"
    | n < 2 = n
    | otherwise = fibonacciCazuri (n - 2) + fibonacciCazuri ( n - 1)


-- Alternativ, putem folosi o definitie in stil ecuational (cu sabloane):
fibonacciEcuational :: Integer -> Integer
fibonacciEcuational 0 = 0
fibonacciEcuational 1 = 1
fibonacciEcuational n = 
    fibonacciEcuational (n - 1) + fibonacciEcuational (n - 2)


fibonacciLiniar :: Integer -> Integer
fibonacciLiniar 0 = 0
fibonacciLiniar n = snd (fibonacciPereche n)
    where 
        fibonacciPereche 1 = (0,1)
        fibonacciPereche n = (b, a + b)
            where (a, b) = fibonacciPereche (n - 1)


-- Data fiind o lista de numere intregi, sa se scrie o functie semiPare care elimina numerele impare si le injumatateste pe cele pare
semiPareRecDestr :: [Int] -> [Int]
semiPareRecDestr l 
    | null l = l
    | even h = h `div` 2 : semiPareRecDestr t
    | otherwise = semiPareRecDestr t
    where 
        h = head l
        t = tail l


semiPareRecEq :: [Int] -> [Int]
semiPareRecEq [] = []
semiPareRecEq (h:t) = if even h then h `div` 2 : t' else t'
    where 
        t' = semiPareRecEq t


semiPareComp :: [Int] -> [Int]
semiPareComp l = [x `div` 2 | x <- l, even x]


-- [In interval] Scrieti o functie care date find limita inferioar si cea superioara (intregi) a unui 
-- interval inchis si o list de numere intregi, calculeaza lista numerelor din lista care apartin intervalului.
inInterval :: Ord a => a -> a -> [a] -> [a]
inInterval inf sup l = [x | x <- l, x >= inf && x <= sup]


-- [Numaram pozitive] Scrieti o functie care numara cate numere strict pozitive sunt intr-o lista data ca argument
numPozitive :: (Ord a, Num a) => [a] -> Int
numPozitive l = length [x | x <- l , x > 0]


-- [Pozitii] Scrieti o functie care dat find o lista de numere calculeaza lista pozitiilor elementelor impare din lista originala
pozitiiImpareAux :: (Integral a1, Num a2) => [a1] -> a2 -> [a2]
pozitiiImpareAux [] _ = []
pozitiiImpareAux (x:xs) a
    | odd x = a : pozitiiImpareAux xs (a + 1)
    | otherwise = pozitiiImpareAux xs (a + 1)

pozitiiImpare :: (Integral a1, Num a2) => [a1] -> [a2]
pozitiiImpare l = pozitiiImpareAux l 0


pozitiiImpareComp :: (Integral a1, Num a2, Enum a2) => [a1] -> [a2]
pozitiiImpareComp l = [index | (x, index) <- zip l [0..], odd x]


-- [MultDigit] Scrieti o functie care calculeaza produsul tuturor cifrelor care apar in sirul de caractere dat ca intrare. 
-- Daca nu sunt cifre in sir raspunsul functiei trebuie sa fie 1.
multDigitsRec "" = 1
multDigitsRec (c:sir)
    | isDigit c = digitToInt c * multDigitsRec sir
    | otherwise = multDigitsRec sir


multDigitsComp :: String -> Int
multDigitsComp sir = product [ digitToInt ch | ch <- sir, isDigit ch ]


-- [Discount] Scrieti o functie care pentru o list de valori (reprezentand niste preturi) aplica un discount 
-- de 25% acelor valori si pastreaz in list doar valorile reduse care sunt mai mici decat 200.
discountRec :: (Ord a, Fractional a) => [a] -> [a]
discountRec [] = []
discountRec (x:xs)
    | 0.75 * x < 200 = 0.75 * x : discountRec xs
    | otherwise = discountRec xs

discountRec2 :: (Ord a, Fractional a) => [a] -> [a]
discountRec2 [] = []
discountRec2 (x:xs) = if discount < 200 then discount : xs' else xs'
    where
        discount = 0.75 * x
        xs' = discountRec xs


discount :: Fractional a => a -> a
discount x = x - 0.25 * x

discountRec3 :: (Ord a, Fractional a) => [a] -> [a]
discountRec3 [] = []
discountRec3 (x:xs)
    | discount x < 200 = discount x : discountRec xs
    | otherwise = discountRec xs


discountComp :: (Ord a, Fractional a) => [a] -> [a]
discountComp l = [ 0.75 * val | val <- l, 0.75 * val < 200 ]


discountComp2 :: [Float] -> [Float]
discountComp2 xs = [ y | x<- xs, let y = discount x, y < 200 ]