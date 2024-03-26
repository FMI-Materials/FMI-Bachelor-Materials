{-# LANGUAGE TypeSynonymInstances #-}
{-# LANGUAGE FlexibleInstances #-}
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
            a <- p
            spaces
            return a

symbol :: String -> Parser String
symbol symb = token (string symb)

data AExp = Nu Int | Qid String | PlusE AExp AExp | TimesE AExp AExp | DivE AExp AExp
    deriving Show
    
aexp :: Parser AExp
aexp = plusexp <|> mulexp <|> divexp <|> npexp

npexp = parexp <|> qid <|> integer

parexp :: Parser AExp
parexp = do
            symbol "("
            p <- aexp
            symbol ")"
            return p

look :: Parser (Maybe Char)
look = Parser (\cs -> case cs of
      [] -> [(Nothing, [])]
      (c:cs') -> [(Just c, c:cs')]
    )

digit :: Parser Int
digit = do
          d <- sat isDigit
          return (digitToInt d)

integer :: Parser AExp
integer = do
                  spaces
                  s <- look
                  ss <- do
                            if s == (Just '-') then
                                                  do
                                                    item
                                                    return (-1)
                                               else return 1
                  d <- digitToInt <$> sat isDigit
                  if d == 0 
                    then 
                      return (Nu 0)
                    else 
                      do
                        ds <- many0 digit
                        return (Nu (ss*(asInt (d:ds))))
          where asInt ds = sum [d * (10^p) | (d, p) <- zip (reverse ds) [0..] ]

qid :: Parser AExp
qid = do
            char '\''
            a <- many1 (sat isLetter)
            return (Qid a)

plusexp :: Parser AExp
plusexp = do
            p <- npexp
            symbol "+"
            q <- npexp
            return (PlusE p q)

mulexp :: Parser AExp
mulexp = do
            p <- npexp
            symbol "*"
            q <- npexp
            return (TimesE p q)

divexp :: Parser AExp
divexp = do
            p <- npexp
            symbol "/"
            q <- npexp
            return (DivE p q)


data BExp = BE Bool | LE AExp AExp | NotE BExp | AndE BExp BExp
    deriving Show
    
bexp :: Parser BExp
bexp = lexp <|> notexp <|> andexp <|> npexpb

npexpb = parexpb <|> true <|> false

parexpb :: Parser BExp
parexpb = do
            symbol "("
            p <- bexp
            symbol ")"
            return p

true :: Parser BExp
true = do
            symbol "true"
            return (BE True)

false :: Parser BExp
false = do
            symbol "false"
            return (BE False)

lexp :: Parser BExp
lexp = do
            p <- npexp
            symbol "<="
            q <- npexp
            return (LE p q)

notexp :: Parser BExp
notexp =  do
            symbol "not"
            q <- npexpb
            return (NotE q)

andexp :: Parser BExp
andexp = do
            p <- npexpb
            symbol "&&"
            q <- npexpb
            return (AndE p q)
          
data Stmt = Skip | AtrE String AExp | Seq Stmt Stmt | IfE BExp Stmt Stmt | WhileE BExp Stmt
    deriving Show

stmt :: Parser Stmt
stmt = seqp <|> stmtneseq

stmtneseq :: Parser Stmt
stmtneseq = atre <|> ife <|> whileE <|> skip

atre :: Parser Stmt
atre = do
            spaces
            y <- qid
            case y of
                (Qid x) -> do
                            symbol ":="
                            a <- aexp
                            spaces
                            return (AtrE x a)
                _ -> zero

seqp :: Parser Stmt
seqp = do
            x <- stmtneseq
            rest x
      where rest x = (
                     do
                        symbol ";"
                        y <- stmtneseq
                        rest (Seq x y)
                     )
                     <|> return x

ife :: Parser Stmt
ife = do
          symbol "if"
          symbol "("
          b <- bexp
          symbol ")"
          symbol "{"
          s1 <- stmt
          symbol "}"
          symbol "else"
          symbol "{"
          s2 <- stmt
          symbol "}"
          return (IfE b s1 s2)

whileE :: Parser Stmt
whileE =  do
              symbol "while"
              symbol "("
              b <- bexp
              symbol ")"
              symbol "{"
              s1 <- stmt
              symbol "}"
              return (WhileE b s1)

skip :: Parser Stmt
skip = do
          symbol "skip"
          return Skip

sum_no = "'n:=100; 's:=0; 'i:=0; while ( ('i<= 'n)) { 's:='s+'i; 'i:= 'i+1} "

sum_no_p :: Stmt
sum_no_p = (fst.head) (parse stmt sum_no)

inf_cycle = "'n := 0; while (0 <= 0) {'n := 'n +1}"

inf_cycle_p :: Stmt
inf_cycle_p = (fst.head) (parse stmt inf_cycle)

recall :: String -> [(String, Int)] -> Int
recall s ((t,v):xs) = if t == s then v else recall s xs

update :: String -> Int -> [(String, Int)] -> [(String, Int)]
update s v [] = [(s,v)]
update s v ((t,w):xs) = if t==s then ((s,v):xs) else ((t,w):(update s v xs))

value :: AExp -> [(String, Int)] -> Int
value (Nu n) _ = n
value (Qid t) s = recall t s
value (PlusE e1 e2) s = (value e1 s) + (value e2 s)
value (TimesE e1 e2) s = (value e1 s) * (value e2 s)
value (DivE e1 e2) s = div (value e1 s) (value e2 s)

valueb :: BExp -> [(String, Int)] -> Bool
valueb (BE b) _ = b
valueb (LE e1 e2) s = (value e1 s) <= (value e2 s)
valueb (NotE e) s = not (valueb e s)
valueb (AndE e1 e2) s = (valueb e1 s) && (valueb e2 s)

bssos :: Stmt -> [(String, Int)] -> [(String, Int)]
bssos Skip s = s
bssos (AtrE t e) s = update t (value e s) s
bssos (Seq s1 s2) s = bssos s2 (bssos s1 s)
bssos (IfE be s1 s2) s = if (valueb be s) then (bssos s1 s) else (bssos s2 s)
bssos (WhileE be s1) s = if (valueb be s) then (bssos (WhileE be s1) (bssos s1 s)) else s

prog = sum_no_p

test_bssos = bssos prog []

-- This is where the new stuff starts

-- substitutes the Qid with the string by the arithmetic expression
substaexp :: AExp -> String -> AExp -> AExp
substaexp (Nu x) _ _ = (Nu x)
substaexp (Qid s) s1 a 
  | s == s1 = a
  | otherwise = (Qid s)
substaexp (PlusE e1 e2) s a = PlusE (substaexp e1 s a) (substaexp e2 s a)
substaexp (TimesE e1 e2) s a = TimesE (substaexp e1 s a) (substaexp e2 s a)
substaexp (DivE e1 e2) s a = DivE (substaexp e1 s a) (substaexp e2 s a)

data Assn = BEX Bool | LEX AExp AExp | NotEX Assn | AndEX Assn Assn | DisjInfX [Assn]

-- value of an assertion relative to a state, similar to valueb
valueassn :: Assn -> [(String, Int)] -> Bool
valueassn (BEX b) _ = b
valueassn (LEX e1 e2) s = (value e1 s) <= (value e2 s)
valueassn (NotEX e) s = not (valueassn e s)
valueassn (AndEX e1 e2) s = (valueassn e1 s) && (valueassn e2 s)
valueassn (DisjInfX l) s = foldr (||) False (map (\x -> valueassn x s) l)

-- converts a boolean expression to an assertion
convassn :: BExp -> Assn
convassn (BE b) = (BEX b)
convassn (LE e1 e2) = (LEX e1 e2)
convassn (NotE e) = NotEX (convassn e)
convassn (AndE e1 e2) = AndEX (convassn e1) (convassn e2)

-- substitutes the Qid with the string by the arithmetic expression
substassn :: Assn -> String -> AExp -> Assn
substassn (BEX b) _ _ = (BEX b)
substassn (LEX e1 e2) s a = LEX (substaexp e1 s a) (substaexp e2 s a)
substassn (NotEX e) s a = NotEX (substassn e s a)
substassn (AndEX e1 e2) s a = AndEX (substassn e1 s a) (substassn e2 s a)
substassn (DisjInfX l) s a = DisjInfX (map (\x -> substassn x s a) l)

-- logical or
orx :: Assn -> Assn -> Assn
orx p q = NotEX (AndEX (NotEX p) (NotEX q))

-- extracts the list
extr :: Assn -> [Assn]
extr (DisjInfX li) = li

-- computes the weakest precondition
wp :: Stmt -> Assn -> Assn
wp Skip as = as
wp (AtrE s a) as = substassn as s a
wp (Seq s1 s2) as = wp s1 (wp s2 as)
wp (IfE b s1 s2) as = orx (AndEX (convassn b) (wp s1 as)) (AndEX (convassn (NotE b)) (wp s2 as))
wp (WhileE b s1) as = DisjInfX [precondition i | i<-[0..]] 
                        where precondition 0 = AndEX (convassn (NotE b)) as
                              precondition k = AndEX (convassn b) (wp s1 (precondition (k-1)))

test1 = valueassn (wp prog (LEX (Qid "s") (Nu 5051))) [] -- should return true

test2 = valueassn (wp prog (LEX (Qid "s") (Nu 5050))) [] -- should return true

test3 = valueassn (wp prog (LEX (Qid "s") (Nu 5049))) [] -- should not terminate
