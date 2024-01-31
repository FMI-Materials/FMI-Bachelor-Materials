-- 1
-- Q: Apelare valida a lui hof
hof :: (a -> b -> c) -> (a -> b) -> a -> c
hof f h a = f a (h a)
-- A: hof (||) (== False) True

-- 2
-- Q: Rezultatul expresiei f_2 ["Ana", "are", "mere"]
f_2 :: [String] -> Int
f_2 xs = foldr (+) 0 [length x | x <- xs]
-- A: 10

-- 3
-- Q: O secventa dreapta a lui (<+)
(<+) :: String -> [Int] -> Bool
(<+) s x = False
-- A: Nu exista varianta corecta
-- :t ("123" <+) merge, dar e secventa stanga
-- :t ([1,2,3] <+) nu merge pt ca [Int] trebuie pt dreapta
-- :t (<+ ["1","2","3"]) nu merge pt ca [Int] != [String]
-- Un exemplu de raspuns bun era (<+ [1,2,3])

-- 4
-- Q: Valoarea lui x_4
l1_4 = [2, 4..]
l2_4 = ['a','b'..]
l3_4 = zip l1_4 l2_4
x_4 = head $ tail l3_4
-- A: (4,'b')

-- 5
-- Q: Rezultatul expresiei filter (\x -> length x `mod` 2 == 0) ["abc","defg","hi","jkl"]
-- A: ["defg","hi"]

-- 6
-- Q: Declararea corecta a lui Arb
-- A:
data Arb a = Vid | Nod2 (Arb a) (Arb a) | Nod3 (Arb a) (Arb a) (Arb a)
-- data Arb a = vid | nod2 (Arb a) (Arb a) | nod3 (Arb a) (Arb a) (Arb a) invalid, constructorii nu pot incepe cu litera mica
-- data Arb a = Vid | Nod (Arb a) (Arb a) | Nod (Arb a) (Arb a) invalid, nu se poate refolosi acelasi constuctor de date
-- data Arb a = Vid, Nod (Arb a) (Arb a) invalid

-- 7
-- Q: Ce expresie putem folosi pentru a obtine (4, 'b') din l3_7
l1_7 = ['a','b'..]
l2_7 = [2,4..]
l3_7 = take 3 $ zip l1_7 l2_7
-- A: Nu exista varianta corecta
-- :t l3_7 -> [(Char, Integer)], iar (4,'b') este [(Integer, Char)], asadar nu il putem obtine din nicio varianta
-- un exemplu de raspuns bun era (map (\(x,y) -> (y,x)) l3_7) !! 1 
-- sau (\x y -> (x,y)) (snd (unzip l3_7) !! 1) (fst (unzip l3_7) !! 1)

-- 8
-- Q: Care dintre urmatoarele expresii genereaza un raspuns?
-- A: Nu exista varianta corecta
-- foldr (-) 0 lista_infinita nu stie cand sa se opreasca, asadar nu genereaza un raspuns
-- chiar daca ar fi generat un raspuns, acesta ar fi fost un numar, cu care nu putem apela take 3
-- [100..] = [100,101,102..]
-- [100,99..] = [100,99,98..0,-1,-2..] 
-- un exemplu de raspuns bun era take 3 $ [foldr (-) 0 [100,99..0]]

-- 9
-- Q: Care este rezultatul expresiei :t (\x y -> (x+y)^2)
-- A: Num a => a -> a -> a
-- restul nu aveau sintaxa valida

-- 10
-- Ce rezultat va avea evaluarea expresiei h 7?
-- A: Nu exista varianta corecta
-- h x = x + f x let f x = x + 1 nu are sintaxa valida, intrucat let nu este folosit corect
-- varianta corecta era h x = let f x = x + 1 in x + f x, echivalent cu x + x + 1

-- 11
-- Q: Ce valoarea are expresia f_11 [1..10]?
f_11 :: [Int] -> Bool
f_11 xs = foldr (||) True [x `mod` 3 > 0 | x <- xs]
-- A: True
-- foldr op default [x1,x2..xn] = x1 op (x2 op (.. (xn op default)))
-- foldr (||) True [Bool] = Bool || (Bool || (.. (Bool || True))) =  True
-- chiar daca toate Bool-urile erau False i.e. nu existau numere divizibile cu 3 in xs, rezultatul era True din cauza valorii default

-- 12
-- Q: In urma carei expresii obtinem rezultatul [10,11,12,13]?
-- A: [10,11,12,13] == map id [10,11,12,13]
-- id x = x, iar pentru a o aplica integii liste folosim map
-- restul aveau eroare de sintaxa / alt rezultat

-- 13
-- Q: Care este tipul expresiei map (: ["a","b","c"])?
-- A: [String] -> [[String]] i.e. [[Char]] -> [[[Char]]]
-- :t map (functie) --> [a] -> [b], iar :t functie --> a -> b
-- asadar, putem afla a si b din (: ["a","b","c"])
-- ["a","b","c"] este de tip [String], iar (:) este de tipul a -> [a] -> [a], asadar a este String, iar b este [a], adica [String]
-- in concluzie, tipul lui map (: ["a","b","c"]) este [String] -> [[String]]

-- 14
-- Q: Ce tip de data este Animal?
data Animal = Sheep | Cow | Horse
-- A: Animal este data de tip suma
-- Animal este constructor de tip
-- Sheep, Cow si Horse sunt constructori de date

-- 15
-- Q: Ce rezultat va avea expresia filter(\(x,y) -> x == y) [('a',"a"), ('b',"b"), ('c',"d")]
-- A: Nu exista varianta corecta
-- desi filter pastreaza tipul listei, in cazul acesta [(Char,[Char])], functia cu care acesta este apel trebuie sa fie valida
-- tipul lui (==) este a -> a -> Bool, asadar x si y trebuie sa aiba acelasi tip
-- insa, x este de tip Char, iar y este de tip String, deci x == y va produce eroare
-- o varianta corecta era filter(\(x,y) -> x == head y) [('a',"a"), ('b',"b"), ('c',"d")]
-- sau filter(\(x,y) -> [x] == y) [('a',"a"), ('b',"b"), ('c',"d")]