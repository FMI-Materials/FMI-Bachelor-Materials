import Data.Bifunctor (Bifunctor)
{-
class Functor f where
fmap : : ( a -> b ) -> f a -> f b
-}
-- Scrieti instante ale clasei Functor pentru tipurile de 
-- date descrise mai jos.
newtype Identity a = Identity a
    deriving Show
instance Functor Identity where
    fmap f (Identity a) = Identity (f a)

data Pair a = Pair a a
    deriving Show
instance Functor Pair where
    fmap f (Pair a b) = Pair (f a) (f b)

data Constant a b = Constant b
    deriving Show
instance Functor (Constant  a) where
    fmap f (Constant b) = Constant (f b)

data Two a b = Two a b 
    deriving Show
instance Functor (Two a ) where
    fmap f (Two a b) = Two a (f b)

data Three a b c = Three a b c
    deriving Show
instance Functor (Three a b) where
    fmap f (Three a b c) = Three a b (f c)

data Three' a b = Three' a b b
    deriving Show
instance Functor (Three' a) where
    fmap f (Three' a b c) = Three' a (f b) (f c)

data Four a b c d = Four a b c d
    deriving Show
instance Functor (Four a b c) where
    fmap f (Four a b c d) = Four a b c (f d)

data Four'' a b = Four'' a a a b
    deriving Show
instance Functor (Four'' a) where
    fmap f (Four'' a b c d) = Four'' a b c (f d)

data Quant a b = Finance | Desk a | Bloor b
    deriving Show
instance Functor (Quant a) where
    fmap f (Finance) = Finance
    fmap f (Desk a) = Desk a
    fmap f (Bloor b) = Bloor (f b)

-- S-ar putea să fie nevoie să adăugati unele constrângeri 
-- la definirea instantelor

data LiftItOut f a = LiftItOut (f a)
    deriving Show
instance Functor f => Functor (LiftItOut f) where
    fmap func (LiftItOut fa) = LiftItOut (fmap func fa)

data Parappa f g a = DaWrappa (f a) (g a)
    deriving Show
instance (Functor f, Functor g) => Functor (Parappa f g) where
    fmap func (DaWrappa fa ga) = DaWrappa (fmap func fa) (fmap func ga)

data IgnoreOne f g a b = IgnoringSomething (f a) (g b)
    deriving Show
instance (Functor f, Functor g) => Functor (IgnoreOne f g a) where
    fmap f (IgnoringSomething fa gb) = IgnoringSomething fa (fmap f gb)

data Notorious g o a t = Notorious (g o) (g a) (g t)
    deriving Show
instance (Functor g) => Functor (Notorious g o a) where
    fmap f (Notorious go ga gt) = Notorious go ga (fmap f gt)

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)
    deriving Show
instance Functor GoatLord where
    fmap f NoGoat = NoGoat
    fmap f (OneGoat a) = OneGoat (f a)
    fmap f (MoreGoats a b c) = MoreGoats (fmap f a) (fmap f b) (fmap f c)

data TalkToMe a = Halt | Print String a | Read (String -> a)
instance Functor TalkToMe  where
    fmap f Halt = Halt
    fmap f (Print a b) = Print a (f b)
    fmap f (Read g) = Read (fmap f g)

