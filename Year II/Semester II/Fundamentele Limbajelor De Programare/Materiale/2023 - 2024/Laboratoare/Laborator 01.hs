import Data.Char

newtype Parser a = Parser { parse :: String -> [(a,String)] }

item :: Parser Char
item = Parser (\cs -> case cs of
                "" -> []
                (c:cs) -> [(c,cs)])

instance Monad Parser where
    return a = Parser (\cs -> [(a,cs)])
    p >>= f = Parser (\cs -> concat (map (\(a, cs') -> (parse (f a) cs')) (parse p cs)))

instance Applicative Parser where
    pure = return
    mf <*> ma = do
        f <- mf
        va <- ma
        return (f va)    

instance Functor Parser where              
    fmap f ma = pure f <*> ma
  
{-
instance Functor Parser where              
    fmap g p = Parser (\cs -> map (\(a,cs') -> (g a, cs')) (parse p cs))

instance Applicative Parser where
    pure a = Parser (\cs -> [(a, cs)])
    pg <*> pa = Parser (\cs -> concat (map (\(g, cs') -> (parse (fmap g pa) cs')) (parse pg cs)))

instance Monad Parser where
    p >>= f = Parser (\cs -> concat (map (\(a, cs') -> (parse (f a) cs')) (parse p cs)))
-}

zero :: Parser a
zero = Parser (const [])

psum :: Parser a -> Parser a -> Parser a
psum p q = Parser (\cs -> (parse p cs) ++ (parse q cs))

(<|>) :: Parser a -> Parser a -> Parser a
p <|> q = Parser (\cs -> case parse (psum p q) cs of
                                [] -> []
                                (x:xs) -> [x])

dpsum0 :: Parser [a] -> Parser [a]
dpsum0 p = p <|> (return [])

sat :: (Char -> Bool) -> Parser Char
sat p = do
            c <- item
            if p c then return c else zero

char :: Char -> Parser Char
char c = sat (c ==)

string :: String -> Parser String
string [] = return []
string (c:cs) = do
                    pc <- char c
                    prest <- string cs
                    return (pc : prest)

many0 :: Parser a -> Parser [a]
many0 p = dpsum0 (many1 p)

many1 :: Parser a -> Parser [a]
many1 p = do 
    a <- p
    aa <- many0 p
    return (a : aa)

spaces :: Parser String
spaces = many0 (sat isSpace)

token :: Parser a -> Parser a
token p = do
            spaces
            x <- p
            spaces
            return x

symbol :: String -> Parser String
symbol symb = token (string symb)

sepBy0 :: Parser a1 -> Parser a2 -> Parser [a1]
p `sepBy0` sep = dpsum0 (p `sepBy1` sep)

sepBy1 :: Parser a1 -> Parser a2 -> Parser [a1]
p `sepBy1` sep = do
                    a <- p
                    as <- many0 (do
                                    sep
                                    p)
                    return (a:as)

look :: Parser (Maybe Char)
look = Parser (\cs -> case cs of
      [] -> [(Nothing, [])]
      (c:cs') -> [(Just c, c:cs')]
    )

takeUntil :: Char -> Parser [Char]
takeUntil stop = consumeRest "" stop
    where consumeRest acc stop = do
                                    l <- look
                                    if l == Just stop then return [] else do
                                                                            c <- item
                                                                            cs <- consumeRest (acc ++ [c]) stop
                                                                            return (c:cs)

chainl1 :: Parser t -> Parser (t -> t -> t) -> Parser t
p `chainl1` op = do
                    x <- p
                    rest x
                 where rest x = (do
                                    f <- op
                                    y <- p
                                    rest (f x y)
                                ) <|> return x

digit :: Parser Int
digit = do
            d <- sat isDigit
            return (digitToInt d)

integer :: Parser Int
integer = do
              spaces
              d <- digitToInt <$> sat isDigit
              if d == 0 
                then 
                  return 0 
                else 
                  do
                    ds <- many0 digit
                    return (asInt (d:ds))
          where asInt ds = sum [d * (10^p) | (d, p) <- zip (reverse ds) [0..] ]

number :: Parser Double
number = withDecimalPt <|> withoutDecimalPt
  where
    withoutDecimalPt = fromIntegral <$> integer
    withDecimalPt = do
                      wholePart <- withoutDecimalPt
                      char '.'
                      fractionalPart <- fmap asFracPt (many0 digit)
                      return (wholePart + fractionalPart)
    asFracPt ds = sum [fromIntegral d * (10 ** (-p)) | (d, p) <- zip ds [1..]]

addop :: Parser (Double -> Double -> Double)
addop = add <|> sub
  where add = do
                symbol "+"
                return (+)
        sub = do
                symbol "-"
                return (-)

mulop :: Parser (Double -> Double -> Double)
mulop = mul <|> div
  where mul = do
                symbol "*"
                return (*)
        div = do
                symbol "/"
                return (/)

factor :: Parser Double
factor = negativeFactor <|> parensExpr <|> number
  where
    negativeFactor = do
                        symbol "-"
                        negate <$> factor
    parensExpr = do
                    symbol "("
                    x <- expr
                    symbol ")"
                    return x
                    
