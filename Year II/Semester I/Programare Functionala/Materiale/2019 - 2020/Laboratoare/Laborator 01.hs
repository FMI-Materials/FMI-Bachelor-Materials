myInt = 55555555555555555555555555555555555555555555555555555555555
double :: Integer -> Integer
double x = x+x

triple :: Int -> Int
triple x = 3 * x

suma:: (Int, Int) -> Int
suma (x, y) = x + y

suma':: Int -> Int -> Int
suma' x y = x + y

maxim x y = if(x > y) then x else y

maxim3 :: Int -> Int -> Int -> Int
maxim3 x y z = maxim x (maxim y z)

maxim3' :: Int -> Int -> Int -> Int
maxim3' x y z = 
    if (x > y)
        then if(x > z)
            then x
            else if(y > z)
                then y
                else z
        else if(y > z)
            then y
            else z

maxim3'' :: Int -> Int -> Int -> Int
maxim3'' x y z = let u = (maxim x y) in (maxim u z)

maxim4 a b c d = let u  = (maxim3 a b c) in (maxim u d)

maxim4' a b c d = x
    where
        y = maxim3 a b c
        x = maxim y d

maxim4'' a b c d =
    let 
        x = maxim a b
        y = maxim c d
    in maxim x y

testmaxim4 a b c d = if x >= a && x >= b && x >= c && x >= d then True else False
    where
        x = maxim4 a b c d

--Exercitii
-- (i) Functie cu 2 parametrii ce calculeaza suma patratelor a doua numere
patrat :: Int -> Int
patrat x = x * x

suma_patrate :: Int -> Int -> Int
suma_patrate x y = (patrat x) + (patrat y)

-- (ii) Functie cu un parametru care intoarce mesajul "par" daca parametrul este par si "impar" altfel
paritate :: Int -> String
paritate n = if n `mod` 2 == 0 then "par" else "impar"

-- (iii) Functie care calculeaza factorialul unui numar 
fact n = product[1..n]

fact' 1 = 1
fact' n = n * fact (n-1)

-- (iv) Functie cu 2 parametrii care verifica daca primul este mai mare decat dublul celui de al doilea
verif x y = x > 2 * y

verif2 x y
 | x > 2 * y = "Da"
 | otherwise = "Nu"