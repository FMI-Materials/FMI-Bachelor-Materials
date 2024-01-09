data Tree 
    = Empty -- arbore vid
    | Node Int Tree Tree Tree -- arbore cu valoare de tip Int in radacina
                              -- si 3 fii
    deriving Show

extree :: Tree
extree = Node 4 (Node 5 Empty Empty Empty) (Node 3 Empty Empty (Node 1 Empty Empty Empty)) Empty

-- 1
class ArbInfo t where
    level :: t -> Int -- intoarce inaltimea arborelui;
                      -- consideram ca un arbore vid are inaltimea 0
    sumval :: t -> Int -- intoarce suma valorilor din arbore
    nrFrunze :: t -> Int -- intoarce nr de frunze al arborelui

instance ArbInfo Tree where
    level t = level' t where
              level' Empty = 0
              level' (Node _ child1 child2 child3)= 1 + max (level' child1) (max (level' child2) (level' child3))
    sumval t = sumval' t 0 where
               sumval' Empty s = s
               sumval' (Node x child1 child2 child3) s = x + sumval' child1 0 + sumval' child2 0 + sumval' child3 0
    nrFrunze t = nrFrunze' t where
                 nrFrunze' Empty = 0
                 nrFrunze' (Node _ Empty Empty Empty) = 1
                 nrFrunze' (Node _ child1 child2 child3) = nrFrunze' child1 + nrFrunze' child2 + nrFrunze' child3


class Scalar a where
    zero :: a
    one :: a
    adds :: a -> a -> a
    mult :: a -> a -> a
    negates :: a -> a
    recips :: a -> a

-- 2
instance Scalar Double where
  zero = 0
  one = 1
  adds x y = x + y
  mult x y = x * y
  negates x = (-x)
  recips x = if x == 0 then error "Division by 0" else 1 / x


class (Scalar a) => Vector v a where
    zerov :: v a
    onev :: v a
    addv :: v a -> v a -> v a -- adunare vector
    smult :: a -> v a -> v a -- inmultire cu scalare
    negatev :: v a -> v a -- negare vector

-- 3
data Vector2D a = Vector2D a a deriving Show

instance Scalar a => Vector Vector2D a where    
    zerov = Vector2D zero zero
    onev = Vector2D one one
    addv (Vector2D x1 y1) (Vector2D x2 y2) = Vector2D (adds x1 x2) (adds y1 y2)
    smult x (Vector2D x1 y1) = Vector2D (mult x x1) (mult x y1)
    negatev (Vector2D x y) = Vector2D (negates x) (negates y)

data Vector3D a = Vector3D a a a

instance Scalar a => Vector Vector3D a where
    zerov = Vector3D zero zero zero
    onev = Vector3D one one one
    addv (Vector3D x1 y1 z1) (Vector3D x2 y2 z2) = Vector3D (adds x1 x2) (adds y1 y2) (adds z1 z2)
    smult x (Vector3D x1 y1 z1) = Vector3D (mult x x1) (mult x y1) (mult x z1)
    negatev (Vector3D x y z) = Vector3D (negates x) (negates y) (negates z)