import Data.List
myInt=5

double :: Integer -> Integer
double x= x+x

triple :: Integer -> Integer
triple a= a+a+a

maxim :: Integer-> Integer->Integer
maxim x y =if (x>y) then x else y

maxim3 :: Integer-> Integer-> Integer->Integer
maxim3 x y z=maxim x (maxim y z)
max3 x y z=let u= maxim x y in (maxim u z)
fact x=let     
      z=x*x*x
      t=x+x
      w=23+x
   in (z+t+w)
--data Bool=True|False (ca la ele)
--pt orice tip de data nou trebuie sa
--spunem cum sa afiseze => toString
data Alegere =Piatra| Foarfeca| Hartie
              deriving (Eq, Show)--pt afisare
data Rezultat= Victorie|Infrangere|Egalitate
               deriving(Show, Eq)
partida :: Alegere -> Alegere -> Rezultat
partida x y = if ((x==Piatra && y==Foarfeca) || (x==Piatra && y==Hartie) || (x==Foarfeca && y==Hartie))
              then Victorie
              else if(x==y) then Egalitate else Infrangere
