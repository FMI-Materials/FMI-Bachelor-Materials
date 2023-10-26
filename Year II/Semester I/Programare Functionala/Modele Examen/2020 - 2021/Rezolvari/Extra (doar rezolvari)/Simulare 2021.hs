import Test.QuickCheck
import Data.Foldable
import Data.Monoid 

data BST a = Node (BST a) a (BST a) | Leaf a | Empty 

instance Functor BST where
   fmap f (Node l a r) = Node (fmap f l) (f a) (fmap f r)
   fmap f (Leaf a) = Leaf (f a)
   fmap f Empty = Empty

instance Foldable BST where  
   foldr f z Empty = z
   foldr f z (Leaf a) = f a z
   foldr f z (Node l a r) = foldr f (f a (foldr f z r)) l

isBST :: Ord a => BST a -> Bool
isBST a = let list = toList a in
          isAsc list 
          where
            isAsc [] = True
            isAsc [_] = True
            isAsc (a:b:t)
              | a > b = False
              | otherwise = isAsc (b:t)

instance (Show a, Ord a) => Show (BST a) where
   show a
      | isBST a = show $ toList a
      | otherwise = "Nu e arbore"

insertBST :: Ord a => BST a -> a -> BST a
insertBST (Node l a r) x
   | x < a = Node (insertBST l x) a r
   | otherwise = Node l a (insertBST r x)
insertBST (Leaf a) x
   | x < a = Node (Leaf x) a Empty
   | otherwise = Node Empty a (Leaf x)
insertBST Empty x = Leaf x

instance Monad BST where
   return a = Leaf a
   Empty >>= mab = Empty
   Leaf a >>= mab = mab a
   Node _ a _ >>= mab = mab a

instance Applicative BST where
   pure = return
   mf <*> ma = do
      f <- mf
      a <- ma
      return (f a)

-- Checking
bst1 = Node (Node (Leaf 3) 4 (Leaf 5)) 6 (Leaf 9)
bst2 = Node (Leaf 5) 2 (Leaf 100)

test_insertBST :: Ord a => BST a -> a -> Bool
test_insertBST a x = isBST (insertBST a x) == True

main = undefined
