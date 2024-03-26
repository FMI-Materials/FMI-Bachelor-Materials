import Data.Char

newtype Parser a = Parser { parse :: String -> [(a,String)] }

-- item -> ia primul caracter 
-- porse item "test"
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
  
-- zero -> nu ia nimic
-- parse zero "test"
zero :: Parser a
zero = Parser (const [])

-- psum -> concateneaza rezultatele parserelor
-- parse (psum item item) "test"
psum :: Parser a -> Parser a -> Parser a
psum p q = Parser (\cs -> (parse p cs) ++ (parse q cs))

-- <|> -> ia rezultatul primului parser care nu da [] sau [] daca dau fail toate
-- parse ((string "tes") <|> (takeUntil 'e')) "test"
-- parse ((string "st") <|> (takeUntil 'e')) "test"
-- parse ((string "es") <|> (string "e")) "test"
(<|>) :: Parser a -> Parser a -> Parser a
p <|> q = Parser (\cs -> case parse (psum p q) cs of
                                [] -> []
                                (x:xs) -> [x])

-- dpsum0 -> in cazul in care dau toate parserele fail, in loc de [] intoarce [("", valoare_initiala)]
-- parse (dpsum0 ((string "es") <|> (string "e"))) "test"
dpsum0 :: Parser [a] -> Parser [a]                       
dpsum0 p = p <|> (return [])

-- sat -> ia primul caracter daca indeplineste conditia
-- parse (sat isDigit) "123"
sat :: (Char -> Bool) -> Parser Char
sat p = do
            c <- item
            if p c then return c else zero

-- char -> ia primul caracter, daca este egal cu cel dat ca parametru
-- parse (char '1') "123" 
char :: Char -> Parser Char
char c = sat (c ==)

-- string -> ia prefiul dat ca parametru daca acesta coincide
-- parse (string "12") "123"
-- poate fi combinat cu dpsum0 in caz de fail, pt ca string este o lista
-- parse (dpsum0 (string "23")) "123" 
string :: String -> Parser String
string [] = return []
string (c:cs) = do
                    pc <- char c
                    prest <- string cs
                    return (pc : prest)

-- many0 -> many1 combinat cu dpsum0
-- parse (many0 (char '2')) "1123"
many0 :: Parser a -> Parser [a]
many0 p = dpsum0 (many1 p)

-- many1 -> repeta parser-ul cat timp se poate, dar in caz de fail returneaza []
-- parse (many1 (char '1')) "1123"
many1 :: Parser a -> Parser [a]
many1 p = do 
    a <- p
    aa <- many0 p
    return (a : aa)

-- spaces -> many0 aplicat lui (sat isSpace), adica scoate toate spatiile de la inceput
-- parse spaces "     1123"
spaces :: Parser String
spaces = many0 (sat isSpace)

-- token -> aplica parserul dupa ce au fost eliminate spatiile, si elimina spatiile dintre ce este selectat si ce ramane
-- parse (token (char '1')) "     1123"
-- parse (token (string "11")) "     11   23"
token :: Parser a -> Parser a
token p = do
            spaces
            a <- p
            spaces
            return a

-- symbol -> combina token si string
-- parse (symbol "11") "     11      23     "
symbol :: String -> Parser String
symbol symb = token (string symb)

data AExp = Nu Int | Qid String | PlusE AExp AExp | TimesE AExp AExp | DivE AExp AExp
    deriving Show
    
-- aexp -> parseaza adunarea, inmultirea si impartirea intre primii 2 termeni
-- parse aexp "5*4"
-- parse aexp "(3+4)+(4+5)/5" 
aexp :: Parser AExp
aexp = plusexp <|> mulexp <|> divexp <|> npexp

-- npexp -> parseaza o operatie cu 2 termeni intre paranteze sau un string precedat de ' sau un numar intreg
-- parse npexp "(5+3)"
-- parse npexp "'if"
npexp = parexp <|> qid <|> integer

-- parexp -> parseaza o operatie cu 2 termeni intre parnteze
-- parse parexp "(3+2)+12" 
parexp :: Parser AExp
parexp = do
            symbol "("
            p <- aexp
            symbol ")"
            return p

