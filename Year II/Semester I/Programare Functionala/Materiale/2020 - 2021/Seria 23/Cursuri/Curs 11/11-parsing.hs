import Data.Char
import Data.List (intercalate)
import Control.Applicative

newtype Parser a = Parser { apply :: String -> [(a, String)] }

satisfy :: (Char -> Bool) -> Parser Char
satisfy p = Parser f
  where
  f []                 = []
  f (c:s) | p c        = [(c, s)]
          | otherwise = []

parse :: Show a => Parser a -> String -> a
parse m s = case parses of
    [] -> error "No valid parse."
    [a] -> a
    l -> error ("Ambiguity. Possible parses: \n\t" ++ intercalate "\n\t" (map show l))
  where
    parses = [ x | (x,t) <- apply m s, t == "" ]

instance Functor Parser where
  fmap f p =
    Parser
      (\s -> [(f a, r) | (a, r) <- apply p s])

instance Applicative Parser where
  pure a = Parser (\s -> [(a, s)])
  pf <*> pa =
      Parser
          (\s -> [(f a, r) | (f, rf) <- apply pf s
                           , (a, r) <- apply pa rf ])

instance Alternative Parser where
  empty = Parser (\s -> [])
  pa <|> pb = Parser (\s -> apply pa s ++ apply pb s)

-- Recunoasterea unui anumit caracter
char :: Char -> Parser Char
char c = satisfy (== c)

-- Recunoasterea unui caracter oarecare
anyChar :: Parser Char
anyChar = satisfy (const True)

skipSpace :: Parser ()
skipSpace = many (satisfy isSpace) *> pure ()

token :: Parser a -> Parser a
token p = skipSpace *> p <* skipSpace

string :: String -> Parser String
string []      = pure []
string (x:xs) = pure (:) <*> char x <*> string xs

sepBy1 :: Parser item -> Parser sep -> Parser [item]
sepBy1 pItem pSep =
    pure (:) <*> pItem <*> many (pSep *> pItem)

parseId :: (Char -> Bool) -> (Char -> Bool) -> Parser String
parseId pFirst pNext =
    pure (:) <*> satisfy pFirst <*> many (satisfy pNext)

parseNat :: Parser Int
parseNat = read <$> some (satisfy isDigit)

-- Recunoasterea unui numar negativ
parseNeg :: Parser Int
parseNeg =  char '-' *> (negate <$> parseNat)

-- Recunoasterea unui numar intreg
parseInt :: Parser Int
parseInt = parseNat <|> parseNeg

data Exp = Lit Int
         | Add Exp Exp
         | Mul Exp Exp
         deriving (Eq,Show)

evalExp   :: Exp -> Int
evalExp   (Lit n)    = n
evalExp   (Add e f) = evalExp e + evalExp f
evalExp   (Mul e f) = evalExp e * evalExp f


parseExp :: Parser Exp
parseExp = parseTerm
    <|> pure Add <*> parseTerm <* token (char '+') <*> parseExp
  where
    parseTerm = parseFactor
        <|> pure Mul <*> parseFactor <* token (char '*') <*> parseTerm
    parseFactor = Lit <$> parseInt
        <|> char '(' *> skipSpace *> parseExp <* skipSpace <* char ')'

