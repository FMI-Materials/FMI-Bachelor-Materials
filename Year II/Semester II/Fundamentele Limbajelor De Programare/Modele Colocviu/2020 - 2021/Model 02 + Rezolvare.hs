{-
---------- Ex 1 si 2 ---------
  - finalizati definitia functiilor de interpretare 
  - aruncați excepții dacă stiva nu are suficiente valori 
  - adaugati instrucțiunea `Loop ss` care evaluează repetat lista de instrucțiuni ss
    până când stiva de valori are lungime 1
   -- On [Push 1, Push 2, Push 3, Push 4, Loop [Plus]]  -- [10]
-}
data Prog  = On [Stmt]

data Stmt
  = Push Int -- pune valoare pe stivă    s --> i s
  | Pop      -- elimină valoarea din vărful stivei            i s --> s
  | Plus     -- extrage cele 2 valori din varful stivei, le adună si pune rezultatul inapoi pe stivă i j s --> (i + j) s
  | Dup      -- adaugă pe stivă valoarea din vârful stivei    i s --> i i s
  | Loop [Stmt]
 
type Env = [Int]   -- corespunzator stivei care conține valorile salvate
 
testLength :: [Int] -> Bool 
testLength l = if length l > 0 then True else False  
 
stmt :: Stmt -> Env -> Env -- Stmt -> [Int] -> [Int]
stmt (Push n) env = env ++ [n] -- 2 : [1,2]
stmt Pop [x] = []
stmt Pop env = if testLength env 
                  then head env : (stmt Pop (tail env)) 
                      else error "Nu sunt elemente in stiva" -- [1,2,3] => [1,2]
stmt Plus env = if length env >= 2 then let 
                                              x = env !! (length env -1)
                                              y = env !! (length env -2)
                                              envNou = stmt Pop env
                                              envN = stmt Pop envNou
                                        in 
                                          envN ++ [x+y] -- [1,2,3] => [1,5]
                else error "Nu sunt destule elemente"
stmt Dup env = env ++ [env !! (length env -1)] --[1,2,3] => [1,2,3,3]
stmt (Loop l ) env = if (length env) <= 1 then env else stmt (Loop l) (stmts l env)
-- stmt (Loop [Plus]) [1,2,3,4] => [10] --aplica repetat plus pana la lungimea 1

stmts :: [Stmt] -> Env -> Env
stmts [] env = env
stmts (h:t) env = let
                    envNou = stmt h env
                  in 
                    stmts t envNou
 
prog :: Prog -> Env
prog (On l) = stmts l []

test1 = On [Push 3, Push 5, Plus] -- [8]
test2 = On [Push 3, Push 5, Push 7] -- [3,5,7]
test3 = On [Push 6, Push 2, Pop, Plus]  -- "Nu sunt destule elemente"
test4 = On [Pop] -- "Nu sunt elemente in stiva"
test5 = On [Push 1, Push 2, Push 3, Push 4, Loop [Plus]] -- [10]


{- 
------- Ex 3 ------------
Modificați interpretarea limbajului extins astfel incat interpretarea unui program / instrucțiune / expresie
să nu mai arunce excepții, ci să aibă tipul rezultat `Maybe Env` / `Maybe Int`, unde rezultatul final în cazul în care
execuția programului încearcă să scoată/acceseze o valoare din stiva de valori vidă va fi `Nothing`.
Rezolvați subiectul în același fișier redenumind funcțiile de interpretare.    

-}
type M = Maybe -- nu mai trebuie scrisa pt ca e deja monada

interpProg :: Prog -> M Env -- Prog -> Maybe (Just/Nothing) [Int]
interpProg (On l) = interpStmts l (Just [])

interpStmts :: [Stmt] -> M Env -> M Env
interpStmts [] env = env
interpStmts (h:t) env = let
                    envNou = interpStmt h env
                  in 
                    interpStmts t envNou

interpStmt :: Stmt -> M Env -> M Env -- Stmt -> Maybe [Int] -> Maybe [Int]
interpStmt (Push n) Nothing = Nothing 
interpStmt (Push n) (Just env) = return (env ++ [n]) -- interpStmt (Push 2) (Just []) => Just [2]

interpStmt Pop Nothing = Nothing
interpStmt Pop (Just [x]) = return []
interpStmt Pop (Just env) = if testLength env 
                              then return (head env : (stmt Pop (tail env))) 
                                else Nothing -- interpStmt (Pop) (Just [2,3]) => Just [2]

interpStmt Plus Nothing = Nothing
interpStmt Plus (Just env) = if length env >= 2 then let 
                                              x = env !! (length env -1)
                                              y = env !! (length env -2)
                                              envNou = stmt Pop env
                                              envN = stmt Pop envNou
                                              in 
                                              return (envN ++ [x+y]) 
                                              else Nothing -- interpStmt Plus (Just [1,2,3]) => Just [1,5]

interpStmt Dup Nothing = Nothing
interpStmt Dup (Just env) = return (env ++ [env !! (length env -1)]) 
-- interpStmt Dup (Just [1,2]) => Just [1,2,2]

interpStmt (Loop l ) Nothing = Nothing
interpStmt (Loop l ) (Just env) = if (length env) <= 1 then return env else return (stmt (Loop l) (stmts l env))
-- interpStmt(Loop [Plus]) (Just [1,2,3,4]) => Just [10] --aplica repetat plus pana la lungimea 1

test6 = On [Push 3, Push 5, Plus] -- Just [8]
test7 = On [Push 3, Push 5, Push 7] -- Just [3,5,7]
test8 = On [Push 6, Push 2, Pop, Plus]  -- Nothing
test9 = On [Pop] -- Nothing
test10 = On [Push 1, Push 2, Push 3, Push 4, Loop [Plus]] -- Just [10]
