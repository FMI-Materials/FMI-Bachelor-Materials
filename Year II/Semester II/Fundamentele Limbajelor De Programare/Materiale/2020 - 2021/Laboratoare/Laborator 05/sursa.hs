import qualified Text.Parsec.Token as Token
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
import Imp


impLanguageDef :: LanguageDef ()
impLanguageDef =
    emptyDef
    { commentStart = "/*"
    , commentEnd = "*/"
    , commentLine = "//"
    , nestedComments = False
    , caseSensitive = True
    , identStart = letter
    , identLetter = alphaNum
    , reservedNames =
    [ "while", "if", "else", "int", "bool"
    , "true", "false", "read", "print"
    ]
    , reservedOpNames =
    [ "+", "-", "*", "/", "%"
    , "==", "!=", "<", "<=", ">=", ">"
    , "&&", "||", "!", "="
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
parens :: Parser a -> Parser a
parens = Token.parens impLexer
braces :: Parser a -> Parser a
braces = Token.braces impLexer
semiSep :: Parser a -> Parser [a]
semiSep = Token.semiSep impLexer
integer :: Parser Integer
integer = Token.integer impLexer
whiteSpace :: Parser ()
whiteSpace = Token.whiteSpace impLexer
stringParser :: Parser String
stringParser = Token.stringLiteral impLexer
commaParser :: Parser String
commaParser = Token.comma impLexer
bracesParser :: Parser a -> Parser a
bracesParser = Token.braces impLexer
semiParser :: Parser String
semiParser = Token.semi impLexer
semiSepParser :: Parser a -> Parser [a]
semiSepParser = Token.semiSep impLexer

ifStmt :: Parser Stmt
ifStmt = do
  reserved "if"
  cond <- parens expression
  thenS <- statement
  reserved "else"
  If cond thenS <$> statement


asgnStmt :: Parser Stmt
asgnStmt = do
  varname <- identifier
  reservedOp "="
  Asgn varname <$> expression


readStmt :: Parser Stmt 
readStmt = do
  reserved "read"
  let readParameters :: Parser (String, Name)
      readParameters = do
        str <- stringParser
        _ <- commaParser
        name <- identifier
        return (str, name)
  (str, name) <- parens readParameters
  return $ Read str name

printStmt :: Parser Stmt 
printStmt = do
  reserved "print"
  let readParameters :: Parser (String, Exp)
      readParameters = do
        str <- stringParser
        _ <- commaParser
        name <- expression
        return (str, name)
  (str, exp) <- parens readParameters
  return $ Print str exp

readBlock :: Parser Stmt 
readBlock = bracesParser (Block <$> semiSepParser statement) <|> statement

whileStmt :: Parser Stmt 
whileStmt = do
  reserved "while"
  condition <- parens expression
  While condition <$> readBlock

typeParser :: Parser Type 
typeParser = (reserved "int" >> return TInt) <|> (reserved "bool" >> return TBool)

declStmt :: Parser Stmt 
declStmt = do
  t <- typeParser
  Decl t <$> identifier


statement :: Parser Stmt
statement = ifStmt 
            <|> asgnStmt 
            <|> readStmt
            <|> printStmt
            <|> whileStmt 
            <|> declStmt            
            
            



expression :: Parser Exp
expression = buildExpressionParser operators term
  where
    operators =
      [ [ prefix "!" Not
          , prefix "-" UMin
      ]
      , [ binary "*" (BinA Mul) AssocLeft
          , binary "%" (BinA Mod) AssocLeft
      ]
      , [ binary "+" (BinA Add) AssocLeft
      ]
      , [ binary "==" (BinE Eq) AssocNone
      , binary "<=" (BinC Lte) AssocNone
      , binary "<" (BinC Lt) AssocNone
      ]
      , [ binary "&&" (BinL And) AssocLeft
      , binary "||" (BinL Or) AssocLeft
      ]
      ]
    binary name fun = Infix ( reservedOp name >> return fun)
    prefix name fun = Prefix ( reservedOp name >> return fun)
term :: Parser Exp
term =
    parens expression
    <|> I <$> integer
    <|> Id <$> identifier
    <|> boolExp

boolExp :: Parser Exp 
boolExp = (do 
  reserved "true"
  return $ B True
  ) <|> (do
    reserved "false"
    return $ B False)

readLines :: Parser Stmt
readLines = Block <$> semiSepParser statement



main :: IO()
main = do
  result <- parseFromFile (readLines <* eof) "1.imp"
  case result of
    Left err -> print err
    Right xs -> print xs
