data Piesa = One   -- primul jucător
            | Two   -- al doilea jucător
            | Empty -- căsuță liberă pe tablă
   deriving (Show, Eq)

data Careu = C [Piesa]
      deriving (Show,Eq)

type Tabla = [Careu]

table1 :: Tabla
table1 = [C [Empty, One, Two, One, Empty, Empty, Two, One],
          C [Two, Empty, One, Two, One, Two, One, Two],
          C [Two, Two, One, Empty, Empty, One, Two, One]]

table2 :: Tabla
table2 = [C [Two, One, Two, One, Empty, Empty, Two, One],
          C [Two, Empty, One, Two, One, Two, One, Two],
          C [Two, Two, One, Empty, Empty, One, Two, One]]

table3 :: Tabla
table3 = [C [Empty, One, Empty, Empty, Empty, Empty, Two, One],
          C [Two, Empty, One, Two, One, Two, One, Two],
          C [Two, Empty, One, Empty, Empty, One, Two, One]]

table4 :: Tabla
table4 = [C [Empty,Empty,Two,One,Empty,Empty,Two,One],
          C [Two,One,One,Two,One,Two,One,Two],
          C [Two,Two,One,Empty,Empty,One,Two,One]]
table5 :: Tabla
table5 = [C [Empty,Empty,Two,One,Empty,Empty,Two,One],
          C [Two,One,One,Two,One,Two,One,Two]]



validTabla :: Tabla -> Bool
validTabla = undefined

test11 = validTabla table1 == True
test12 = validTabla table2 == False
test13 = validTabla table3 == True
test14 = validTabla table5 == False



data Pozitie = Poz (Int,Int)

instance Show Pozitie where
  show (Poz (i,j)) = "careul " ++ show i ++ " pozitia " ++ show j


move :: Tabla -> Pozitie -> Pozitie -> Maybe Tabla
move = undefined

test21 = move table2 (Poz (0,2)) (Poz(1,2)) == Nothing
test22 = move table1 (Poz (0,2)) (Poz(1,2)) == Nothing
test23 = move table1 (Poz (0,1)) (Poz(1,1))
       == Just ([C [Empty,Empty,Two,One,Empty,Empty,Two,One],
                  C [Two,One,One,Two,One,Two,One,Two],
                  C [Two,Two,One,Empty,Empty,One,Two,One]])
                      -- table4
test24 = move table1 (Poz (2,1)) (Poz(1,1))
        == Just ([C [Empty,One,Two,One,Empty,Empty,Two,One],
                  C [Two,Two,One,Two,One,Two,One,Two],
                  C [Two,Empty,One,Empty,Empty,One,Two,One]])



data EitherWriter a = EW {getvalue :: Either String (a, String)}


playGame :: Tabla -> [(Pozitie, Pozitie)] -> [(Pozitie, Pozitie)] -> EitherWriter Tabla
playGame  = undefined

printGame :: EitherWriter Tabla -> IO ()
printGame ewt = do
    let t = getvalue ewt
    case t of
      Left v -> putStrLn v
      Right (t,v) -> putStrLn v

list1, list2 :: [(Pozitie,Pozitie)]
list1 = [(Poz(0,1),Poz(0,0)), (Poz(1,2),Poz(1,1)), (Poz(0,3),Poz(1,3)) ]
list2 = [(Poz(0,6),Poz(0,5)), (Poz(1,3),Poz(2,3)), (Poz(0,2),Poz(0,3)) ]

test41 = printGame $ playGame table1 list1 list2


{-
> test41
Jucatorul One a mutat din careul 0 pozitia 1 in  careul 0 pozitia 0
Jucatorul Two a mutat din careul 0 pozitia 6 in  careul 0 pozitia 5
Jucatorul One a mutat din careul 1 pozitia 2 in  careul 1 pozitia 1
Jucatorul Two a mutat din careul 1 pozitia 3 in  careul 2 pozitia 3
Jucatorul One a mutat din careul 0 pozitia 3 in  careul 1 pozitia 3
Jucatorul Two a mutat din careul 0 pozitia 2 in  careul 0 pozitia 3
Tabla finala este [C [One,Empty,Empty,Two,Empty,Two,Empty,One],C [Two,One,Empty,One,One,Two,One,Two],C [Two,Two,One,Two,Empty,One,Two,One]]
-}
list3, list4 :: [(Pozitie,Pozitie)]
list3 = [(Poz(1,1),Poz(1,0)), (Poz(2,2),Poz(2,4)), (Poz(1,3),Poz(2,3)) ]
list4 = [(Poz(1,6),Poz(1,5)), (Poz(2,3),Poz(3,3)), (Poz(1,2),Poz(1,3)) ]

test42 = printGame $ playGame table1 list3 list4
-- test42
-- Jucatorul One nu poate muta din careul 1 pozitia 1 in  careul 1 pozitia 0
