import GHC.Types (Nat)
{-
[ x^2 |x <- [1..10], x `rem` 3 == 2] = [4,25,64]
[(x,y)| x<- [1..5], y <- [x..(x+2)]] = [(1,1),(1,2),(1,3),(2,2),(2,3),(2,4),(3,3),(3,4),(3,5),(4,4),(4,5),(4,6),(5,5),(5,6),(5,7)]
[(x,y)| x<-[1..3], let k = x^2, y <- [1..k]] = [(1,1),(2,1),(2,2),(2,3),(2,4),(3,1),(3,2),(3,3),(3,4),(3,5),(3,6),(3,7),(3,8),(3,9)]
[ x | x<- "Facultatea de Matematica si Informatica", elem x ['A'..'Z']] = "FMI"
[[x..y]| x <- [1..5], y <- [1..5], x < y] = [[1,2],[1,2,3],[1,2,3,4],[1,2,3,4,5],[2,3],[2,3,4],[2,3,4,5],[3,4],[3,4,5],[4,5]]
-}
--1. Folosind numai metoda prin selectie definiti o functie
--astfel încât factori n întoarce lista divizorilor pozitivi ai lui n.
factori :: Int -> [Int]
factori x = [y | y <- [1..x], x `rem` y == 0]

--2. Folosind functia factori, definiti predicatul prim n care întoarce True dacă si numai dacă n este număr prim.
prim :: Int -> Bool
prim n = length (factori n) == 2

--3. Folosind numai metoda prin selectie si functiile definite anterior,
--definiti functia 
numerePrime :: Int -> [Int]
numerePrime n = [x | x<-[2..n], prim x]

--4. Definiti functia myzip3 care se comportă asemenea lui zip dar are trei argumente:
myzip3 :: [a] -> [a] -> [a] -> [(a,a,a)]
myzip3 x y z =  [(a, b, c) | ((a, b), c) <- zip (zip x y) z]

--5. Folosind metoda prin selectie, functia and si functia zip, completati
--definitia functiei ordonataNat care verifică dacă o listă de valori Int este
--ordonată, relatia de ordine fiind cea naturală:
ordonataNat :: [Int] -> Bool
ordonataNat [] = True
ordonataNat [x] = True
ordonataNat (x:xs) = and [ x <= y | (x,y) <- zip (x:xs) xs]

--6. Folosind doar recursie, definiti functia ordonataNat1, care are acelasi 
--comportament cu functia de mai sus.
ordonataNat1 :: [Int] -> Bool
ordonataNat1 [] = True
ordonataNat1 [x] = True
ordonataNat1 (x:xs) = x < head xs && ordonataNat1 xs

--7. Scrieti o functie ordonata generică cu tipul

ordonata :: [a] -> (a -> a -> Bool) -> Bool
ordonata [] functie = True
ordonata [x] functie = True
ordonata (x:y:xs) functie =
    functie x y && ordonata (y:xs) functie

divizibil :: Int -> Int -> Bool
divizibil x y = mod x y == 0

--8. Definiti un operator *<*, asociativ la dreapta, cu precedenta 6, cu signatura
--care defines, te o relatie pe perechi de numere întregi (alegeti voi relatia).
--Folosind functia ordonata verificat,dacă o listă de perechi este ordonată fată
--de relatia *<*.
(*<*) :: (Integer, Integer) -> (Integer, Integer) -> Bool
(x,y) *<* (z,t) = x * y < z * t


--9. Scrieti o functie compuneList de tip care primeste ca argumente o functie si o listă
-- de functii si întoarce lista functiilor obtinute prin compunerea primului argument cu fiecare functie
-- din al doilea argument.
compuneList :: (b -> c) -> [a -> b] -> [a -> c]
compuneList functie l = map (functie.) l

compuneList1 :: (b -> c) -> [a -> b] -> [a -> c]
compuneList1 functie l = map (\x -> functie . x) l

--10.Scrieti o functie aplicaList de tip care primeste un argument de tip a si o listă de 
--functii de tip a -> b si întoarce lista rezultatelor obtinute prin aplicarea functiilor 
--din listă pe primul argument:
aplicaList :: a -> [(a -> b)] -> [b]
aplicaList arg1 functii = [fct arg1 | fct <- functii]

aplicaList1 :: a -> [(a -> b)] -> [b]
aplicaList1 arg1 functii = map (\fct -> fct arg1) functii