{-# LANGUAGE RankNTypes #-}
module HaskellChurch where

import Data.Foldable (toList)

-- A boolean is any way to choose between two alternatives
newtype CBool = CBool {cIf :: forall t. t -> t -> t}

-- An instance to show CBools as regular Booleans
instance Show CBool where
    show b = "cBool " <> show (cIf b True False)

--The boolean constant true always chooses the first alternative
cTrue :: CBool
cTrue = undefined

--The boolean constant false always chooses the second alternative
cFalse :: CBool
cFalse = undefined

cBool :: Bool -> CBool
cBool True = cTrue
cBool False = cFalse

--The boolean negation switches the alternatives
cNot :: CBool -> CBool
cNot = undefined

--The boolean conjunction can be built as a conditional
(&&:) :: CBool -> CBool -> CBool
(&&:) = undefined
infixr 3 &&:

--The boolean disjunction can be built as a conditional
(||:) :: CBool -> CBool -> CBool
(||:) = undefined
infixr 2 ||:

-- a pair is a way to compute something based on the values
-- contained within the pair.
newtype CPair a b = CPair { cOn :: forall c . (a -> b -> c) -> c }

--An instance to show CPairs as regular pairs.
instance (Show a, Show b) => Show (CPair a b) where
    show p = "cPair " <> show (cOn p (,))

-- builds a pair out of two values as an object which, when given
--a function to be applied on the values, it will apply it on them.
cPair :: a -> b -> CPair a b
cPair = undefined

--first projection uses the function selecting first component on a pair
cFst :: CPair a b -> a
cFst = undefined

--second projection
cSnd :: CPair a b -> b
cSnd = undefined

-- A natural number is any way to iterate a function s a number of times 
-- over an initial value z
newtype CNat = CNat { cFor :: forall t. (t -> t) -> t -> t }

-- An instance to show CNats as regular natural numbers
instance Show CNat where
    show n = show $ cFor n (1 +) (0 :: Integer)

--0 will iterate the function s 0 times over z, producing z
c0 :: CNat
c0 = undefined

--1 is the the function s iterated 1 times over z, that is, z
c1 :: CNat
c1 = undefined

--Successor n either
--   - applies s one more time in addition to what n does
--   - iterates s  n times over (s z)
cS :: CNat -> CNat
cS = undefined

--Addition of m and n is done by iterating s n times over m
(+:) :: CNat -> CNat -> CNat
(+:) = undefined
infixl 6 +:

--Multiplication of m and n can be done by composing n and m
(*:) :: CNat -> CNat -> CNat
(*:) = undefined
infixl 7 *:

--Exponentiation of m and n can be done by applying n to m
(^:) :: CNat -> CNat -> CNat
(^:) = undefined
infixr 8 ^:

--Testing whether a value is 0 can be done through iteration
--  using a function constantly false and an initial value true
cIs0 :: CNat -> CBool
cIs0 = undefined

--Predecessor (evaluating to 0 for 0) can be defined iterating
--over pairs, starting from an initial value (0, 0)
cPred :: CNat -> CNat
cPred = undefined

--substraction from m n (evaluating to 0 if m < n) is repeated application
-- of the predeccesor function
(-:) :: CNat -> CNat -> CNat
(-:) = undefined

-- Transform a Num value into a CNat (should yield c0 for nums <= 0)
cNat :: (Ord n, Num n) => n -> CNat
cNat n = undefined

-- We can define an instance Num CNat which will allow us to see any
-- integer constant as a CNat (e.g.   12 :: CNat ) and also use regular
-- arithmetic
instance Num CNat where
    (+) = (+:)
    (*) = (*:)
    (-) = (-:)
    abs = id
    signum n = cIf (cIs0 n) 0 1
    fromInteger = cNat

-- m is less than (or equal to) n if when substracting n from m we get 0
(<=:) :: CNat -> CNat -> CBool
(<=:) = undefined
infix 4 <=:

(>=:) :: CNat -> CNat -> CBool
(>=:) = undefined
infix 4 >=:

(<:) :: CNat -> CNat -> CBool
(<:) = undefined
infix 4 <:

(>:) :: CNat -> CNat -> CBool
(>:) = undefined
infix 4 >:

-- equality on naturals can be defined my means of comparisons
(==:) :: CNat -> CNat -> CBool
(==:) = undefined

--Fun with arithmetic and pairs

--Define factorial. You can iterate over a pair to contain the current index and so far factorial
cFactorial :: CNat -> CNat
cFactorial = undefined

--Define Fibonacci. You can iterate over a pair to contain two consecutive numbers in the sequence
cFibonacci :: CNat -> CNat
cFibonacci = undefined

--Given m and n, compute q and r satisfying m = q * n + r. If n is not 0 then r should be less than n.
--hint repeated substraction, iterated for at most m times.
cDivMod :: CNat -> CNat -> CPair CNat CNat
cDivMod = undefined

-- a list is a way to aggregate a sequence of elements given an aggregation function and an initial value.
newtype CList a = CList { cFoldR :: forall b. (a -> b -> b) -> b -> b }

-- make CList an instance of Foldable
instance Foldable CList where

--An instance to show CLists as regular lists.
instance (Show a) => Show (CList a) where
    show l = "cList " <> (show $ toList l)

-- The empty list is that which when aggregated it will always produce the initial value
cNil :: CList a
cNil = undefined

-- Adding an element to a list means that, when aggregating the list, the newly added
-- element will be aggregated with the result obtained by aggregating the remainder of the list
(.:) :: a -> CList a -> CList a
(.:) = undefined

-- we can obtain a CList from a regular list by folding the list
cList :: [a] -> CList a
cList = undefined

-- builds a CList of CNats corresponding to a list of Integers
cNatList :: [Integer] -> CList CNat
cNatList = undefined

-- sums the elements in the list
cSum :: CList CNat -> CNat
cSum = undefined

-- checks whether a list is nil (similar to cIs0)
cIsNil :: CList a -> CBool
cIsNil = undefined

-- gets the head of the list (or the default specified value if the list is empty)
cHead :: CList a -> a -> a
cHead = undefined

-- gets the tail of the list (empty if the list is empty) --- similar to cPred
cTail :: CList a -> CList a
cTail = undefined

-- length of a list
cLength :: CList a -> CNat
cLength = undefined
