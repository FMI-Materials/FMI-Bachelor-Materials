import Data.List
import Test.QuickCheck
--ex1
data Fruct =Mar String Bool | Portocala String Int--tipul suma

ionatanFaraVierme = Mar "Ionatan" False
goldenCuVierme = Mar "Golden" True
portocalaSiciliana10 = Portocala "Siciliana" 10
listaFructe = [Mar "Ionatan" False,
            Portocala "Sanguinello" 10,
            Portocala "Valencia" 22,
            Mar "Golden Delicious" True,
            Portocala "Sanguinello" 15,
            Portocala "Moro" 12,
            Portocala "Tarocco" 3,
            Portocala "Moro" 12,
            Portocala "Valencia" 2,
            Mar "Golden Delicious" False,
            Mar "Golden" False,
            Mar "Golden" True]
--a)
ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Portocala s n) = s== "Tarocco" || s=="Moro" || s=="Sanguinello"
ePortocalaDeSicilia (Mar s b) =False

--b)
nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia l = foldr (\(Portocala s n) acc-> acc+ n) 0 (filter (\f->ePortocalaDeSicilia f )l) 

--comprehensiune liste
nrFeliiSiciliaCOMP :: [Fruct] -> Int
nrFeliiSiciliaCOMP l = sum [ felii | (Portocala soi felii) <-l , ePortocalaDeSicilia (Portocala soi felii)]

--c)
nrMereViermi :: [Fruct] -> Int
nrMereViermi l=length (filter (\f->eMar f )l)
eMar :: Fruct -> Bool
eMar(Mar s b)= b==True
eMar(Portocala s n)=False

--ex2
--a)
data Linie= L [Int]
            deriving Show

data Matrice = M [Linie]
--comprehensiune
verificaC :: Matrice-> Int -> Bool
verificaC (M m) n= and [ n == sum(l) | (L l) <- m]

--foldr
verificaF :: Matrice-> Int -> Bool
verificaF (M m) n= foldr (\ (L l) curent -> curent && (sum (l)==n)) True m

--map
verifica :: Matrice-> Int -> Bool
verifica (M m) n =and( map (\ (L l) -> sum (l)==n ) m)

--b)
--data Matrice =MNull | M[Linie]
instance Show Matrice where
      show (M [])=""
      show (M m)= showL (head m) ++ "\n" ++ show (M(tail m))
                  where 
                        showL (L [] ) = ""
                        showL (L l ) = show (head l) ++" "++ showL (L (tail l))


--c)
--varianta 1
doarPozN :: Matrice -> Int-> Bool
doarPozN (M cm) n = foldr(\l acc -> acc && (vl n l)) True cm

vl:: Int-> Linie ->Bool
vl n (L cl)  = length cl /= n  ||  length( filter(>0) cl) == n

--varianta 2
pozitiv :: [Int] -> Bool
pozitiv l = foldr (\element curent-> curent && (element > 0) ) True l

doarPozN2 :: Matrice -> Int -> Bool
doarPozN2 (M m) n= and [ pozitiv l | (L l) <- m, length l ==n ]