import Data.List (nub)
import Data.Maybe (fromJust)
import Data.Char

type Nume = String
data Prop
  = Var Nume
  | F
  | T
  | Not Prop
  | Prop :|: Prop
  | Prop :&: Prop
  deriving (Eq, Read)
infixr 2 :|:
infixr 3 :&:

p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: (Not (Var "P") :&: Not (Var "Q"))

p3 :: Prop
p3 = (Var "P" :&: (Var "Q" :|: Var "R") :&: ((Not (Var "P") :|: Not (Var "Q")) :&: (Not (Var "P") :|: Not (Var "R"))))

instance Show Prop where
  show (Var nume) = nume
  show F = "False"
  show T = "True"
  show (Not prop) = "(~" ++ ( show prop) ++ ")"
  show (prop1 :|: prop2) = "(" ++ (show prop1) ++ "|" ++ (show prop2) ++ ")"
  show (prop1 :&: prop2) = "(" ++ (show prop1) ++ "&" ++ (show prop2) ++ ")"
 
test_ShowProp :: Bool
test_ShowProp =
    show (Not (Var "P") :&: Var "Q") == "((~P)&Q)"

type Env = [(Nume, Bool)]

impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a

eval :: Prop -> Env -> Bool
eval T _ = True
eval F _ = False
eval (Var nume) vals = impureLookup nume vals
eval (prop1 :|: prop2) vals = (eval prop1 vals) || (eval prop2 vals)
eval (prop1 :&: prop2) vals = (eval prop1 vals) && (eval prop2 vals)
eval (Not prop) vals = not (eval prop vals)

test_eval = eval  (Var "P" :|: Var "Q") [("P", True), ("Q", False)] == True

variabile :: Prop -> [Nume]
variable (Var nume) = [nume]
variable (Not prop) = nub $ variable prop
variable (prop1 :|: prop2) = nub ((variable prop1) ++ (variable prop2))
variable (prop1 :&: prop2) = nub ((variable prop1) ++ (variable prop2))
variabile _ = []
 
test_variabile =
  variabile (Not (Var "P") :&: Var "Q") == ["P","Q"]

envs :: [Nume] -> [Env]
envs [] = []
envs [x] = [[(x,False)],[(x,True)]]
envs (str:xs) = let r = envs xs in  map (\x-> (str,False):x) r  ++ map (\x->(str,True):x) r 
 
test_envs = 
    envs ["P", "Q"]
    ==
    [ [ ("P",False)
      , ("Q",False)
      ]
    , [ ("P",False)
      , ("Q",True)
      ]
    , [ ("P",True)
      , ("Q",False)
      ]
    , [ ("P",True)
      , ("Q",True)
      ]
    ]

satisfiabila :: Prop -> Bool
satisfiabila prop = let vars = variable prop in
                    let env = envs vars in
                    or [eval prop x  | x<-env]
 
test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q") == True
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P") == False

valida :: Prop -> Bool
valida prop = let vars = variable prop in
              let env = envs vars in
              and [eval prop x  | x<-env]

test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 = valida (Not (Var "P") :|: Var "P") == True

tabelAdevar :: Prop -> String
tabelAdevar prop = let vars = variable prop in
                   let env = envs vars in
                   let propStr = show prop in
                   let table = [(show (eval prop x)) ++ "\n" | x<-env] in
                   propStr ++ "\n" ++ (concat table)

echivalenta :: Prop -> Prop -> Bool
echivalenta = undefined
 
test_echivalenta1 =
  True
  ==
  (Var "P" :&: Var "Q") `echivalenta` (Not (Not (Var "P") :|: Not (Var "Q")))
test_echivalenta2 =
  False
  ==
  (Var "P") `echivalenta` (Var "Q")
test_echivalenta3 =
  True
  ==
  (Var "R" :|: Not (Var "R")) `echivalenta` (Var "Q" :|: Not (Var "Q"))

main = undefined
