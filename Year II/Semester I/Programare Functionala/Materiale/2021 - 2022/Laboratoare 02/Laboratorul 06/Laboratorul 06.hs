import Data.Char ( ord, chr, toUpper, isDigit )

-- CODAREA UNUI MESAJ

-- 1. functie care roteste caractere dintr-un
-- sir cu n pozitii la stanga

rotate :: Int -> [Char] -> [Char]
rotate n str | n < 0 = error "Invalid: mai mic ca 0"
rotate n str | n > length str = error "Invalid: mai mare ca lungimea sirului"
rotate n str = drop n str ++ take n str

-- 3. intoarce cheia de criptare cu o anumita
-- deplasare pentru alfabetul englez

makeKey :: Int -> [(Char, Char)]
makeKey n = zip a (rotate n a)
    where a = ['A'..'Z']

-- 4. functie care cauta o pereche dupa prima componenta
-- si intoarce a doua componenta a acesteia

lookUp :: Char -> [(Char, Char)] -> Char
lookUp k [] = k
lookUp k x = if fst (head x) == k then snd (head x)
                else lookUp k (tail x)

-- 5. functie care cripteaza un caracter

encipher :: Int -> Char -> Char
encipher n c = lookUp c ( makeKey n )

-- 6. functie care elimina orice caracter care nu e litera
-- sau cifra si trasforma toate literele in litere mari

normalize :: String -> String 
normalize x = [toUpper c | c <- x, elem (toUpper c) ['A'..'Z'] || isDigit c]

-- 7. functie care normalizeaza un sir si il cripteaza

encipherStr :: Int -> String -> String 
encipherStr n str = [encipher n c | c <- normalize str]

-- DECODAREA UNUI MESAJ

-- 8. inverseaza o cheie de criptare

reverseKey :: [(Char, Char)] -> [(Char, Char)]
reverseKey ls = [(b,a) | (a,b) <- ls]

-- 9. functie care descifreaza un caracter respectiv un sir

decipher :: Int -> Char -> Char
decipher n c = lookUp c (reverseKey (makeKey n))

decipherStr :: Int -> String -> String
decipherStr n str = [decipher n c | c <- str]