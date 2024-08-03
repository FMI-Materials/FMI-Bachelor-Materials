import Data.Char

prelStr strin = map toUpper strin

ioString = do
           strin <- getLine
           putStrLn $ "Intrare\n" ++ strin
           let  strout = prelStr strin
           putStrLn $ "Iesire\n" ++ strout

prelNo noin = sqrt noin

ioNumber = do
           noin <- readLn :: IO Double
           putStrLn $ "Intrare\n" ++ (show noin)
           let  noout = prelNo noin
           putStrLn $ "Iesire"
           print noout

inoutFile = do
              sin <- readFile "Input.txt"
              putStrLn $ "Intrare\n" ++ sin
              let sout = prelStr sin
              putStrLn $ "Iesire\n" ++ sout
              writeFile "Output.txt" sout

readPerson :: IO (String, Int)
readPerson = do
    nume <- getLine
    varsta <- readLn
    return (nume, varsta)

printPeople [] = ""
printPeople (h:t) = (fst h) ++ " (" ++ (show $ snd h) ++ " ani)\n" ++ printPeople t

getMaxAge l = maximum [x | x <- l]

theOldest = do
            num <- readLn :: IO Int
            people <- sequence (replicate num readPerson)          
            let maxAge = maximum $ fmap snd people
            let peopleMaxAge = [x | x<- people, (snd x) == maxAge]
            if length peopleMaxAge > 1 then
                putStrLn "Cei mai in varsta sunt: "
            else
                putStrLn "Cel mai in varsta este: "
            putStrLn $ printPeople peopleMaxAge

readPersonComma :: String -> (String, Int)
readPersonComma s = (nume, read varsta)
  where
    (nume, ',':' ':varsta) = break (== ',') s

readPersons :: String -> [(String, Int)]
readPersons = map readPersonComma . lines

theOldest2 = do
            people <- readPersons <$> readFile "ex2.in"          
            let maxAge = maximum $ fmap snd people
            let peopleMaxAge = [x | x<- people, (snd x) == maxAge]
            if length peopleMaxAge > 1 then
                putStrLn "Cei mai in varsta sunt: "
            else
                putStrLn "Cel mai in varsta este: "
            putStrLn $ printPeople peopleMaxAge 

type Input = String
type Output = String
 
newtype MyIO a = MyIO { runIO :: Input -> (a, Input, Output)}

myGetChar :: MyIO Char
myGetChar = MyIO (\(f:t) -> (f, t, ""))
 
testMyGetChar :: Bool
testMyGetChar = runIO myGetChar "Ana" == ('A', "na", "")
 
myPutChar :: Char -> MyIO ()
myPutChar c = MyIO (\i -> ((), i, [c]))
 
testMyPutChar :: Bool
testMyPutChar = runIO (myPutChar 'C') "Ana" == ((), "Ana", "C")

instance Functor MyIO where
--   fmap f (MyIO a) = MyIO (f a)
testFunctorMyIO :: Bool
testFunctorMyIO = runIO (fmap toUpper myGetChar) "ana" == ('A', "na", "")

instance Applicative MyIO where
 
testPureMyIO :: Bool
testPureMyIO = runIO (pure 'C') "Ana" == ('C', "Ana", "")
 
testApMyIO :: Bool
testApMyIO = runIO (pure (<) <*> myGetChar <*> myGetChar) "Ana" == (True, "a", "")

instance Monad MyIO where
 
testBindMyIO :: Bool
testBindMyIO = runIO (myGetChar >>= myPutChar) "Ana" == ((), "na", "A")

main = undefined
