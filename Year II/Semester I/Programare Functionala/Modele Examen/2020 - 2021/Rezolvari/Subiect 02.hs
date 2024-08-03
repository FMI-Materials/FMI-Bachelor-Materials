data Piece = One   -- primul jucător
            | Two   -- al doilea jucător
            | Empty -- căsuță liberă pe tablă
   deriving (Show, Eq)

data Table = Table [Piece] [Piece] [Piece]
   deriving (Show,Eq)

table1 :: Table
table1 = Table [Empty, One, Two, One, Empty, Empty, Two, One]
               [Two, Empty, One, Two, One, Two, One, Two]
               [Two, Two, One, Empty, Empty, One, Two, One]

table2 :: Table
table2 = Table [Two, One, Two, One, Empty, Empty, Two, One]
               [Two, Empty, One, Two, One, Two, One, Two]
               [Two, Two, One, Empty, Empty, One, Two, One]

table3 :: Table
table3 = Table [Empty, One, Empty, Empty, Empty, Empty, Two, One]
               [Two, Empty, One, Two, One, Two, One, Two]
               [Two, Empty, One, Empty, Empty, One, Two, One]

table4 :: Table
table4 = Table [Empty,Empty,Two,One,Empty,Empty,Two,One]
               [Two,One,One,Two,One,Two,One,Two]
               [Two,Two,One,Empty,Empty,One,Two,One]



validTable :: Table -> Bool
validTable = undefined
test11 = validTable table1 == True
test12 = validTable table2 == False
test13 = validTable table3 == True



data Position = P (Int,Int)

instance Show Position where
  show (P (i,j)) = "careul " ++ show i ++ " pozitia " ++ show j

move :: Table -> Position -> Position -> Maybe Table
move = undefined

test21 = move table2 (P (1,2)) (P(2,2)) == Nothing
test22 = move table1 (P (1,2)) (P(2,2)) == Nothing
test23 = move table1 (P (1,1)) (P(2,1))
       == Just (Table [Empty,Empty,Two,One,Empty,Empty,Two,One]
                      [Two,One,One,Two,One,Two,One,Two]
                      [Two,Two,One,Empty,Empty,One,Two,One])
                      -- table4
test24 = move table1 (P (3,1)) (P(2,1))
        == Just (Table [Empty,One,Two,One,Empty,Empty,Two,One]
                       [Two,Two,One,Two,One,Two,One,Two]
                       [Two,Empty,One,Empty,Empty,One,Two,One])



data EitherWriter a = EW {getvalue :: Either String (a, String)}


playGame :: Table -> [(Position, Position)] -> [(Position, Position)] -> EitherWriter Table
playGame = undefined

printGame :: EitherWriter Table -> IO ()
printGame ewt = do
    let t = getvalue ewt
    case t of
      Left v -> putStrLn v
      Right (t,v) -> putStrLn v

list1, list2 :: [(Position,Position)]
list1 = [(P(1,1),P(1,0)), (P(2,2),P(2,1)), (P(1,3),P(2,3)) ]
list2 = [(P(1,6),P(1,5)), (P(2,3),P(3,3)), (P(1,2),P(1,3)) ]

test41 = printGame $ playGame table1 list1 list2


{-
> test41
Jucatorul One a mutat din careul 1 pozitia 1 in  careul 1 pozitia 0
Jucatorul Two a mutat din careul 1 pozitia 6 in  careul 1 pozitia 5
Jucatorul One a mutat din careul 2 pozitia 2 in  careul 2 pozitia 1
Jucatorul Two a mutat din careul 2 pozitia 3 in  careul 3 pozitia 3
Jucatorul One a mutat din careul 1 pozitia 3 in  careul 2 pozitia 3
Jucatorul Two a mutat din careul 1 pozitia 2 in  careul 1 pozitia 3
Table finala este Table [One,Empty,Empty,Two,Empty,Two,Empty,One] [Two,One,Empty,One,One,Two,One,Two] [Two,Two,One,Two,Empty,One,Two,One]
-}
list3, list4 :: [(Position,Position)]
list3 = [(P(1,1),P(1,0)), (P(2,2),P(2,4)), (P(1,3),P(2,3)) ]
list4 = [(P(1,6),P(1,5)), (P(2,3),P(3,3)), (P(1,2),P(1,3)) ]

test42 = printGame $ playGame table1 list3 list4
-- test42
-- Jucatorul One nu poate muta din careul 2 pozitia 2 in  careul 2 pozitia 4
