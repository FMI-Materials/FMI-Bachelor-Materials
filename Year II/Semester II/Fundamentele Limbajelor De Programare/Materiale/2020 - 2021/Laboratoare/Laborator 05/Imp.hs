module Imp where

type Name = String

data BinAop = Add | Mul | Sub | Div | Mod
  deriving (Show)

data BinCop = Lt | Lte | Gt | Gte
  deriving (Show)

data BinEop = Eq | Neq
  deriving (Show)

data BinLop = And | Or
  deriving (Show)

data Exp
    = Id Name
    | I Integer
    | B Bool
    | UMin Exp
    | BinA BinAop Exp Exp
    | BinC BinCop Exp Exp
    | BinE BinEop Exp Exp
    | BinL BinLop Exp Exp
    | Not Exp
  deriving (Show)

data Type = TInt | TBool
  deriving (Eq, Show)

data Stmt
    = Asgn Name Exp
    | If Exp Stmt Stmt
    | Read String Name
    | Print String Exp
    | While Exp Stmt
    | Block [Stmt]
    | Decl Type Name
  deriving (Show)
