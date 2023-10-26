import Data.List (nub)
import Data.Maybe (fromJust)
import Test.QuickCheck

type Nume = String
data Prop
  = Var Nume
  | F
  | T
  | Not Prop
  | Prop :|: Prop
  | Prop :&: Prop
  deriving (Eq, Read)
  --deriving (Eq, Read, Show)
--precedenta operatorilor
--infixR -> right
-- numerele sunt nivelurile de precedenta ( 0-> 9)
infixr 2 :|:
infixr 3 :&:

-----------------Formule--> Expresii de tip Prop-----------
--ex1.1
p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

--ex1.2
p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: (Not (Var "P") :&: Not (Var "Q"))

--ex1.3
p3 :: Prop
p3 =   (Var "P" :&: (Var "Q" :|: Var "R")) :&:(((Not (Var "P")) :|: (Not (Var "Q"))) :&: ((Not (Var "P")) :&: (Not (Var "R"))))

--ex2
instance Show Prop where
  show (Var p) = p
  show F = "0" --nu poate fi number pt ca te duce in String
  show T = "1"
  show (Not prop) = "(~" ++ (show prop) ++ ")"
  show (prop1 :|: prop2) = "(" ++ show prop1 ++ "|" ++ show prop2 ++ ")"
  show (prop1 :&: prop2) = "(" ++ show prop1 ++ "&" ++ show prop2 ++ ")"
 
test_ShowProp :: Bool
test_ShowProp = show (Not (Var "P") :&: Var "Q") == "((~P)&Q)"

--Mediu de evaluare (Pt evaluarea expresiilor logice)
type Env = [(Nume, Bool)]
--putem folosi lookup pt obtinerea valorii asociata unui Nume in Env

--ca lookup doar ca genereaza eroare daca nu o gaseste
impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a

--ex3
eval :: Prop -> Env -> Bool
eval (Var prop) env = impureLookup prop env
eval F _ = False
eval T _ = True
eval (Not prop) env = not $ eval prop env
eval (prop1 :|: prop2) env = (eval prop1 env )|| (eval prop2 env)
eval (prop1 :&: prop2) env = (eval prop1 env) && (eval prop2 env)
--eval (prop1 :->: prop2) env = not (eval prop1 env) || (eval prop2 env)

--mediu de evaluare:  [("P", True), ("Q", False)]
--eval p1  [("P", True), ("Q", False)]
test_eval = eval  (Var "P" :|: Var "Q") [("P", True), ("Q", False)] == True

--ex4 ----Satisfiabilitate----------
--functie care colecteaza lista tuturor variabilelor dintr-o formula
--functia nub elimina duplicatele dintr-o lista
variabile :: Prop -> [Nume]
variabile (Var prop) = [prop]
variabile (Not prop) = variabile prop
variabile (prop1 :|: prop2) = nub(variabile prop1 ++ variabile prop2)
variabile (prop1 :&: prop2) = nub(variabile prop1 ++ variabile prop2)
--variabile (prop1 :->: prop2) = nub(variabile prop1 ++ variabile prop2)
 
test_variabile = variabile (Not (Var "P") :&: Var "Q") == ["P", "Q"]

--ex5
gen:: Int-> [[Bool]] --gen 2 =[[False, False], [True, False], [True, True]]
gen 0 =[]
gen 1=[[False], [True]]
gen n= ls1 ++ ls2
    where 
      ls= gen (n-1)
      ls1 =[False: x| x<-ls] 
      ls2= [True: x | x<-ls]


envs :: [Nume] -> [Env]
envs xs = map ( xs `zip`) (gen (length xs))

 
test_envs = envs ["P", "Q"] == [ 
      [ ("P",False), ("Q",False)], [ ("P",False), ("Q",True)],
      [ ("P",True), ("Q",False)], [ ("P",True), ("Q",True)] 
      ]

--ex6
evals :: Prop-> [Bool]
evals prop= map (eval prop) (envs(variabile prop))

satisfiabila :: Prop -> Bool
satisfiabila prop = or (evals prop) 
 
test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q") == True
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P") == False

--ex7
valida :: Prop -> Bool
valida prop= and (evals prop) 

test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 = valida (Not (Var "P") :|: Var "P") == True

--ex8
tabelAdevar :: Prop -> String
tabelAdevar p = concat [(concat [btc(x) ++ "\t" | x <- v]) ++ "|\t" ++ btc(r) ++ "\n" | (v, r) <- zip values result]
                where
                varbls = variabile p
                values = gen(length(varbls))
                result = map (eval p) (envs (varbls))
                btc x = if(x) then "T" else "F"
var :: [String] -> String --functie auxiliara care im concateneaza o lista de stringuri
var [x]=x
var (h:t)= h++ "\t" ++ var t

afisareTabelAdevar :: Prop -> IO()
afisareTabelAdevar p  = putStrLn$(  var (variabile p)++"\t|\t" ++ show p ++ "\n"++ 
                        "-\t-\t|\t----------\n"++tabelAdevar p)
--sau
tabelAdevar1 :: Prop -> [String]
tabelAdevar1 p = map (\env-> if (eval p env)==True then (aux1 env) ++ "T\n" else  (aux1 env) ++ "F\n") (envs (variabile p ) )
--variabile p => ["p", "q"]
--show p => (p&(~q))
--envs variabile p=> valori adevar
--eval p env => valoare expresie

--transforma o lista de string-uri intr-un sir de caractere
aux:: [String] -> String
aux []= ""
aux l= head l  ++ aux (tail l)

--transforma un env intr-un sir de caractere
aux1:: Env -> String
aux1 []=""
aux1 env = if snd (head env) ==True then "T "++ aux1 (tail env) else "F "++ aux1 (tail env)

afisare:: Prop -> String
afisare p = aux (variabile p) ++ (show p) ++"\n" ++ aux (tabelAdevar1 p)
--apel cu putStrLn$ afisare
--ex 10

echivalenta :: Prop -> Prop -> Bool
echivalenta p1 p2 = and (map (\(x, y) -> x == y) (map (eval p1) (envs (variabile (p1 :|: p2))) `zip` map (eval p2) (envs (variabile (p1 :|: p2)))))

 
test_echivalenta1 = True == (Var "P" :&: Var "Q") `echivalenta` (Not (Not (Var "P") :|: Not (Var "Q")))
test_echivalenta2 = False == (Var "P") `echivalenta` (Var "Q")
test_echivalenta3 = True == (Var "R" :|: Not (Var "R")) `echivalenta` (Var "Q" :|: Not (Var "Q"))