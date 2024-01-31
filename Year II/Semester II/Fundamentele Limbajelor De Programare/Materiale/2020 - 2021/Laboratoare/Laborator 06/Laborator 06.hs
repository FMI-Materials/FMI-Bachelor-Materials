module Checker where


import Data.Map.Strict (Map)
import qualified Data.Map.Strict as Map

import SIMPLE

data Type = TInt | TBool
  deriving (Eq)

instance Show Type where
    show TInt = "int"
    show TBool = "bool"

type CheckerState = Map Name Type

emptyCheckerState :: CheckerState
emptyCheckerState = Map.empty

newtype EReader a =
    EReader { runEReader :: CheckerState ->  (Either String a) }

throwError :: String -> EReader a
throwError e = EReader (\_ -> (Left e))

instance Monad EReader where
    return a = EReader (\env ->  Right a)
    act >>= k = EReader  f
                where
                 f env  = case (runEReader act env) of
                           Left s -> Left s
                           Right va -> runEReader (k va) env


instance Functor EReader where
    fmap f ma = do { a <- ma; return (f a) }

instance Applicative EReader where
    pure = return
    mf <*> ma = do { f <- mf; a <- ma; return (f a)}

askEReader :: EReader CheckerState
askEReader =EReader (\env -> Right env)

localEReader :: (CheckerState -> CheckerState) -> EReader a -> EReader a
localEReader f ma = EReader (\env -> (runEReader ma) (f env))


type M = EReader

expect :: (Show t, Eq t, Show e) => t -> t -> e -> M ()
expect tExpect tActual e =
    if (tExpect /= tActual)
    then     (throwError
        $ "Type mismatch. Expected " <> show tExpect <> " but got " <> show tActual
        <> " for " <> show e)
    else (return ())

checkExp :: Exp -> M Type
checkExp = undefined


checkStmt :: Stmt -> M ()
checkStmt = undefined

checkBlock :: [Stmt] -> M ()
checkBlock = undefined


checkPgm :: [Stmt] -> Bool
checkPgm pgm =
    case  (runEReader (checkBlock pgm)) emptyCheckerState of
        Left err -> error err
        Right _ -> True
