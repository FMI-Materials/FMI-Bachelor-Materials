{- Fie tipul de date Arb dat de definiția de mai jos. Aceste definiții vor fi folosite pentru toate exercițiile care urmează.

Pentru fiecare exercițiu, indicați testele pe care le-ați folosit în verificarea soluțiilor.  -}

{- (10pct) Finalizati definitia functiilor de interpretare astfel încât valoarea asociata 

unei expresii de forma `Nod op exps`  sa se obtina prin agregarea valorilor corespunzătoare elementelor

listei folosind operatia `op`. Pentru lista vidă se va folosi elementul neutru al operației `op`.

Valorile identificatorilor (literali de forma `Id str`) se vor obține prin căutarea asocierii `(str, v)` in stare.

În cazul în care nu se găsește o valoare pentru variabilă, se va afișa eroarea "variabila negasita" și se va încheia execuția. -}

type Val = Int
data Operatie = Add
data Lit = V Val | Id String
data Arb
   = Leaf Lit
   | Node Operatie [Arb]

type Stare = [(String, Val)]   -- valori pentru identificatorii (`Id x`) din arbore

eval ::  Arb -> Stare -> Val
eval (Leaf v) env = val v env
eval (Node Add []) _ = 0
eval (Node Add (x:xs)) env = let v = eval x env in
                             let rest = eval (Node Add xs) env in
                             v + rest

val :: Lit -> Stare -> Val
val (V v) _ = v
val (Id i) env = case lookup i env of
                    Nothing -> error "variabila negasita"
                    (Just x) -> x


test :: Val -> Bool
test = (/= 0)

-- Teste
test1 :: Bool
test1 = eval arb1 [] == 3

test2 :: Bool
test2 = eval arb2 [("a", 10)] == 21 -- Genereaza eroarea: variabila negasita

test3 :: Bool
test3 = eval arb2 [("a", 10), ("b", 11)] == 21

test4 :: Bool
test4 = eval arb3 [("a", 10), ("b", 11)] == 26

arb1 :: Arb
arb1 = Node Add [Leaf (V 1), Leaf (V 2)]

arb2 :: Arb
arb2 = Node Add [Node Add [Leaf (Id "a"), Leaf (Id "b")]]

arb3 :: Arb
arb3 = Node Add [Node Add [Leaf (Id "a"), Leaf (Id "b")], Leaf (V 5)]