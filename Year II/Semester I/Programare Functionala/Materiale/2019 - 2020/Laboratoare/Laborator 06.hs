{-# LANGUAGE DataKinds #-}
{-# LANGUAGE TypeApplications #-}
import Data.List (nub)
import Data.Maybe

data Fruct
    = Mar String Bool
    | Portocala String Int

ionatanFaraVierme = Mar "Ionatan" False
goldenCuVierme = Mar "Golden Delicious" True
portocalaSicilia10 = Portocala "Sanguinello" 10
listaFructe = [Mar "Ionatan" False
                , Portocala "Sanguinello" 10
                , Mar "Golden Delicious" True
                , Portocala "Sanguinello" 15
                , Portocala "Moro" 12
                , Portocala "Tarocco" 3
                , Portocala "Moro" 12
                , Portocala "Valencia" 2
                , Mar "Golden Delicious" False
                , Mar "Golden" False
                , Mar "Golden" True]
                --deriving(Show)

instance Show Fruct where
    show (Mar s b) = "Marul " ++ s ++ (if b then " are viermi" else " nu are vierme ")
    show (Portocala s i) = "Portocala " ++ s ++ " are " ++ show i ++ " felii."


ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Portocala s _) = s `elem` ["Tarocco", "Moro", "Sanguinello"]
ePortocalaDeSicilia _ = False


nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia [] = 0
nrFeliiSicilia (x@(Portocala s i):xs) = 
    (if ePortocalaDeSicilia x then i else 0) + nrFeliiSicilia xs
nrFeliiSicilia (_:xs) = nrFeliiSicilia xs


nrFeliiSicilia' :: [Fruct] -> Int
nrFeliiSicilia' l = sum [ i | x@(Portocala s i) <- l, ePortocalaDeSicilia x]


nrFeliiSicilia'' l = sum[ i | Portocala s i <- l, 
    s `elem` ["Tarocco", "Moro", "Sanguinello"]]

nrFeliiSicilia''' list = foldr ((+) . \(Portocala s i) -> i) 0 (filter ePortocalaDeSicilia list)

nrMereViermi :: [Fruct] -> Int
nrMereViermi [] = 0
nrMereViermi (x@(Mar s b):xs) = 
    (if b then 1 else 0) + nrMereViermi xs
nrMereViermi (_:xs) = nrMereViermi xs


nrMereViermi' list = sum[1 | x@(Mar s b) <- list, b]


type NumeA = String
type Rasa = String
data Animal = Pisica NumeA | Caine NumeA Rasa


vorbeste :: Animal -> String
vorbeste (Pisica _) = "Meow!"
vorbeste (Caine _ _) = "Woof!"

rasa :: Animal -> Maybe String
rasa (Pisica _) = Nothing
rasa (Caine _ r) = Just r


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
p2 = (Var "P" :|: Var "Q") :&: (Not(Var "P") :&: Not(Var "Q"))

p3 :: Prop
p3 = (Var "P" :&: (Var "Q" :|: Var "R")) :&: (((Not(Var "P") :|: Not(Var "Q")) :&: (Not(Var "P") :|: Not(Var "R"))))

instance Show Prop where
    show (Var x) = x
    show F = "False"
    show T = "True"
    show (Not p) = "(" ++ "~" ++ show p ++ ")"
    show (a :|: b) = "(" ++ show a ++ "\\/" ++ show b ++ ")"
    show (a :&: b) = "(" ++ show a ++ "&" ++ show b ++ ")"

test_ShowProp :: Bool
test_ShowProp = show (Not (Var "P") :&: Var "Q") == "((~P)&Q)"

type Env = [(Nume, Bool)]

impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a


eval :: Prop -> Env -> Bool
eval (Var v) env = impureLookup v env
eval T _ = True
eval F _ = False
eval (Not v) env = not (eval v env)
eval (a :|: b) env = (eval a env) || (eval b env)
eval (a :&: b) env = (eval a env) && (eval b env)

test_eval = eval  (Var "P" :|: Var "Q") [("P", True), ("Q", False)] == True

-- O formula in logica propozitionala este satisfiabila daca exista o atribuie de
-- valori de adevar pentru variabilele propozitionale din formula pentru care aceasta se evalueaza la True
variabile :: Prop -> [Nume]
variabile = nub . listAllVar
    where 
        listAllVar T  = []
        listAllVar F  = []
        listAllVar (Var v) = [v]
        listAllVar (Not p) = listAllVar p
        listAllVar (a :|: b) = listAllVar a ++ listAllVar b
        listAllVar (a :&: b) = listAllVar a ++ listAllVar b


test_variabile = variabile (Not (Var "P") :&: Var "Q") == ["P", "Q"]

envs :: [Nume] -> [Env]
envs [] = [[]]
envs (x:xs) = [ (x,y):e | y <- [False, True], e <- envs xs]

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



toateEvaluarile :: Prop -> [Bool]
toateEvaluarile prop  = map ( prop `eval`) (envs (variabile prop))

satisfiabila :: Prop -> Bool
satisfiabila prop = or (toateEvaluarile prop)

test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q") == True
test_satisfiabila2 :: Bool
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P") == False


valida :: Prop -> Bool
valida = and . toateEvaluarile
test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 = valida (Not (Var "P") :|: Var "P") == True