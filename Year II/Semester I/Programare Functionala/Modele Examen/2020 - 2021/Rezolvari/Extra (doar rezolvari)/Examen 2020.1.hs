data Piece = One | Two | Empty deriving (Show, Eq)

data Table = Table [Piece] [Piece] [Piece] deriving (Show, Eq)

countOne l = length [x | x<-l, x==One]
countTwo l = length [x | x<-l, x==Two]

validTable :: Table -> Bool
validTable (Table l1 l2 l3) = let validLen = ((length l1)==8) && ((length l2)==8) && ((length l3)==8) in
                              let numOne = (countOne l1) + (countOne l2) + (countOne l3) in
                              let numTwo = (countTwo l1) + (countTwo l2) + (countTwo l3) in
                              validLen && (numOne <= 9) && (numTwo <= 9)

data Position = P (Int, Int) deriving Show

validMove :: Position -> Position -> Bool
validMove (P (0, x)) (P (0, y)) = (abs (x - y)) == 1
validMove (P (1, x)) (P (1, y)) = (abs (x - y)) == 1
validMove (P (2, x)) (P (2, y)) = (abs (x - y)) == 1

validMove (P (x, 1)) (P (y, 1)) = (abs (x - y)) == 1
validMove (P (x, 3)) (P (y, 3)) = (abs (x - y)) == 1
validMove (P (x, 5)) (P (y, 5)) = (abs (x - y)) == 1
validMove (P (x, 7)) (P (y, 7)) = (abs (x - y)) == 1

validMove _ _ = False

replaceNth _ _ [] = []
replaceNth pos val (h:t)
   | pos == 0 = val:t
   | otherwise = h:(replaceNth (pos-1) val t)

movePiece matrix (P (x1, y1)) (P (x2, y2)) = 
      let oldPiece = matrix !! x1 !! y1 in
      let newMatrix = replaceNth x1 (replaceNth y1 Empty (matrix !! x1)) matrix in
      replaceNth x2 (replaceNth y2 oldPiece (newMatrix !! x2)) newMatrix

move :: Table -> Position -> Position -> Maybe Table
move (Table l1 l2 l3) p1 p2
   | not (validMove p1 p2) = Nothing
   | otherwise = let matrix = (movePiece [l1, l2, l3] p1 p2) in
                 Just (Table (matrix !! 0) (matrix !! 1) (matrix !! 2))

table = Table [Empty, One, Empty, Empty, Two, Empty, Empty, Empty] [Empty, Empty, One, One, One, Two, One, One] [Empty, Empty, Two, Two, Two, Empty, Empty, One]

data EitherWriter a = EW {getValue :: Either String (a, String)} deriving (Show, Eq)

instance Monad EitherWriter where
   return a = EW (Right (a, ""))
   EW (Left x) >>= fb = EW (Left x) 
   EW (Right (a, _)) >>= fb = fb a

instance Applicative EitherWriter where
   pure a = return a
   mf <*> ma = do
     f <- mf
     a <- ma
     return (f a)
   
instance Functor EitherWriter where
   fmap f ma = do
     a <- ma
     return (f a)

invalidMove = EW (Left "Mutare invalida")

makeMove :: Table -> (Position, Position) -> String -> EitherWriter Table
makeMove t (p1, p2) player = let table = move t p1 p2 in
                      if table == Nothing then
                          invalidMove
                      else
                          let (Just actual_table) = table in
                          EW (Right (actual_table, "\nJucatorul " ++ player ++ " a mutat din " ++ (show p1) ++ " in "++(show p2)))

playGame' :: Table -> [(Position, Position)] -> [(Position, Position)] -> String -> EitherWriter Table
playGame' t (m1:t1) (m2:t2) res = let table11 = makeMove t m1 "One" in
                             if table11 == invalidMove then
                                 table11
                             else
                                 let (EW (Right (table12, msg1))) = table11 in
                                 let table21 = makeMove table12 m2 "Two" in
                                 if table21 == invalidMove then
                                     table21
                                 else
                                     let (EW (Right (table22, msg2))) = table21 in
                                     playGame' table22 t1 t2 (msg1 ++ msg2 ++ res)
playGame' table _ _ res = EW (Right (table, res ++ "\nTabla finala este: " ++ (show table)))


playGame :: Table -> [(Position, Position)] -> [(Position, Position)] -> EitherWriter Table
playGame a b c = playGame' a b c ""

printGame :: EitherWriter Table -> IO ()
printGame ewt = do
    let t = getValue ewt
    case t of
      Left v -> putStrLn v
      Right (t,v) -> putStrLn v

table1 :: Table
table1 = Table [Empty, One, Two, One, Empty, Empty, Two, One]
               [Two, Empty, One, Two, One, Two, One, Two]
               [Two, Two, One, Empty, Empty, One, Two, One]
list1, list2 :: [(Position,Position)]
list1 = [(P(1,1),P(1,0)), (P(2,2),P(2,1)), (P(1,3),P(2,3)) ]
list2 = [(P(1,6),P(1,5)), (P(2,3),P(3,3)), (P(1,2),P(1,3)) ]

test41 = printGame $ playGame table1 list1 list2

list3, list4 :: [(Position,Position)]
list3 = [(P(1,1),P(1,0)), (P(2,2),P(2,4)), (P(1,3),P(2,3)) ]
list4 = [(P(1,6),P(1,5)), (P(2,3),P(3,3)), (P(1,2),P(1,3)) ]

test42 = printGame $ playGame table1 list3 list4

main = undefined
