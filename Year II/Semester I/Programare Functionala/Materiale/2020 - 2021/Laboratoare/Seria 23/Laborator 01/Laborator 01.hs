import Data.List

myInt = 5555555555555555555555555555555555555555555555555555555555555555555555555555555555555

double :: Integer -> Integer
double x = x+x


--maxim :: Integer -> Integer -> Integer
maxim x y = if (x > y)
               then x
          else y
maxim3 x y z = let u = (maxim x y) in (maxim u z)
max3 x y z = let
             u = maxim x y
             in (maxim  u z)

data Alegere = Piatra | Foarfece | Hartie deriving (Eq, Show)
data Rezultat = Victorie | Infrangere | Egalitate deriving (Eq, Show)

partida :: Alegere -> Alegere -> Rezultat

partida Piatra Foarfece = Victorie
partida Piatra Hartie = Infrangere
partida Piatra Piatra = Egalitate

partida Foarfece Piatra = Infrangere
partida Foarfece Hartie = Victorie
partida Foarfece Foarfece = Egalitate

partida Hartie Piatra = Victorie
partida Hartie Foarfece = Infrangere
partida Hartie Hartie = Infrangere


main = print "Hello"
