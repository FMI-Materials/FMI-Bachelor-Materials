import Data.Char

-- ========== P1 ==========
data Expr = Var String | Val Int | Expr :+: Expr | Expr :*: Expr
    deriving (Show, Eq)

class Operations exp where
    simplify :: exp -> exp

instance Operations Expr where
    simplify (Var x) = Var x
    simplify (Val x) = Val x
    simplify ((Val 0) :+: exp2) = simplify exp2
    simplify (exp1 :+: (Val 0)) = simplify exp1
    simplify ((Val 0) :*: exp2) = Val 0
    simplify (exp1 :*: (Val 0)) = Val 0
    simplify (exp1 :*: (Val 1)) = simplify exp1
    simplify ((Val 1) :*: exp2) = simplify exp2
    simplify (exp1 :+: exp2) = simplify exp1 :+: simplify exp2
    simplify (exp1 :*: exp2) = simplify exp1 :*: simplify exp2
    
ex1 = ((Val 1) :+: (Var "x")) :*: (Val 1)
ex2 = (ex1) :+: (Val 3)
ex3 = ((Val 0) :*: (Val 2)) :+: (Val 3)
ex4 = ex3 :*: Val 5
-- I should mention that it doesn't work as expected but 
-- I didn't have any other ideas
-- ======================== 

-- ========== P2 ==========  
pasareasca :: String -> String
pasareasca [] = []
pasareasca (x:xs) 
    | x `elem` "aeiouAEIOU" = [x] ++ "p" ++ [toLower x] ++ pasareasca xs
    | otherwise = [x] ++ pasareasca xs
-- ======================== 

-- ========== P3 ==========  
newtype ReaderM env a = ReaderM { runReaderM :: env -> Maybe a }

instance Monad (ReaderM env) where
    return x = ReaderM (\_ -> Just x)
    ma >>= k = ReaderM f where f env = case runReaderM ma env of
                                        Just a -> runReaderM (k a) env
                                        Nothing -> Nothing 

instance Applicative (ReaderM env)
instance Functor(ReaderM env)

testReaderM :: ReaderM String String
testReaderM = ma >>= k
    where
        ma =
            ReaderM
                (\ str -> if length str > 10 then Just (length str) else Nothing)
        k val =
            ReaderM
                (\ str -> if val `mod` 2 == 0 then Just "par" else Nothing)

main :: IO ()
main = do
    let result = runReaderM testReaderM "Hello, this is a long string"
    putStrLn $ "Result: " ++ show result
-- ======================== 
