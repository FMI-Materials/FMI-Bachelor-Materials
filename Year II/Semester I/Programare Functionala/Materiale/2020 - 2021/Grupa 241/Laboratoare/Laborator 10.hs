import Test.QuickCheck
import Test.QuickCheck.Gen

--monoid : op asociativa si e*m=m*e=m
--semigrup : op asociativa
semigroupAssoc :: (Eq m, Semigroup m) => m -> m -> m -> Bool
semigroupAssoc a b c = (a <> (b <> c)) == ((a <> b) <> c)

monoidLeftIdentity   :: (Eq m, Monoid m) => m -> Bool
monoidLeftIdentity a = (mempty <> a) == a

monoidRightIdentity   :: (Eq m, Monoid m) => m -> Bool
monoidRightIdentity a = (a <> mempty) == a

-- Exercițiul 1 - Trivial
data Trivial = Trivial
              deriving (Eq, Show)

instance Semigroup Trivial where
  _ <> _ = Trivial
instance Monoid Trivial where
  mempty  = Trivial
instance Arbitrary Trivial where
  arbitrary = elements[Trivial]

--semigroupAssoc :: (Eq m, Semigroup m) => m -> m -> m -> Bool
type TrivAssoc = Trivial -> Trivial -> Trivial -> Bool
--monoidLeftIdentity   :: (Eq m, Monoid m) => m -> Bool
--monoidRightIdentity   :: (Eq m, Monoid m) => m -> Bool
type TrivId    = Trivial -> Bool

test1=quickCheck (semigroupAssoc :: TrivAssoc) --verifica daca e asociativa
test2=quickCheck (monoidLeftIdentity :: TrivId) --daca are element neutru la stanga
test3=quickCheck (monoidRightIdentity :: TrivId) --daca are element neutru la dreapta

-- Exercițiul 2 - Conjuncții
-- newtype se foloseste cand un singur constructor este aplicat unui singur tip de date 
-- declaratia cu newtype este mai eficienta decât cea cu data
-- type redenumeste tipul
-- newtype face o copie si permite redefinirea operatiilor

newtype BoolConj = BoolConj Bool --newtype pt ca facem copie a tipului boolean
                   deriving (Eq, Show)

instance Semigroup BoolConj where 
    BoolConj a <> BoolConj b = BoolConj (a && b)

instance Monoid BoolConj where 
    mempty = BoolConj True --elementul neutru pt conjunctii => True 

instance Arbitrary BoolConj where
  --arbitrary = MkGen ( \s i -> BoolConj  ((unGen arbitrary) s i)) --generator pt tipul BoolConj
  arbitrary = fmap BoolConj arbitrary --Functori
--arbitrary pt Bool -> [True, False, True]
--arbitrary pt BoolConj -> [BoolConj True, BoolConj False, ...]

--Definitie curs a generatorului
--      MkGen ( \s i -> BoolConj  (f s i))
--                     where 
--                       f = unGen (arbitrary :: Gen Bool)

type BoolConjAssoc = BoolConj -> BoolConj -> BoolConj -> Bool
type BoolConjId    = BoolConj -> Bool

test4=quickCheck (semigroupAssoc :: BoolConjAssoc)
test5=quickCheck (monoidLeftIdentity :: BoolConjId)
test6=quickCheck (monoidRightIdentity :: BoolConjId)
--(BoolConj True <> BoolConj False) <> BoolConj True == BoolConj True <> (BoolConj True <> BoolConj False)
--BoolConj (True && False)<> BoolConj True = BoolConj True <> BoolConj (False && True)

-- Exercițiul 3 - Disjuncții 
newtype BoolDisj = BoolDisj Bool
                   deriving (Eq, Show)

instance Semigroup BoolDisj where 
    BoolDisj a <>BoolDisj b = BoolDisj (a||b)   
instance Monoid BoolDisj where 
    mempty = BoolDisj False
instance Arbitrary BoolDisj where
    arbitrary = fmap BoolDisj arbitrary
  
type BoolDisjAssoc = BoolDisj -> BoolDisj -> BoolDisj -> Bool
type BoolDisjId    = BoolDisj -> Bool

test7=quickCheck (semigroupAssoc :: BoolDisjAssoc)
test8=quickCheck (monoidLeftIdentity :: BoolDisjId)
test9=quickCheck (monoidRightIdentity :: BoolDisjId)


-- Exercițiul 4 - Identity
newtype Identity a = Identity a
                     deriving (Eq, Show)

-- !! cand apare litera in stanga egalului
instance Semigroup a => Semigroup (Identity a) where
    Identity x <> Identity y = Identity ( x <> y) 
    --stim ca tipul de date a lui x si y are un semigrup definit pe el deja
instance Monoid a => Monoid (Identity a) where
    --aici ne folosim de faptul care are un monoid pe a
    mempty = Identity mempty 
instance Arbitrary a => Arbitrary (Identity a) where
    arbitrary = MkGen ( \s i -> Identity  ((unGen arbitrary) s i))
   
type IdentityAssoc a = Identity a -> Identity a -> Identity a -> Bool
type IdentityId    a = Identity a -> Bool

test10=quickCheck (semigroupAssoc :: IdentityAssoc String) --pe String
test11=quickCheck (monoidLeftIdentity :: IdentityId [Int]) --lista de Int
test12=quickCheck (monoidRightIdentity :: IdentityId [Int]) --lista de Int

-- Exercițiul 5 - Pereche
data Two a b = Two a b
               deriving (Eq, Show)

instance (Semigroup a, Semigroup b) => Semigroup (Two a b) where 
    Two x y <> Two z t = Two (x<>z) (y<>t)
instance (Monoid a, Monoid b) => Monoid (Two a b) where 
    mempty = Two mempty mempty
--primul mempty ii coresp Monoidului a si al doilea monoidului b
instance (Arbitrary a, Arbitrary b) => Arbitrary (Two a b) where
  arbitrary = MkGen ( \s i -> Two ((unGen (arbitrary)) s i) ((unGen (arbitrary)) s i)) 
  
type TwoAssoc a b = Two a b -> Two a b -> Two a b -> Bool
type TwoId    a b = Two a b -> Bool

test13=quickCheck (semigroupAssoc :: TwoAssoc String [Int])
test14=quickCheck (monoidLeftIdentity :: TwoId [Int] String)
test15=quickCheck (monoidRightIdentity :: TwoId [Int] [Int])

-- Exercițiul 6 - Alternative  
data Or a b = Fst a | Snd b
              deriving (Eq, Show)

instance  Semigroup (Or a b) where 
    Fst _ <> x =  x
    y     <> _ = y
 
instance (Arbitrary a, Arbitrary b) => Arbitrary (Or a b) where
    arbitrary = oneof [MkGen ( \s i -> Fst ((unGen (arbitrary)) s i)) , 
                      MkGen ( \s i -> Fst ((unGen (arbitrary)) s i))]
                     
type OrAssoc a b = Or a b -> Or a b -> Or a b -> Bool
                    
test16=quickCheck (semigroupAssoc :: OrAssoc String Int)
test17=quickCheck (semigroupAssoc :: OrAssoc String [Int])
