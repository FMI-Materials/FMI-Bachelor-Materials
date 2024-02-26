-- c
data B e = R e Int | B e ::: B e
    deriving Eq
infixr 5 :::

instance Foldable B where
   foldr f z (R x _) = f x z
   foldr f z (l ::: r) = foldr f (foldr f z r) l

-- Teste foldable
bdr41Test1 = maximum (R "nota" 2 ::: R "zece" 3 ::: R "la" 5 ::: R "examen" 1) == "zece"
bdr42Test2 = minimum (R "nota" 55 ::: R "aaaaaa" 1) == "aaaaaa"

-- d
class C e where
  cFilter :: (a -> Bool) -> e a -> e (Maybe a)
  fromList :: [a] -> e a

-- Functie auxiliara, mai primeste ca parametru indexul
bdr51FromList :: [e] -> Int -> B e
bdr51FromList [el] i = R el i
bdr51FromList (h:t) i = (R h i):::(bdr51FromList t (i+1)) 

instance C B where
   cFilter f (R x y)
      | f x = R (Just x) y
      | otherwise = R Nothing y
   cFilter f ((R x y) ::: r) 
      | f x = (R (Just x) y) ::: (cFilter f r)
      | otherwise = (R Nothing y) ::: (cFilter f r)
   fromList l = bdr51FromList l 1 

-- Teste instanta C B
bdr52Test1 = cFilter (\x -> length x == 4) (fromList ["nota", "zece", "la", "examen"]) ==
      (R (Just "nota") 1 ::: R (Just "zece") 2 ::: R Nothing 3 ::: R Nothing 4)
bdr53Test2 = cFilter (\x -> x !! 0 == 't') (fromList ["nota", "zece", "test", "tac"]) ==
       (R Nothing 1 ::: R Nothing 2 ::: R (Just "test") 3 ::: R (Just "tac") 4)

main = undefined
