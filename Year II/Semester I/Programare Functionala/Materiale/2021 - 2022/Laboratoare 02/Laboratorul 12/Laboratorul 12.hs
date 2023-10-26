-- FUNCTORI

-- scrieti instante ale clasei Functor
-- pentru tipurile de date descrie mai jos

-- 1

newtype Identity a = Identity a

instance Functor Identity where
    -- fmap :: (a -> b) -> Identity a -> Identity b
    fmap f (Identity x) = Identity (f x)

-- 2

data Pair a = Pair a a

instance Functor Pair where
    -- fmap :: (a -> b) -> Pair a -> Pair b
    fmap f (Pair x y) = Pair (f x) (f y)

-- 3

data Constant a b = Constant b

instance Functor (Constant a) where
    -- fmap :: (t -> u) -> Constant a t -> Constant a u
    fmap f (Constant x) = Constant (f x)

-- 4

data Two a b = Two a b

instance Functor (Two a) where
    -- fmap :: (t -> u) -> Two a t -> Two a u
    fmap f (Two x y) = Two x (f y)

-- 5

data Three a b c = Three a b c

instance Functor (Three a b) where
    -- fmap :: (t -> u) -> Three a b t -> Three a b u
    fmap f (Three x y z) = Three x y (f z)

-- 6

data Three' a b = Three' a b b

instance Functor (Three' a) where
    -- fmap :: (t -> u) -> Three' a t -> Three' a u
    fmap f (Three' x y z) = Three' x (f y) (f z)

-- 7 

data Four a b c d = Four a b c d

instance Functor (Four a b c) where
    -- fmap :: (t -> u) -> Four a b c t -> Four a b c u
    fmap f (Four x y z t) = Four x y z (f t)

-- 8

data Four'' a b = Four'' a a a b

instance Functor (Four'' a) where
    -- fmap :: (t -> u) -> Four'' a t -> Four'' a u
    fmap f (Four'' x y z t) = Four'' x y z (f t)

-- 9

data Quant a b = Finance | Desk a | Bloor b

instance Functor (Quant a) where
    -- fmap :: (t -> u) -> Quant a t -> Quant a u
    fmap f Finance = Finance
    fmap f (Desk x) = Desk x
    fmap f (Bloor y) = Bloor (f y)

-- instante ce contin constrangeri

-- 10

data LiftItOut f a = LiftItOut (f a)

instance (Functor f) => Functor (LiftItOut f) where
    -- fmap :: (a -> b) -> LiftItOut f a -> LiftItOut f b
    fmap h (LiftItOut fa) = LiftItOut (fmap h fa)

-- 11

data Parappa f g a = DaWrappa (f a) (g a)

instance (Functor f, Functor g) => Functor (Parappa f g) where
    fmap h (DaWrappa fa ga) = DaWrappa (fmap h fa) (fmap h ga)

-- 12

data IgnoreOne f g a b = IgnoringSomething (f a) (g b)

instance (Functor f, Functor g) => Functor (IgnoreOne f g a) where
    -- fmap :: (t -> u) -> IgnoreOne f g a t -> IgnoreOne f g a u
    fmap h (IgnoringSomething fa gb) = IgnoringSomething fa (fmap h gb)

-- 13

data Notorious g o a t = Notorious (g o) (g a) (g t)

instance (Functor g) => Functor (Notorious g o a) where
    fmap f (Notorious go ga gt) = Notorious go ga (fmap f gt)

-- 14

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)

instance Functor GoatLord where
    fmap f NoGoat = NoGoat
    fmap f (OneGoat a) = OneGoat (f a)
    fmap f (MoreGoats a b c) = MoreGoats (fmap f a) (fmap f b) (fmap f c)

-- 15

data TalkToMe a = Halt | Print String a | Read (String -> a)

instance Functor TalkToMe where
    fmap f Halt = Halt
    fmap f (Print s a) = Print s (f a)
    fmap f (Read h) = Read (f . h)
