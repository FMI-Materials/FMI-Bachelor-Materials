-- 1
data Fruct = Mar String Bool
           | Portocala String Int

cosFructe = [Mar "Ionatan" False,Portocala "Sanguinello" 10,Portocala "Valencia" 22,Mar "Golden Delicious" True,Portocala "Sanguinello" 15,Portocala "Moro" 12,Portocala "Tarocco" 3,Portocala "Moro" 12,Portocala "Valencia" 2,Mar "Golden Delicious" False,Mar "Golden" False,Mar "Golden" True]
-- a
ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Mar _ _) = False
ePortocalaDeSicilia (Portocala soi _)
    | soi == "Tarocco" || soi == "Moro" || soi == "Sanguinello" = True
    | otherwise = False

-- b
nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia l = foldr (+) 0 (map(\(Portocala _ x) -> x) (filter ePortocalaDeSicilia l))

-- c
nrMereViermi :: [Fruct] -> Int
nrMereViermi l = foldr (+) 0 (map do_stuff l) 
                 where do_stuff (Portocala _ _) = 0
                       do_stuff (Mar _ x) = if x then 1 else 0

-- 2
type NumeA = String
type Rasa = String
data Animal = Pisica NumeA | Caine NumeA Rasa
              deriving Show

-- a
vorbeste :: Animal -> String
vorbeste (Pisica _) = "Meow!"
vorbeste (Caine _ _) = "Woof!"

-- b
rasa :: Animal -> Maybe String
rasa (Pisica _) = Nothing
rasa (Caine _ r) = Just r

-- 3
data Linie = L [Int]
     deriving Show
data Matrice = M [Linie]
     deriving Show

-- a
verifica :: Matrice -> Int -> Bool
verifica (M l) n = foldr (&&) True (map (==n) (map sum (map (\(L x) -> x) l)))

-- b
doarPozN :: Matrice -> Int -> Bool
doarPozN (M l) n = foldr (&&) True (map (\(L x) -> foldr (&&) True (map (>0) x)) (filter (\(L x) -> length x == n) l))

-- c
corect :: Matrice -> Bool
corect (M l) = foldr (&&) True (map (\(L x) -> length x == length (head (map (\(L x) -> x) l))) l)