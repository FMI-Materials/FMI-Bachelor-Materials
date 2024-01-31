{-
Gasiti mai jos limbajul unui minicalculator si o interpretare partiala. 
Memoria calculatorului este o stivă de valori (intregi), inițial vidă.
Un program este o listă de instrucțiuni iar rezultatul executiei este starea finală a memoriei.
Testare se face apeland prog test. 
-}

data Prog  = On [Stmt]
data Stmt
  = Push Int -- pune valoare pe stivă    s --> i s
  | Pop      -- elimină valoarea din vărful stivei            i s --> s
  | Plus     -- extrage cele 2 valori din varful stivei, le adună si pune rezultatul inapoi pe stivă i j s --> (i + j) s
  | Dup      -- adaugă pe stivă valoarea din vârful stivei    i s --> i i s

type Env = [Int]   -- corespunzator stivei care conține valorile salvate

stmt :: Stmt -> Env -> Env
stmt   = undefined

stmts :: [Stmt] -> Env -> Env
stmts   = undefined

prog :: Prog -> Env
prog (On ss) = stmts ss []

test1 = On [Push 3, Push 5, Plus]            -- [8]
test2 = On [Push 3, Dup, Plus]               -- [6]
test3 = On [Push 3, Push 4, Dup, Plus, Plus] -- [11]

{-CERINTE

1) (10pct) Finalizati definitia functiilor de interpretare (aruncați excepții dacă stiva nu are suficiente valori pentru o instrucțiune)
2) (10 pct) Adaugati instrucțiunea Loop ss care evaluează repetat lista de instrucțiuni ss până când stiva de valori are lungime 1
   -- On [Push 1, Push 2, Push 3, Push 4, Loop [Plus]]  -- [10]
3) (20pct) Modificați interpretarea limbajului extins astfel incat interpretarea unui program / instrucțiune / expresie
   să nu mai arunce excepții, ci să aibă tipul rezultat Maybe Env / Maybe Int, unde rezultatul final în cazul în care
   execuția programului încearcă să scoată/acceseze o valoare din stiva de valori vidă va fi Nothing.
   Rezolvați subiectul 3) în același fișier redenumind funcțiile de interpretare.

Indicati testele pe care le-ati folosit in verificarea solutiilor. 
-}
