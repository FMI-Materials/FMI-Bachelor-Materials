myInt = 5555555555555
double :: Integer -> Integer
double x = x+x

maxim :: Integer -> Integer -> Integer
maxim x y =
    if x > y
        then x
        else y

maxim31 x y z = maxim x (maxim y z)
maxim32 x y z =
    if x >= y && y >= z
        then x
        else if y >= x && x >= z
            then y
            else z

maxim33 x y z
  | x > y && x > z = x
  | y > x && y > z = y
  | otherwise = z
--maxim3 x y z = let u = (maxim x y) in (maxim u z)

--maxim4 x y z t = let u = (maxim3 x y z) in (maxim u t)

maxim4 x y z t =
    let
        u = maxim31 x y z
    in
        maxim u t

verif1 x y z t =
    (maxim4 x y z t) >= x && (maxim4 x y z t) >= y && (maxim4 x y z t) >= z && (maxim4 x y z t) >=t


--Exercitii
--a) functie cu 2 parametri care calculeaza suma pătratelor celor două numere;
sumaPatrate :: Num a => a -> a -> a
sumaPatrate x y = x * x + y * y
--b) functie cu un parametru ce întoarce mesajul “par” dacă parametrul este par s, i “impar” altfel;
paritate :: Integral a => a -> String
paritate x = if mod x 2 == 0 then "par" else "impar"
--c) functie care calculează factorialul unui număr;
factorial :: (Integral p) => p -> p
factorial x =
    if x <= 1
        then 1
        else x * factorial(x - 1)
factorial1 :: (Integral a) => a -> a
factorial1 x = product[1..x]
--d) functie care verifică dacă un primul parametru este mai mare decât dublul celui de-al doilea parametru. 
verifica :: (Ord a, Num a) => a -> a -> Bool
verifica x y = 
    if x > y * y
        then True 
        else False 


verifica1 :: (Ord a, Num a) => a -> a -> Bool
verifica1 x y = 
    x > y * y
    
