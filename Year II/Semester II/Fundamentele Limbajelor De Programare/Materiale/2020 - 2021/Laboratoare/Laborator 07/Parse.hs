module Parse where

import AST
import Text.Parsec.String ( Parser, parseFromFile )
import Text.Parsec.Expr
    ( buildExpressionParser,
      Assoc(..),
      Operator(..) )
import Text.ParserCombinators.Parsec.Language
    ( emptyDef,
      GenLanguageDef( .. ),
      LanguageDef)
import Text.Parsec ( alphaNum, letter, (<|>), eof )
import qualified Text.Parsec.Token as Token

impLanguageDef :: LanguageDef ()
impLanguageDef =
    emptyDef
    { commentStart = "/*"
    , commentEnd = "*/"
    , commentLine  = "//"
    , nestedComments = False
    , caseSensitive = True
    , identStart = letter
    , identLetter = alphaNum
    , reservedNames =
        [ "while"
        , "if"
        , "else"
        , "true"
        , "false"
        , "read"
        , "print"
        , "var"
        ]
    , reservedOpNames =
        [ "+", "-", "*", "/", "%"
        , "==", "!="
        , "<", "<=", ">=", ">"
        , "&&", "||", "!"
        , "="
        ]
    }

impLexer :: Token.TokenParser ()
impLexer = Token.makeTokenParser impLanguageDef
identifier :: Parser String
identifier = Token.identifier impLexer
reserved :: String -> Parser ()
reserved = Token.reserved impLexer
reservedOp :: String -> Parser ()
reservedOp = Token.reservedOp impLexer
comma :: Parser String 
comma = Token.comma impLexer
semi :: Parser String 
semi = Token.semi impLexer
parens :: Parser a -> Parser a
parens = Token.parens impLexer
braces :: Parser a -> Parser a
braces = Token.braces impLexer
semiSep :: Parser a -> Parser [a]
semiSep = Token.semiSep impLexer
semiSep1 :: Parser a -> Parser [a]
semiSep1 = Token.semiSep1 impLexer
integer :: Parser Integer
integer = Token.integer impLexer
space :: Parser ()
space = Token.whiteSpace impLexer
stringLiteral :: Parser String
stringLiteral = Token.stringLiteral impLexer

ifStmt :: Parser Stmt
ifStmt = do
    reserved "if"
    cond <- parens expression
    thenS <- statement
    reserved "else"
    elseS <- statement
    return (If cond thenS elseS)

readStmt :: Parser Stmt
readStmt = do
    reserved "read"
    parens $ do
        st <- stringLiteral
        comma
        x <- identifier
        return (Read st x)

printStmt :: Parser Stmt
printStmt = do
    reserved "print"
    parens $ do
        st <- stringLiteral
        comma
        e <- expression
        return (Print st e)

whileStmt :: Parser Stmt
whileStmt = do
    reserved "while"
    cond <- parens expression
    whileS <- statement
    return (While cond whileS)

blockStmt :: Parser Stmt
blockStmt = do
    stmts <- braces (semiSep statement)
    return (Block stmts)

assignStmt :: Parser Stmt
assignStmt = do
    x <- identifier
    reservedOp "="
    exp <- expression
    return (Asgn x exp)

statement :: Parser Stmt
statement =
    declStmt
    <|> assignStmt
    <|> whileStmt
    <|> ifStmt
    <|> blockStmt
    <|> readStmt
    <|> printStmt

declStmt :: Parser Stmt
declStmt = do
    reserved "var"
    x <- identifier
    reservedOp "="
    e <- expression
    return (Decl x e)

expression :: Parser Exp
expression = buildExpressionParser operators term
  where
    operators =
        [ [ prefix "-" UMin
          , prefix "!" Not
          ]
        , [ binary "*" (BinA Mul) AssocLeft
          , binary "/" (BinA Div) AssocLeft
          , binary "%" (BinA Mod) AssocLeft
          ]
        , [ binary "+" (BinA Add) AssocLeft
          , binary "-" (BinA Sub) AssocLeft
          ]
        , [ binary "==" (BinE Eq) AssocNone
          , binary "!=" (BinE Neq) AssocNone
          , binary ">=" (BinC Gte) AssocNone
          , binary ">" (BinC Gt) AssocNone
          , binary "<" (BinC Lt) AssocNone
          , binary "<=" (BinC Lte) AssocNone
          ]
        , [ binary "&&" (BinL And) AssocLeft
          , binary "||" (BinL Or) AssocLeft
          ]
        ]
    binary  name fun = Infix ( reservedOp name >> return fun)
    prefix  name fun = Prefix ( reservedOp name >> return fun)
    postfix name fun = Postfix (do{ reservedOp name; return fun })

bool :: Parser Bool
bool =
    (reserved "true" >> return True)
    <|> (reserved "false" >> return False)

term :: Parser Exp
term =
    parens expression
    <|> (I <$> integer)
    <|> (B <$> bool)
    <|> (Id <$> identifier)

program :: Parser [Stmt]
program = do
    space
    pgm <- semiSep1 statement
    eof
    return pgm
    

loadProgramFromFile :: FilePath -> IO [Stmt]
loadProgramFromFile file = do
    mpgm <- parseFromFile program file
    case mpgm of
        Right pgm -> return  pgm
        Left err -> error (show err)