sfChr :: Char -> Bool
sfChr ch = ch `elem` ['.', '?', '!', ':']

numarPropozitiiRec :: [Char] -> Int
numarPropozitiiRec [] = 0
numarPropozitiiRec (x:xs) = (if sfChr x then 1 else 0) + numarPropozitiiRec xs


numarPropozitii :: (Foldable t, Num b) => t Char -> b
numarPropozitii = foldr(\x -> (+) (if sfChr x then 1 else 0)) 0 

nrPropListComp :: Num a => [Char] -> a
nrPropListComp propozitii = sum [1| x <- propozitii, sfChr x]

testNumarPropozitii :: Bool
testNumarPropozitii = numarPropozitiiRec "Ana are mere." == 1
testNumarPropozitii' = numarPropozitii "Ana are mere? Ana are mere!" == 2
testNumarPropozitii'' = nrPropListComp "Ana. are? mere: si pere!" == 4


all' fct = foldr (&&) True . map fct
any' fct = foldr (||) True . map fct

liniiN :: (Ord a, Num a) => [[a]] -> Int -> Bool
liniiN [[]] _ = False
liniiN matrice n = length (areAllPositive (rowsOfLength matrice n)) == length (rowsOfLength matrice n)
    where 
        rowsOfLength matrice n = filter((==n) . length) matrice
        areAllPositive rows = filter(all' (>0)) rows


newtype Punct = Pt [ Int ]
            deriving Show

data Arb = Vid | F Int | N Arb Arb
            deriving Show
-- showArb :: Arb -> [Char]
-- showArb (F a) = show a
-- showArb (N arb_left arb_right) = "(" ++ showArb arb_left ++ "),(" ++ showArb arb_right ++ ")"

-- instance Show Arb where
--     show = showArb
class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a


instance ToFromArb Punct where
    toArb (Pt coordonate) = coordToArbRec coordonate
        where
            coordToArbRec [] = Vid
            coordToArbRec (x:xs) = N (F x) (coordToArbRec xs)
    fromArb arb = Pt (arbToCoordRec arb)
        where
            arbToCoordRec Vid = []
            arbToCoordRec (N (F x) t) = x : arbToCoordRec t