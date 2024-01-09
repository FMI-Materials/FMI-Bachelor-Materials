{- 
class Functor f where 
     fmap :: (a -> b) -> f a -> f b 
class Functor f => Applicative f where
    pure :: a -> f a
    (<*>) :: f (a -> b) -> f a -> f b

Just length <*> Just "world"

Just (++" world") <*> Just "hello,"
pure (+) <*> Just 3 <*> Just 5
pure (+) <*> Just 3 <*> Nothing
(++) <$> ["ha","heh"] <*> ["?","!"]
-}

-- 1
data List a
    = Nil
    | Cons a (List a)
    deriving (Eq, Show)

instance Functor List where
    fmap _ Nil = Nil
    fmap f (Cons a list) = (Cons (f a) (fmap f list))

instance Applicative List where
    pure a = (Cons a Nil)
    (<*>) Nil _ = Nil
    (<*>) (Cons f g) l = flattenCons (fmap f l) (g <*> l)
                         where flattenCons Nil x = x
                               flattenCons (Cons a b) x = Cons a (flattenCons b x)

f = Cons (+1) (Cons (*2) Nil)
v = Cons 1 (Cons 2 Nil)
test :: List Int
test = (f <*> v)

-- 2
data Cow 
    = Cow 
    {
        name :: String, 
        age :: Int, 
        weight :: Int
    } 
    deriving (Eq, Show)

-- a
noEmpty :: String -> Maybe String
noEmpty "" = Nothing
noEmpty s = Just s

noNegative :: Int -> Maybe Int
noNegative x
    | x < 0 = Nothing
    | otherwise = Just x

test21 = noEmpty "abc" == Just "abc"
test22 = noNegative (-5) == Nothing 
test23 = noNegative 5 == Just 5

-- b
{- 
cowFromString :: String -> Int -> Int -> Maybe Cow
cowFromString s a b 
  | ((noEmpty s) == Just s) && ((noNegative a) == Just a) && ((noNegative b) == Just b) = Just (Cow s a b)
  | otherwise = Nothing
-}

test24 = cowFromString "Milka" 5 100 == Just (Cow {name = "Milka", age = 5, weight = 100})

-- c
cowFromString :: String -> Int -> Int -> Maybe Cow
cowFromString s a b = Cow <$> noEmpty s <*> noNegative a <*> noNegative b

-- 3
newtype Name = Name String deriving (Eq, Show)
newtype Address = Address String deriving (Eq, Show)

data Person 
    = Person Name Address
    deriving (Eq, Show)

-- a
validateLength :: Int -> String -> Maybe String
validateLength x s
  | (length s) < x = Just s
  | otherwise = Nothing

test31 = validateLength 5 "abc" == Just "abc"

-- b
{-
mkName :: String -> Maybe Name
mkName s
  | (validateLength 26 s) == Just s = Just (Name s)
  | otherwise = Nothing

mkAddress :: String -> Maybe Address
mkAddress s
  | (validateLength 101 s) == Just s = Just (Address s)
  | otherwise = Nothing
-}

-- c
{-
mkPerson :: String -> String -> Maybe Person
mkPerson name address
  | (mkName name == Just (Name name)) && (mkAddress address == Just (Address address)) = Just (Person (Name name) (Address address))
  | otherwise = Nothing 
-}

-- d
mkName :: String -> Maybe Name
mkName s = Name <$> validateLength 26 s

mkAddress :: String -> Maybe Address
mkAddress s = Address <$> validateLength 101 s

mkPerson :: String -> String -> Maybe Person
mkPerson name address = Person <$> mkName name <*> mkAddress address

test32 = mkName "Gigel" ==  Just (Name "Gigel")
test33 = mkAddress "Str Academiei" ==  Just (Address "Str Academiei")
test34 = mkPerson "Gigel" "Str Academiei" == Just (Person (Name "Gigel") (Address "Str Academiei"))
