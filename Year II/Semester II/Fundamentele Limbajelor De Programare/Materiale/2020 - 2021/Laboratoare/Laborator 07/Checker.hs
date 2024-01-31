module Checker where

import Control.Monad.Except
import Control.Monad.Reader
    ( runReader, when, asks, Reader, MonadReader(local) )
import Data.Map.Strict (Map)
import qualified Data.Map.Strict as Map

import AST

data Type = TInt | TBool
  deriving (Eq)

instance Show Type where
    show TInt = "int"
    show TBool = "bool"

type CheckerState = Map Name Type

emptyCheckerState :: CheckerState
emptyCheckerState = Map.empty 

type M = ExceptT String (Reader CheckerState)

lookupM :: Name -> M Type
lookupM x = do
    ot <- asks (Map.lookup x)
    case ot of
        Nothing -> throwError $ "Variable " <> x <> " not declared"
        Just t -> return t

checkExp :: Exp -> M Type
checkExp (I _) = return TInt
checkExp (B _) = return TBool
checkExp (Id x) = lookupM x
checkExp (UMin e) = do
    t <- checkExp e
    expect TInt t e
    return TInt
checkExp (BinA _ e1 e2) = do
    t1 <- checkExp e1
    expect TInt t1 e1
    t2 <- checkExp e2
    expect TInt t2 e2
    return TInt
checkExp (BinC _ e1 e2) = do
    t1 <- checkExp e1
    expect TInt t1 e1
    t2 <- checkExp e2
    expect TInt t2 e2
    return TBool
checkExp (BinE _ e1 e2) = do
    _ <- checkExp e1
    _ <- checkExp e2
    return TBool
checkExp (BinL _ e1 e2) = do
    t1 <- checkExp e1
    expect TBool t1 e1
    t2 <- checkExp e2
    expect TBool t2 e2
    return TBool
checkExp (Not e) = do
    t <- checkExp e
    expect TBool t e
    return TBool

checkStmt :: Stmt -> M ()
checkStmt (Asgn x e) = do
    tx <- lookupM x
    te <- checkExp e
    expect tx te e
checkStmt (If e s1 s2) = do
    te <- checkExp e
    expect TBool  te e
    checkStmt s1
    checkStmt s2
checkStmt (Read _ x) = do
    tx <- lookupM x
    expect TInt tx x
checkStmt (Print _ e) = do
    t <- checkExp e
    expect TInt t e
checkStmt (While e s) = do
    t <- checkExp e
    expect TBool t e
    checkStmt s
checkStmt (Decl _ _) = return ()
checkStmt (Block ss) = checkBlock ss

checkBlock :: [Stmt] -> M ()
checkBlock [] = return ()
checkBlock (Decl x e : ss) = do
    t <- checkExp e
    local (Map.insert x t) (checkBlock ss)
checkBlock (s : ss) = checkStmt s >> checkBlock ss

expect :: (Show t, Eq t, Show e) => t -> t -> e -> M ()
expect tExpect tActual e =
    when (tExpect /= tActual)
        (throwError
        $ "Type mismatch. Expected " <> show tExpect <> " but got " <> show tActual
        <> " for " <> show e)

checkPgm :: [Stmt] -> IO ()
checkPgm pgm =
    case runReader (runExceptT (checkBlock pgm)) emptyCheckerState of
        Left err -> error err
        Right _ -> return ()
