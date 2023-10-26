import Test.QuickCheck hiding (Failure, Success)

semigroupAssoc :: (Eq m, Semigroup m) => m -> m -> m -> Bool
semigroupAssoc a b c = (a <> (b <> c)) == ((a <> b) <> c)

monoidLeftIdentity   :: (Eq m, Monoid m) => m -> Bool
monoidLeftIdentity a = (mempty <> a) == a

monoidRightIdentity   :: (Eq m, Monoid m) => m -> Bool
monoidRightIdentity a = (a <> mempty) == a

-- Example 1 - Trivial
 
data Trivial = Trivial deriving (Eq, Show)

instance Semigroup Trivial where
  _ <> _ = Trivial

instance Monoid Trivial where
  mempty  = Trivial

instance Arbitrary Trivial where
  arbitrary = return Trivial

type TrivAssoc = Trivial -> Trivial -> Trivial -> Bool
type TrivId    = Trivial -> Bool

testTrivial :: IO ()
testTrivial
  = do
    quickCheck (semigroupAssoc :: TrivAssoc)
    quickCheck (monoidLeftIdentity :: TrivId)
    quickCheck (monoidRightIdentity :: TrivId)

-- Exercise 2 - Identity
 
newtype Identity a = Identity a deriving (Eq, Show)

instance Semigroup a => Semigroup (Identity a) where
  Identity x <> Identity y = Identity (x <> y)
 
instance (Semigroup a, Monoid a) => Monoid (Identity a) where
  mempty = Identity mempty

instance Arbitrary a => Arbitrary (Identity a) where
  arbitrary = Identity <$> arbitrary

type IdentityAssoc a = Identity a -> Identity a -> Identity a -> Bool
type IdentityId a = Identity a -> Bool

testIdentity :: IO()
testIdentity = do
   quickCheck (semigroupAssoc :: IdentityAssoc String)
   quickCheck (monoidLeftIdentity :: IdentityId String)
   quickCheck (monoidRightIdentity :: IdentityId String)

-- Exercise 3 - Pair
 
data Two a b = Two a b deriving (Eq, Show)

instance (Semigroup a, Semigroup b) => Semigroup (Two a b) where
  Two x1 y1 <> Two x2 y2 = Two (x1 <> x2) (y1 <> y2)

instance (Monoid a, Monoid b) => Monoid (Two a b) where
  mempty = Two mempty mempty

instance (Arbitrary a, Arbitrary b) => Arbitrary (Two a b) where
  arbitrary = Two <$> arbitrary <*> arbitrary

type TwoAssoc a b = Two a b -> Two a b -> Two a b -> Bool
type TwoId a b = Two a b -> Bool

testTwo = do
   quickCheck (semigroupAssoc :: TwoAssoc String String)
   quickCheck (monoidLeftIdentity :: TwoId String String)
   quickCheck (monoidRightIdentity :: TwoId String String)

-- Exercise 4 - Triple
 
data Three a b c = Three a b c
  deriving (Eq, Show)

--instance (Semigroup a, Semigroup b, Semigroup c) => Semigroup (Three a b c) where
--  (Three x1 y1 z1 <> Three x2 y2 z2) <> Three x3 y3 z3 = Three ((x1 <> x2) <> x3) ((y1 <> y2) <> y3) ((z1 <> z2) <> z3)

instance (Arbitrary a, Arbitrary b, Arbitrary c) => Arbitrary (Three a b c) 
  where
    arbitrary = Three <$> arbitrary <*> arbitrary <*> arbitrary

-- Exercise 5 - Boolean conjunction
 
newtype BoolConj = BoolConj Bool deriving (Eq, Show)

instance Semigroup BoolConj where
  BoolConj a <> BoolConj b = BoolConj (a && b)

instance Monoid BoolConj where
  mempty = BoolConj True

instance Arbitrary BoolConj where
  arbitrary = BoolConj <$> arbitrary

type BoolConjAssoc = BoolConj -> BoolConj -> BoolConj -> Bool
type BoolConjId = BoolConj -> Bool

testBoolConj = do
  quickCheck (semigroupAssoc :: BoolConjAssoc)
  quickCheck (monoidLeftIdentity :: BoolConjId)
  quickCheck (monoidRightIdentity :: BoolConjId)

-- Exercise 6 - Boolean disjunction
 
newtype BoolDisj = BoolDisj Bool deriving (Eq, Show)

instance Semigroup BoolDisj where
  BoolDisj a <> BoolDisj b = BoolDisj (a || b)

instance Monoid BoolDisj where
  mempty = BoolDisj False

instance Arbitrary BoolDisj where
  arbitrary = BoolDisj <$> arbitrary

type BoolDisjAssoc = BoolDisj -> BoolDisj -> BoolDisj -> Bool
type BoolDisjId = BoolDisj -> Bool

testBoolDisj = do
  quickCheck (semigroupAssoc :: BoolDisjAssoc)
  quickCheck (monoidLeftIdentity :: BoolDisjId)
  quickCheck (monoidRightIdentity :: BoolDisjId)

-- Exercise 7 - Or
 
data Or a b = Fst a | Snd b deriving (Eq, Show)

instance (Arbitrary a, Arbitrary b) => Arbitrary (Or a b) where
  arbitrary = oneof [Fst <$> arbitrary, Snd <$> arbitrary]

-- Exercise 8 - Lifting Monoid to Functions
 
newtype Combine a b = Combine { unCombine :: a -> b }

instance (CoArbitrary a, Arbitrary b) => Arbitrary (Combine a b) where
  arbitrary = Combine <$> arbitrary

main = undefined