term :: Parser Double
term = factor `chainl1` mulop

expr :: Parser Double
expr = term `chainl1` addop

--1. Testati parser-ul de mai sus

--2. Creati un tip de date abstract (inductiv) pt expresii aritmetice si modificati parser-ul astfel incat el sa returneze o asemenea expresie

data Expr = Num Double | Add Expr Expr | Sub Expr Expr | Mul Expr Expr | Div Expr Expr | Neg Expr
    deriving (Show)

mulop' :: Parser (Expr -> Expr -> Expr)
mulop' = mul <|> div
  where mul = do
                symbol "*"
                return Mul
        div = do
                symbol "/"
                return Div


addop' :: Parser (Expr -> Expr -> Expr)
addop' = add <|> sub
  where add = do
                symbol "+"
                return Add
        sub = do
                symbol "-"
                return Sub

factor' :: Parser Expr
factor' = negativeFactor <|> parensExpr <|> number'
  where
    negativeFactor = do
                        symbol "-"
                        Neg <$> factor'
    parensExpr = do
                    symbol "("
                    x <- expr'
                    symbol ")"
                    return x
    number' = do
                n <- number
                return (Num n)

term' :: Parser Expr
term' = factor' `chainl1` mulop'

expr' :: Parser Expr
expr' = term' `chainl1` addop'


-- item -> ia primul caracter 
-- porse item "test"

-- zero -> nu ia nimic
-- parse zero "test"

-- psum -> concateneaza rezultatele parserelor
-- parse (psum item item) "test"

-- <|> -> ia rezultatul primului parser care nu da [] sau [] daca dau fail toate
-- parse ((string "tes") <|> (takeUntil 'e')) "test"
-- parse ((string "st") <|> (takeUntil 'e')) "test"
-- parse ((string "es") <|> (string "e")) "test"

-- dpsum0 -> in cazul in care dau toate parserele fail, in loc de [] intoarce [("", valoare_initiala)]
-- parse (dpsum0 ((string "es") <|> (string "e"))) "test"

-- sat -> ia primul caracter daca indeplineste conditia
-- parse (sat isDigit) "123"

-- char -> ia primul caracter, daca este egal cu cel dat ca parametru
-- parse (char '1') "123" 

-- string -> ia prefiul dat ca parametru daca acesta coincide
-- parse (string "12") "123"
-- poate fi combinat cu dpsum0 in caz de fail, pt ca string este o lista
-- parse (dpsum0 (string "23")) "123" 

-- many1 -> repeta parser-ul cat timp se poate, dar in caz de fail returneaza []
-- parse (many1 (char '1')) "1123"

-- many0 -> many1 combinat cu dpsum0
-- parse (many0 (char '2')) "1123"

-- spaces -> many0 aplicat lui (sat isSpace), adica scoate toate spatiile de la inceput
-- parse spaces "     1123"

-- token -> aplica parserul dupa ce au fost eliminate spatiile, si elimina spatiile dintre ce este selectat si ce ramane
-- parse (token (char '1')) "     1123"
-- parse (token (string "11")) "     11   23"

-- symbol -> combina token si string
-- parse (symbol "11") "     11      23     "

-- sepBy1 -> repeta parser-ul cat timp se poate, sarind la fiecare pas peste separatorul dat
-- parse (sepBy1 (sat isDigit) (char ',')) "1,2,3,4"
-- parse (sepBy1 (symbol "11") spaces) "11 11 23"
-- parse (sepBy1 (symbol "11") (symbol "22")) "112211 23"

-- sepBy0 -> sepby1 combinat cu dpsum0
-- parse (sepBy0 (symbol "11") (symbol "33")) "12211 23"

-- look -> ia primul caracter cu Just si stringul nemodificat, daca exista, altfel returneaza [Nothing, ""]
-- parse look "abcd"

-- takeUntil -> ia din string pana la prima aparitie a caracterului dat
-- parse (takeUntil 'a') "bbbac"

-- chainl1 -> aplica o operatie asupra tuturor elementelor selectate
-- parse (chainl1 number addop) "1+2+3"

-- digit -> ia primul caracter daca acesta este cifra
-- parse digit "123" 

-- integer -> ia primul numar natural peste care da, daca acesta apare primul sau are doar spatii in fata
-- parse integer "       123.12"

-- number -> ia primul numar real pozitiv peste care da, daca acesta apare primul sau are doar spatii in fata
-- parse number "          1234.13" 

-- addop -> operatiile de adunare si scadere parsate, se foloseste cu chainl1
--  parse (chainl1 number addop) "1+2-3"

-- mulop -> operatiile de inmultire si impartire parsate, se foloseste cu chainl1
-- parse (chainl1 number mulop) "1*3/2" 

-- factor -> ia primul factor al unei expresii, facand calculele necesare in caz de - sau ()
-- parse factor "-(2+3)+12-23"
-- parse factor "(2+3)" 
-- parse factor "-2" 

-- term -> calculeaza termenul aplicand inmultirile si impartirile asupra factorilor
-- parse term "2*3/4*6+12*12"  

-- expr -> calculeaza expresia aplicand adunarile si scaderole asupra termenilor
-- parse expr "-(2+3)*(10-5)+(21-12)*9"