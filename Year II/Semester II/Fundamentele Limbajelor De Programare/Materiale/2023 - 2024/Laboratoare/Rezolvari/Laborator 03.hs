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

--This is where the new stuff starts

factorial :: Integer -> Integer
factorial n = if n==0 then 1 else n * (factorial (n-1))

fix :: (a -> a) -> a
fix f = f (fix f)

factorialf :: Integer -> Integer
factorialf = fix (\f n -> if n==0 then 1 else n * (f (n-1)))

ackermannf :: Integer -> Integer -> Integer
ackermannf = fix (\f m n -> if m == 0 then n + 1 else if n == 0 then (f (m-1) 1) else (f (m-1) (f m (n-1))))

data Peano = Zero | Succ Peano deriving Show

evenp Zero = True
evenp (Succ n) = oddp n
oddp Zero = False
oddp (Succ n) = evenp n

evenoddf :: Peano -> (Bool, Bool)
evenoddf = fix (\f m -> case m of
                                Zero -> (True, False)
                                Succ n -> let (x, y) = (f n) in (y, x))

testevenoddf = evenoddf (Succ (Succ (Succ Zero))) == (False, True)

denot :: Stmt -> [(String, Int)] -> [(String, Int)]
denot Skip = id
denot (AtrE t e) = \s -> update t (value e s) s
denot (Seq s1 s2) = (denot s2) . (denot s1)
denot (IfE be s1 s2) = \s -> if (valueb be s) then (denot s1 s) else (denot s2 s)
denot (WhileE be s1) = fix (\f -> (\s -> (if (valueb be s) then (f (denot s1 s)) else s)))

prog = sum_no_p

test_denot = (bssos prog []) == (denot prog [])

--Now general stuff starts

type Algebra f a = f a -> a

newtype Fix f = Fx (f (Fix f))
-- :k Fix

unFix :: Fix f -> f (Fix f)
unFix (Fx x) = x

catamorphism :: Functor f => (f a -> a) -> (Fix f -> a)
catamorphism a = fix (\f -> a . (fmap f). unFix)
-- this is the unique initial algebra morphism

-- Now specific stuff for propositional logic

data ExprBoolF a = Var String | Neg a | Implies a a deriving Show
-- :k ExprBoolF

instance Functor ExprBoolF where
    fmap eval (Var v) = Var v
    fmap eval (Neg phi) = Neg (eval phi)
    fmap eval (Implies phi psi) = Implies (eval phi) (eval psi)

type ExprBoolFix = Fix ExprBoolF
-- :k ExprBool

instance Show ExprBoolFix where
    show (Fx a) = "(Fx (" ++ show a ++ "))"

sampleExpr :: ExprBoolFix
sampleExpr = Fx (Implies (Fx (Var "a")) (Fx (Var "b")))

type TargetBoolAlgebra = Algebra ExprBoolF ((String -> Bool) -> Bool)

impl :: Bool -> Bool -> Bool
impl a b = (not a) || b

alg :: TargetBoolAlgebra
alg (Var v) = ($ v)
alg (Neg x) = not . x
alg (Implies x y) = \e -> impl (x e) (y e)

sampleEval :: String -> Bool
sampleEval "a" = True
sampleEval "b" = False

test = catamorphism alg sampleExpr sampleEval == False

-- Now specific stuff for IMP
          
data StmtF a = AtrEF String AExp | SeqF a a | IfEF BExp a a | WhileEF BExp a | SkipF deriving Show

type StmtFix = Fix StmtF

instance Show StmtFix where
    show (Fx a) = "(Fx (" ++ show a ++ "))"

instance Functor StmtF where
    fmap eval SkipF = SkipF
    fmap eval (AtrEF t e) = AtrEF t e
    fmap eval (SeqF s1 s2) = SeqF (eval s1) (eval s2)
    fmap eval (IfEF be s1 s2) = IfEF be (eval s1) (eval s2)
    fmap eval (WhileEF be s1) = WhileEF be (eval s1)

type TargetStmtAlgebra = Algebra StmtF ([(String, Int)] -> [(String, Int)])

algs :: TargetStmtAlgebra
algs SkipF = id
algs (AtrEF t e) = \s -> update t (value e s) s
algs (SeqF s1 s2) = s2 . s1
algs (IfEF be s1 s2) = \s -> if (valueb be s) then (s1 s) else (s2 s)
algs (WhileEF be s1) = fix (\f -> (\s -> (if (valueb be s) then (f (s1 s)) else s)))

-- Here we do a hack
convstmt :: Stmt -> StmtFix
convstmt Skip = Fx SkipF
convstmt (AtrE t e) = Fx (AtrEF t e)
convstmt (Seq s1 s2) = Fx (SeqF (convstmt s1) (convstmt s2))
convstmt (IfE be s1 s2) = Fx (IfEF be (convstmt s1) (convstmt s2))
convstmt (WhileE be s1) = Fx (WhileEF be (convstmt s1))

progf :: StmtFix
progf = convstmt prog

testf = catamorphism algs progf []