-- look -> ia primul caracter cu Just si stringul nemodificat, daca exista, altfel returneaza [Nothing, ""]
-- parse look "abcd"
look :: Parser (Maybe Char)
look = Parser (\cs -> case cs of
      [] -> [(Nothing, [])]
      (c:cs') -> [(Just c, c:cs')]
    )

-- digit -> ia primul caracter daca acesta este cifra
-- parse digit "123" 
digit :: Parser Int
digit = do
          d <- sat isDigit
          return (digitToInt d)

-- integer -> ia primul numar natural peste care da, daca acesta apare primul sau are doar spatii in fata
-- parse integer "       123.12"
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

-- qid -> ia primul string precedat de '
-- parse qid "'if x" 
qid :: Parser AExp
qid = do
            char '\''
            a <- many1 (sat isLetter)
            return (Qid a)

-- plusexp -> parseaza adunarea dintre 2 termeni de tip npexp
-- parse plusexp "(3+4)+(5+6)"
plusexp :: Parser AExp
plusexp = do
            p <- npexp
            symbol "+"
            q <- npexp
            return (PlusE p q)

-- mulexp -> parseaza inmultirea dintre 2 termeni de tip npexp
-- parse mulexp "(3+4)*(5+6)" 
mulexp :: Parser AExp
mulexp = do
            p <- npexp
            symbol "*"
            q <- npexp
            return (TimesE p q)

-- divexp parseaza impartirea dintre 2 termeni de tip npexp
-- parse divexp "(3+4)/(5+6)"
divexp :: Parser AExp
divexp = do
            p <- npexp
            symbol "/"
            q <- npexp
            return (DivE p q)


data BExp = BE Bool | LE AExp AExp | NotE BExp | AndE BExp BExp
    deriving Show
    
-- parseaza <=, not si && intre primii 2 termeni
-- parse bexp "3<=4" 
-- parse bexp "(3<=4)&&(4<=5)"
bexp :: Parser BExp
bexp = lexp <|> notexp <|> andexp <|> npexpb

-- npexp -> parseaza o operatie cu 2 termeni intre paranteze sau true/false
-- parse npexpb "(false && true)"
-- parse npexpb "true"
npexpb = parexpb <|> true <|> false

-- parexp -> parseaza o operatie cu 2 termeni intre parnteze
-- parse parexpb "(3<=2)" 
parexpb :: Parser BExp
parexpb = do
            symbol "("
            p <- bexp
            symbol ")"
            return p

-- true -> parseaza true
-- parse true "true&&(3<=2)"
true :: Parser BExp
true = do
            symbol "true"
            return (BE True)

-- false -> parseaza false
-- parse false "false&&(3<=2)"
false :: Parser BExp
false = do
            symbol "false"
            return (BE False)

-- lexp -> parseaza <= dintre 2 termeni de tip npexp
-- parse lexp "(1+2)<=(2+3)"
lexp :: Parser BExp
lexp = do
            p <- npexp
            symbol "<="
            q <- npexp
            return (LE p q)

-- notexp -> parseaza not in fata unui termen de tip npexpb
-- parse notexp "not (1<=3)"
notexp :: Parser BExp
notexp =  do
            symbol "not"
            q <- npexpb
            return (NotE q)

-- notexp -> parseaza && dintre 2 termeni de tip npexpb
-- parse andexp "(not (1<=3)) && (1<=3)"
andexp :: Parser BExp
andexp = do
            p <- npexpb
            symbol "&&"
            q <- npexpb
            return (AndE p q)
          
data Stmt = AtrE String AExp | Seq Stmt Stmt | IfE BExp Stmt Stmt | WhileE BExp Stmt | Skip
    deriving Show

-- stmt -> parseaza una sau mai multe instructiuni separate de ;
stmt :: Parser Stmt
stmt = seqp <|> stmtneseq

-- stmtneseq -> parseaza o instructiune de atribuie, if, while sau skip
-- parse stmtneseq "while ('x<=10) {'x:='x + 1} skip"
stmtneseq :: Parser Stmt
stmtneseq = atre <|> ife <|> whileE <|> skip

