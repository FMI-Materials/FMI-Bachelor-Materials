

data Figura a = Dreptunghi a a a a
	     | Cerc a a a
	     | Patrat a a a


Dreptunghi			Cerc			Patrat
Int * Int * Int * Int    +     Int * Int * Int     +    Int * Int * Int


arie :: (Num a, Integral a) => Figura a -> Double
aria (Dreptunghi x y lung lat) = fromIntegral (lung * lat)


Prelude> :t (Dreptunghi "sus" "jos" "mare" "mic")
Figura [Char]


data IntInf
  = IntInf Int
  | Infinit


data () = ()

data Unit = Unit

data Void =


updateAge :: Person -> Int -> Person
updateAge (Person prenume nume _ inaltime telefon) varsta
  = Person prenume nume varsta inaltime telefon

showName :: Person -> String
showName p = fistName p ++ " " ++ lastName p

-- showName (Person { firstName = f; lastName = l }) = f ++ " " ++ l


head :: [a] -> a

safeHead :: [a] -> Maybe a
safeHead [] = Nothing
safeHead (x:_) = Just x
-- safeHead l = Just (head l)

tail :: [a] -> [a]

safeTail :: [a] -> Maybe [a]
safeTail [] = Nothing
safeTail (_:tl) = Just tl
-- safeTail l = Just (tail l)


utilizare safe

divide :: Int -> Int -> Maybe Int
safe :: Int -> Int -> Maybe Int
safe x y =
  case x `divide` y of
  | Nothing -> Nothing
  | Just d -> Just (d + 3)
  









