# Haskell CheatSheet

## Stuff to know

1. Types and Constructors ALWAYS start with an uppercase
2. Functions ALWAYS start with a lowercase
3. `Foldr` can be used on infinite lists but `foldl` can't
4. `:i Eq` gives informations on the `Eq` typeclass
5. Solutions can be:
    * Descriptive: list comprehension
    * Recursive: recursivity
    * Higher order: `map`, `filter`, `fold` etc.
6. `:browse Data.List` pt informatii.

## Writting `map`, `filter` and `fold` with recursion

``` haskell
map' :: (a -> b) -> [a] -> [b]
map' _ [] = []
map' f (h:t) = f h : map' f t

filter' :: (a -> Bool) -> [a] -> [a]
filter' _ [] = []
filter' f (h:t) =
    if f h then
        h : filter' f t
    else
        filter' f t

foldr' :: (a -> b -> b) -> b -> [a] -> b
foldr' _ acc [] = acc
foldr' f acc (h:t) =
    let new_acc = foldr' f acc t in
    f h new_acc

foldl' :: (b -> a -> b) -> b -> [a] -> b
foldl' _ acc [] = acc
foldl' f acc (h:t) =
    foldl' f (f acc h) t
```

## Writting `map` and `filter` with list comprehension

``` haskell
map' :: (a -> b) -> [a] -> [b]
map' f l = [f x | x <- l]

filter' :: (a -> Bool) -> [a] -> [a]
filter' f l = [x | x <- l, f x]
```

## Writting `map` and `filter` with `foldr`

``` haskell
map' :: (a -> b) -> [a] -> [b]
map' f = foldr (\x acc -> f x : acc) []

filter' :: (a -> Bool) -> [a] -> [a]
filter' f = foldr (\x acc -> if f x then x : acc else acc) []
```

## Defining Type Synonims

``` haskell
type IntList = [Int]

my_list = read "[1, 2, 3]" :: IntList
```

## Defining own Types

``` haskell
data Tree a
    = EmptyNode
    | Node a [Tree a]
    deriving (Show, Eq)

my_tree = Node 10 [Node 4 [], EmptyNode]

data Car = Car
    { name :: String
    , year :: Int
    } deriving (Show)

my_car = Car "Dacia" 2000
my_car2 = Car { name="Dacia", year=2000 }
car_age = year my_car2
```

## Including type in Typeclass

``` haskell
data Lista a = Gol | Lista a (Lista a)

instance (Show a) => Show (Lista a) where
    show Gol = ""
    show (Lista a l) = show a ++ " " ++ show l
```

## Creating new typeclases

``` haskell
class MyEq a where
    (===) :: a -> a -> Bool
    (/==) :: a -> a -> Bool
    x === y = not (x /== y)
    x /== y = not (x === y)
```

## Cusom operators

Operators have a `fixity`.
Basic operators are:
1. `infixl 7 *`
2. `infixl 6 +`
3. `infixr 0 $`

For defining own operators:
``` haskell
infixr 5 :-:  
data List a
    = Empty
    | a :-: (List a)
    deriving (Show, Read, Eq, Ord)  

infixl 9 -=
(-=) :: Int -> Int -> Int
0 -= _ = 0
a -= b = a + b
```

## Case Expressions

``` haskell
tellVar :: Maybe Int -> String
tellVar m =
    case m of
        Just x -> "Value is " ++ show x
        otherwise -> "Nope"

tellVar $ Just 10 -- returns "Value is 10"
tellVar Nothing   -- returns "Nope"
```

## QuickCheck

``` haskell
import Test.QuickCheck

prop :: Int -> Int -> Bool
prop a b = (a + b) == (b + a)

quickCheck prop
```

## Specify type within function

``` haskell
mapTimes2 :: [Int] -> [Int]
mapTimes2 =
    let mul2 :: Int -> Int
        mul2 x = 2 * x in
    map mul2
```

## Lista de functii utile

| Nume      | Descriere         | Inclus 
| --------- | ------------      | ---------
| `elem`    | x exista in lista | `Prelude`
| `isDigit` | este digit        | `Data.Char`
| `isUpper` | este litara mare  | `Data.Char`
| `isLower` | este litera mica  | `Data.Char`
| `isAlpha` | este litera       | `Data.Char`
|`isAphaNum`| este litera/cifra | `Data.Char`
| `toLower` | face litera mica  | `Data.Char`
| `toUpper` | face litera mare  | `Data.Char`
| `and`     | vectorul are true | `prelude`
| `all`     | verifica o conditie| `prelude`
| `any`     | verifica o conditie| `prelude`
| `lookup`  | daca a e in [(a, b)] | `prelude`
| `partition` | splituieste dupa o conditie | `Data.List`
| `ord, chr` | int <-> char     | `Data.Char`
| `toList`  | transforma intr-o lista | `Data.Foldable`
| `when`    | conditie in do       | `Control.Monad`
| `words`   | sparge in cuvinte   | `prelude`

## Typeclasses

```hs
data Container a
    = Data a [String]
    | Error String

instance Foldable Container where
    foldMap f (Error _) = mempty 
    foldMap f (Data a _) = f a

instance Eq a => Eq (Container a) where
    (Error _) == (Error _) = True
    (Data a _) == (Data b _) = a == b
    _ == _ = False

instance Show a => Show (Container a) where
    show (Error s) = "Error: " ++ s
    show (Data a logs) =
        "Data: " ++ show a ++ "\nlogs: " ++ show logs


-- Monad, and then rest 
instance Monad Container where
    return a = Data a []
    (Error s) >>= f = Error s
    (Data a logs) >>= f =
        case f a of
            Error e -> Error e
            Data b logs2 -> Data b (logs ++ ["Apply monad"] ++ logs2)

instance Functor Container where
    fmap f container = do
        a <- container
        return $ f a

instance Applicative Container where
    pure = return
    c1 <*> c2 = do
        f <- c1
        a <- c2
        return $ f a
```

## IO

```hs
readstuff :: IO ()
readstuff = do
    n <- read <$> getLine
    when (n < 10) $ do
        print "Ce penal!"
        print "haha"
    print $ "You said " ++ show n
```

## Random

```hs
import Test.QuickCheck

import System.Random

a :: StdGen
a = mkStdGen 10

(rnd, a') = random a :: (Int, StdGen)

infiniteRange = randomRs (1, 100) a' :: [Int]

prop :: Int -> Bool
prop x = maximum (take (abs x + 1) infiniteRange) <= 100

z = quickCheck prop
```
