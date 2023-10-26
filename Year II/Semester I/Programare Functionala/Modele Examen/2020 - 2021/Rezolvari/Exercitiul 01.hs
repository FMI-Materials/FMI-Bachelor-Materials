import Data.Char

data Reteta = Stop | R Ing Reteta
         deriving Show

data Ing = Ing String Int
         deriving Show

-- a
-- String to lower String
bdr10ToLower :: String -> String
bdr10ToLower a = [toLower x | x<-a]

-- Inserare ingredient in Reteta
bdr11Inserare :: Ing -> Reteta -> Reteta
bdr11Inserare ing Stop = R ing Stop
bdr11Inserare (Ing nume1 cant1) (R (Ing nume2 cant2) reteta)
   | (bdr10ToLower nume1) == (bdr10ToLower nume2) = R (Ing nume1 (max cant1 cant2)) reteta
   | otherwise = R (Ing nume2 cant2) (bdr11Inserare (Ing nume1 cant1) reteta) 

-- Parcurgere Reteta si verificare
bdr12Parcurgere :: Reteta -> Reteta -> Reteta
bdr12Parcurgere Stop nou = nou
bdr12Parcurgere (R ing reteta) nou = bdr12Parcurgere reteta (bdr11Inserare ing nou)

-- Functia finala
bdr13Rezultat :: Reteta -> Reteta
bdr13Rezultat reteta = bdr12Parcurgere reteta Stop

-- Teste functie bdr13Rezultat
bdr14Test1 = (bdr13Rezultat (R (Ing "faina" 400) (R (Ing "faina" 30) (R (Ing "mar" 20) Stop)))) == R (Ing "faina" 400) (R (Ing "mar" 20) Stop)
bdr15Test2 = (bdr13Rezultat (R (Ing "faina" 500) (R  (Ing "Oua" 4) (R (Ing "faina" 300) Stop)))) == R (Ing "faina" 500) (R (Ing "Oua" 4) Stop)

-- b
-- Lungime reteta auxiliar
bdr21Length :: Reteta -> Int -> Int
bdr21Length Stop l = l
bdr21Length (R ing rest) l = bdr21Length rest (l+1)

-- Lungime reteta
bdr22Length :: Reteta -> Int
bdr22Length reteta = bdr21Length reteta 0

-- String to lower String
bdr23ToLower :: String -> String
bdr23ToLower a = [toLower x | x<-a]

-- Cautare ingredient in Reteta
bdr24Cautare :: Ing -> Reteta -> Bool
bdr24Cautare _ Stop = False
bdr24Cautare (Ing nume1 cant1) (R (Ing nume2 cant2) reteta)
   | ((bdr23ToLower nume1) == (bdr23ToLower nume2)) && (cant1 == cant2) = True
   | otherwise = bdr24Cautare (Ing nume1 cant1) reteta

-- Comparare retete
bdr25Compare :: Reteta -> Reteta -> Bool
bdr25Compare Stop _ = True
bdr25Compare (R ing reteta1) reteta2
   | bdr24Cautare ing reteta2 = bdr25Compare reteta1 reteta2
   | otherwise = False

-- Functia finala
bdr26Rezultat :: Reteta -> Reteta -> Bool
bdr26Rezultat reteta1 reteta2
   | (bdr22Length reteta1) == (bdr22Length reteta2) = bdr25Compare reteta1 reteta2
   | otherwise = False

instance Eq Reteta where
   reteta1 == reteta2 = bdr26Rezultat (bdr13Rezultat reteta1) (bdr13Rezultat reteta2)

-- Variabile predefinite in cerinta
r1 = R (Ing "faina" 500) (R (Ing "oua" 4) (R  (Ing "zahar" 500) (R (Ing "faina" 300) Stop)))
r2 = R (Ing "fAIna" 500) (R (Ing "zahar" 500) (R (Ing "Oua" 4) Stop ))
r3 = R (Ing "fAIna" 500) (R (Ing "zahar" 500) (R  (Ing "Oua" 55) Stop))

-- Teste intstanta Eq
bdr27Test1 = (r1 == r2) == True
bdr28Test2 = (r1 == r3) == False

-- c
data Arb = Leaf Int String | Node Arb Int String Arb
         deriving Show

-- Concatenare 2 retete
bdr31Concat :: Reteta -> Reteta -> Reteta
bdr31Concat reteta1 Stop = reteta1
bdr31Concat reteta1 (R ing reteta2) = R ing (bdr31Concat reteta1 reteta2)

-- Functia finala
bdr32Reteta :: Arb -> Reteta
bdr32Reteta (Leaf cant nume) = R (Ing nume cant) Stop
bdr32Reteta (Node l cant nume r) = let reteta1 = bdr32Reteta l in
                                   let reteta2 = bdr32Reteta r in
                                   R (Ing nume cant) (bdr31Concat reteta1 reteta2) 

-- Teste functie bdr32Reteta
bdr33Test1 = bdr32Reteta (Node (Leaf 3 "mar") 100 "sare" (Leaf 22 "piper")) == R (Ing "sare" 100) (R (Ing "piper" 22) (R (Ing "mar" 3) Stop))
bdr34Test2 = (bdr32Reteta (Node (Node (Leaf 6 "carne") 23 "piper" (Leaf 88 "Sare")) 100 "marar" (Leaf 22 "dragoste")) == R (Ing "marar" 100) (R (Ing "dragoste" 22) (R (Ing "piper" 23) (R (Ing "Sare" 88) (R (Ing "carne" 22) Stop))))) == False

main = undefined
