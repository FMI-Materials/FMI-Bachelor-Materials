{-
Gasiti mai jos limbajul unui minicalculator si o interpretare partiala. 
Calculatorul are o celulă de memorie, care are valoarea initiala  0.
Interpretarea instructiunilor este data mai jos.

Un program este o expresie de tip `Prog`iar rezultatul executiei este starea finala a memoriei. 
Testare se face apeland `prog test`. 
-}

data Prog  = On [Stmt]
data Stmt =
     Save Expr     -- evalueaza expresia și salvează rezultatul in Mem
   | NoSave Expr   -- evalueaza expresia, fără a modifica Mem 
data Expr =  Mem | V Int | Expr :+ Expr | If Expr Expr Expr

infixl 6 :+

type Env = Int   -- valoarea curentă a celulei de memorie

expr ::  Expr -> Env -> Int
expr = undefined

stmt :: Stmt -> Env -> Env
stmt = undefined 

stmts :: [Stmt] -> Env -> Env
stmts = undefined

prog :: Prog -> Env
prog (On ss) = stmts ss 0


test1 :: Prog
test1 = On [Save (V 3), NoSave (Mem :+ (V 5))]
test2 :: Prog
test2 = On [NoSave (V 3 :+ V 3)]

-- Teste pentru cerinta 1
test3 :: Prog
test3 = On [Save (V 3), Save (V 4)]
test4 :: Prog
test4 = On [NoSave (V 3), NoSave (Mem :+ (V 5))]

-- Teste pentru cerinta 2
test5 :: Prog
test5 = On [Save (If (V 0) (V 1) (V 2))]
test6 :: Prog
test6 = On [Save (If (V 1) (V 1) (V 2)), NoSave (V 5)]


{-CERINTE

1) (10pct) Finalizati definitia functiilor de interpretare.
2) (10 pct) Adaugati expresia `If e e1 e2` care se evaluează `e1` daca `e` are valoarea `0` si la `e2` in caz contrar.
3) (20pct)Definiti interpretarea  limbajului extins modificand functiile de interpretare astfel incat executia unui program
 sa intoarca starea memoriei si  lista valorilor calculate. 
Rezolvați subiectul 3) în același fișier redenumind funcțiile de interpretare.     


Indicati testele pe care le-ati folosit in verificarea solutiilor. 

-}

-- Ex 3
