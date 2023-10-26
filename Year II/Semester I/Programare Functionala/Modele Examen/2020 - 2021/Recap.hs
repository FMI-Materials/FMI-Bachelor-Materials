a :: Int 
a = 5

b :: Integer 
b = 5

c :: Char 
c = 'a'

type Nume = [Char]
d :: Nume
d = "Salut"

f :: Int -> (Int -> Int)
f x y = x + y

g :: Int -> Int
g = f 3

h :: (Int -> Int) -> Int 
h functie = functie 3

-- un nume bun ar fi aplica5
h' :: (Int -> a) -> a 
h' functie = functie 5


complicat x y z t w v = x + y + z * t + w * (-v)

complicat' x = \y -> \z -> \t -> \w -> \v -> complicat x y z t w v

l1 :: [Integer]
l1 = [1, 2, 3]

l2 :: [[Int]]
l2 = [[1, 2, 3], [4, 5, 6]]

--l2' :: [[Int]]
--l2' :: [[] Int]
l2' :: [] ([] Int)
l2' = (1:2:3:[]):(4:5:6:[]):[]

l3 :: [a]
l3 = []

maybe1 :: Maybe Int 
maybe1 = Just 5

maybe2 :: Maybe a
maybe2 = Nothing 

maybe3 :: Num a => Maybe (Maybe a)
maybe3 = Just (Just 5)

deduplicate [] = []
deduplicate [x] = [x]
deduplicate (x:y:t) = if x == y then deduplicate (y:t) else x:(deduplicate (y:t))

range start step = (start:(range (start + step) step))

divisori n = [x | x <- [1..n], n `mod` x == 0]

[] +++ lista = lista 
(h:t) +++ lista = h:(t +++ lista)

eprim x = divisori x == [1, x]
filtru_prime = filter eprim

toate_pozitive lista = foldr (\elem -> \accum -> elem > 0 && accum) True lista
length' lista = foldr (\_ accum -> 1 + accum) 0 lista

data Expresii a = Numar a | Negare (Expresii a) | (Expresii a) :+: (Expresii a) | (Expresii a) :*: (Expresii a)

instance Show a => Show (Expresii a) where 
    show (Numar x) = show x
    show (Negare x) = "-" ++ show x
    show (x :+: y) = "(" ++ show x ++ " + " ++ show y ++ ")"
    show (x :*: y) = show x ++ " * " ++ show y

instance Num a => Num (Expresii a) where 
    x + y = x :+: y 
    negate x = (Negare x)
    x * y = x :*: y 
    abs = undefined 
    signum = undefined
    fromInteger i = Numar (fromInteger i)

instance Foldable Expresii where 
    foldr f accum (Numar x) = f x accum
    foldr f accum (Negare x) = foldr f accum x
    foldr f accum (x :+: y) = foldr f (foldr f accum y) x
    foldr f accum (x :*: y) = foldr f (foldr f accum y) x 

    foldMap f (Numar x) = f x
    foldMap f (Negare x) = foldMap f x 
    foldMap f (x :+: y) = (foldMap f x) <> (foldMap f y)
    foldMap f (x :*: y) = (foldMap f x) <> (foldMap f y)

data Sum a = Sum a deriving Show

instance Num a => Semigroup (Sum a) where 
    (Sum x) <> (Sum y) = Sum (x + y)

instance Num a => Monoid (Sum a) where 
    mempty = Sum 0

data Prod a = Prod a deriving Show

instance Num a => Semigroup (Prod a) where 
    (Prod x) <> (Prod y) = Prod (x * y)

instance Num a => Monoid (Prod a) where 
    mempty = Prod 1

data Optional a = Nimic | Ceva a deriving Show

instance Functor Optional where 
    fmap functie Nimic = Nimic 
    fmap functie (Ceva x) = Ceva (functie x)

instance Applicative Optional where 
    pure = Ceva
    (Ceva functie) <*> (Ceva elem) = Ceva (functie elem)
    _ <*> _ = Nimic

instance Monad Optional where 
    Nimic >>= _ = Nimic 
    (Ceva x) >>= f = f x

data Lista a = Gol | a ::: (Lista a) deriving Show

infixr :::

concatenare Gol ceva = ceva 
concatenare (h:::tail) ceva = h:::(concatenare tail ceva)

instance Monad Lista where 
    return x = x ::: Gol 

    Gol >>= _ = Gol
    (h:::t) >>= f = 
        let lista = f h in 
        let restul = t >>= f in 
        concatenare lista restul

instance Applicative Lista where 
    pure = return 

    -- cutie_functie <*> cutie_elemente = do
        -- f <- cutie_functie
        -- x <- cutie_elemente
        -- return (f x)
    cutie_functie <*> cutie_elemente = 
        cutie_functie >>= (\f -> cutie_elemente >>= (\x -> return (f x)))

instance Functor Lista where 
    fmap functie cutie = (pure functie) <*> cutie

citeste_n_numere :: Int -> IO [Int]
citeste_n_numere 0 = return []
citeste_n_numere n = do 
    x <- readLn :: IO Int 
    aux <- citeste_n_numere (n - 1)
    return (x : aux)

afiseaza_lista :: [Int] -> IO ()
afiseaza_lista [] = return ()
afiseaza_lista (h:t) = do 
    print h -- echivalent cu _ <- print h 
    afiseaza_lista t 

plan_de_bataie = do 
    n <- readLn :: IO Int 
    lista <- citeste_n_numere n 
    let l = reverse lista 
    afiseaza_lista l

-- Promise.all 
combina_planuri :: [IO a] -> IO [a]
combina_planuri [] = return []
combina_planuri (h:t) = do 
    a <- h 
    b <- combina_planuri t 
    return (a:b)

citeste_numar :: IO Int
citeste_numar = readLn 

citeste_2_si_fa_suma :: IO Int 
citeste_2_si_fa_suma = do 
    x <- readLn 
    y <- readLn 
    return (x + y)

newtype Flip f a b = Flip (f b a) deriving (Show)

data LiftItOut f a = LiftItOut (f a) deriving Show
