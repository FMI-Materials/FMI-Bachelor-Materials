putChar :: Char -> IO ()

getChar :: IO Char

toUpper :: Char -> Char


(toUpper <$> getChar) >>= putChar
===
getChar >>= \c -> putChar (toUpper c)



getResult :: IO a -> a




getResult getChar
"abc"
'a'

"xyz"
'x'



getLine =
  getChar >>= \x ->
    if x == '\n'
      then return []
      else (x:) <$> getLine




getLine :: IO String
getLine
  = do
    x <- getChar
    if x == '\n' then return []
    else do
         xs <- getLine
         return (x : xs)


echo
  = do
    line <- getLine
    if line == "" then return ()
    else do
         putStrLn (map toUpper line)
         echo


class Functor m => Applicative m where

class Applicative m => Monad m where



fmap f ca
  = do
    x <- ca
    return (f x)

cf <*> ca
  = do
    f <- cf
    x <- ca
    return (f x)

pure = return 




Parser a = Parser { apply :: String -> [(a, String)] }


MyIO a = MyIO { runIO :: String -> (a, String, String) }

getChar :: MyIO Char
getChar = MyIO (\s -> (head s, tail s, ""))

putChar :: Char -> MyIO ()
putChar c = MyIO (\s -> ( (), s, [c])