-- atre -> parseaza atribuirea unui termen precedat de '
-- parse atre "'x:=5" 
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

-- seqp -> parseaza mai multe instructiuni separate de ;
-- parse seqp "while ('x<=10) {'x:='x + 1}; skip; 'x:=100"
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

-- ife -> parseaza if else
-- parse ife "if ('x<=5) {'x:=10} else {skip}"
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

-- whileE -> parseaza while
-- parse whileE "while ('x<=10) {'x:='x + 1}"
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

-- skip -> parseaza skip
-- parse skip "skip" 
skip :: Parser Stmt
skip = do
          symbol "skip"
          return Skip

sum_no = unlines ["'n:=100; 's:=0;", "while (not ('n<= 0)) { 's:='s+'n; 'n:= 'n+ (-1)} "]

sum_no_p :: Stmt
sum_no_p = (fst.head) (parse stmt sum_no)

inf_cycle = "'n := 0; while (0 <= 0) {'n := 'n +1}"

inf_cycle_p :: Stmt
inf_cycle_p = (fst.head) (parse stmt inf_cycle)

recall :: String -> [(String, Int)] -> Int
recall s ((str, value):xs)
    | s == str = value
    | otherwise = recall s xs

update :: String -> Int -> [(String, Int)] -> [(String, Int)]
update s v [] = [(s, v)]
update s v ((str, value):xs)
    | s == str = (s, v):xs
    | otherwise = (str, value):(update s v xs)

-- data AExp = Nu Int | Qid String | PlusE AExp AExp | TimesE AExp AExp | DivE AExp AExp

value :: AExp -> [(String, Int)] -> Int
value (Nu x) _ = x
value (Qid s) l = recall s l
value (PlusE a b) l = (value a l) + (value b l) 
value (TimesE a b) l = (value a l) * (value b l) 
value (DivE a b) l = (value a l) `div` (value b l) 

-- data BExp = BE Bool | LE AExp AExp | NotE BExp | AndE BExp BExp

valueb :: BExp -> [(String, Int)] -> Bool
valueb (BE x) _ = x
valueb (LE a b) l = (value a l) <= (value b l)
valueb (NotE a) l = not (valueb a l)
valueb (AndE a b) l = (valueb a l) && (valueb b l)

-- data Stmt = AtrE String AExp | Seq Stmt Stmt | IfE BExp Stmt Stmt | WhileE BExp Stmt | Skip

bssos :: Stmt -> [(String, Int)] -> [(String, Int)]
bssos (AtrE st a) l = update st (value a l) l
bssos (Seq st1 st2) l = bssos st2 (bssos st1 l)
bssos (IfE b st1 st2) l
    | valueb b l = bssos st1 l
    | otherwise = bssos st2 l
bssos (WhileE b st) l
    | valueb b l = bssos (Seq st (WhileE b st)) l
    | otherwise = l
bssos Skip l = l

sssos1 :: (Stmt, [(String, Int)]) -> (Stmt, [(String, Int)])
sssos1 (AtrE st a, l) = (Skip, update st (value a l) l)
sssos1 (Seq Skip st, l) = (st, l)
sssos1 (Seq st1 st2, l) = (Seq (fst ans) st2, snd ans)
    where ans = sssos1 (st1, l)
sssos1 (IfE b st1 st2, l)
    | valueb b l = (st1, l)
    | otherwise = (st2, l)
sssos1 (WhileE b st, l) = (IfE b (Seq st (WhileE b st)) Skip, l)

sssos_star :: (Stmt, [(String, Int)]) -> [(Stmt, [(String, Int)])]
sssos_star (s1, s) = (s1, s):(sssos_plus (s1, s))

sssos_plus :: (Stmt, [(String, Int)]) -> [(Stmt, [(String, Int)])]
sssos_plus (Skip, s) = []
sssos_plus (s1, s) = (sssos_star . sssos1) (s1, s)

sssos_final_state :: (Stmt, [(String, Int)]) -> [(String, Int)]
sssos_final_state = snd . last . sssos_star

prog = sum_no_p -- replace this with inf_cycle_p
inits = (prog, [])

test = (sssos_final_state inits) == (bssos prog [])