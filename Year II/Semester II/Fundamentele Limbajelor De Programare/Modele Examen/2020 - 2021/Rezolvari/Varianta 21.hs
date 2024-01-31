{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
{-# OPTIONS_GHC -Wno-overlapping-patterns #-}
{-
Gasiti mai jos limbajul unui minicalculator si o interpretare partiala. 
Memoria calculatorului este o stivă de valori (intregi), inițial vidă.

Un program este o listă de instrucțiuni iar rezultatul executiei este starea finală a memoriei.
Testare se face apeland `prog test`. 
-}

data Prog  = On [Stmt]
data Stmt
  = Push Int -- pune valoare pe stivă    s --> i s
  | Pop      -- elimină valoarea din vărful stivei            i s --> s
  | Plus     -- extrage cele 2 valori din varful stivei, le adună si pune rezultatul inapoi pe stivă i j s --> (i + j) s
  | Dup      -- adaugă pe stivă valoarea din vârful stivei    i s --> i i s
  | Loop [Stmt]

type Env = [Int]   -- corespunzator stivei care conține valorile salvate

stmt :: Stmt -> Env -> Env
stmt (Push x) env = x:env
stmt Pop (x:xi) = xi
stmt Pop [] = []
stmt Plus (x1:x2:xi) = x1+x2:xi
stmt Plus _ = []
stmt Dup (x:xs) = x:x:xs
stmt Dup [] = []
stmt (Loop ss) env = let env1 = stmts ss env in
                     if length env1 <= 1 then
                        env1
                     else
                        stmt (Loop ss) env1
                     

stmts :: [Stmt] -> Env -> Env
stmts si env = foldl (flip stmt) env si

prog :: Prog -> Env
prog (On ss) = stmts ss []

test1 = On [Push 3, Push 5, Plus]            -- [8]
test2 = On [Push 3, Dup, Plus]               -- [6]
test3 = On [Push 3, Push 4, Dup, Plus, Plus] -- [11]
test4 = On [Push 1, Push 2, Push 3, Push 4, Loop [Plus]] -- [10]

{-CERINTE

1) (10pct) Finalizati definitia functiilor de interpretare (aruncați excepții dacă stiva nu are suficiente valori pentru o instrucțiune)
2) (10 pct) Adaugati instrucțiunea `Loop ss` care evaluează repetat lista de instrucțiuni ss până când stiva de valori are lungime 1
   -- On [Push 1, Push 2, Push 3, Push 4, Loop [Plus]]  -- [10]
3) (20pct) Modificați interpretarea limbajului extins astfel incat interpretarea unui program / instrucțiune / expresie
   să nu mai arunce excepții, ci să aibă tipul rezultat `Maybe Env` / `Maybe Int`, unde rezultatul final în cazul în care
   execuția programului încearcă să scoată/acceseze o valoare din stiva de valori vidă va fi `Nothing`.
   Rezolvați subiectul 3) în același fișier redenumind funcțiile de interpretare.    
   
Indicati testele pe care le-ati folosit in verificarea solutiilor. 

-}

type EnvM = Maybe [Int]
stmtM :: Stmt -> EnvM -> EnvM
stmtM (Push x) (Just env) = return $ x:env
stmtM (Push _) _ = Nothing
stmtM Pop (Just (x:xi)) = return xi
stmtM Pop _ = Nothing
stmtM Plus (Just (x1:x2:xi)) = return $ x1+x2:xi
stmtM Plus _ = Nothing
stmtM Dup (Just (x:xs)) = return $ x:x:xs
stmtM Dup _ = Nothing 
stmtM (Loop ss) env = let env1 = stmtsM ss env in
                      case env1 of
                         (Just env1) -> if length env1 <= 1 then
                           return env1
                         else
                           stmtM (Loop ss) (Just env1)
                         Nothing -> Nothing
                         


stmtsM :: [Stmt] -> EnvM -> EnvM
stmtsM si env = foldl (flip stmtM) env si

progM :: Prog -> EnvM
progM (On ss) = stmtsM ss (return [])

test5 = On [Push 2, Push 3, Pop, Plus] -- Nothing
test6 = On [Push 2, Dup, Pop, Plus, Pop] -- Nothing
test7 = On [Push 1, Push 2, Push 3, Push 4, Loop [Plus, Plus]] -- Nothing