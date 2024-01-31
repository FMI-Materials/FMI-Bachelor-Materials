{-
Gasiti mai jos limbajul unui minicalculator si o interpretare partiala. 
Calculatorul are doua celule de memorie, care au valoarea initiala 0. Expresia `Mem := Expr` are urmatoarea semantica: 
`Expr` este evaluata, iar valoarea este pusa in `Mem`.  
Un program este o expresie de tip `Prog`iar rezultatul executiei este dat de valorile finale ale celulelor de memorie.
Testare se face apeland `run test`. 
-}


-- Monade folosite pentru punctul 3.
import Control.Monad.Writer
import Control.Monad.State

data Prog
    = Stmt ::: Prog
    | Off

data Stmt
    = Mem := Expr

data Mem
    = Mem1 | Mem2

data Expr
    = M Mem
    | V Int
    | Expr :+ Expr
    | Expr :/ Expr

infixl 6 :+
infix 3 :=
infixr 2 :::

type Env = (Int,Int)   -- corespunzator celor doua celule de memorie (Mem1, Mem2)


-- Parseaza expresii.
-- Arunca o eroare daca intampina o impartire la 0
expr ::  Expr -> Env -> Int
expr (M Mem1) (x, _) = x
expr (M Mem2) (_, x) = x
expr (V x) _ = x
expr (e1 :+ e2) env = let v1 = expr e1 env in
                      let v2 = expr e2 env in
                           v1 + v2
expr (e1 :/ e2) env = let v1 = expr e1 env in
                      let v2 = expr e2 env in
                          if v2 == 0 then
                              error "Eroare impartire la 0"
                          else
                              v1 `div` v2


-- Parseaza un statment, si updateaza memoria corespunzator.
stmt :: Stmt -> Env -> Env
stmt (Mem1 := e) env = let v = expr e env in
                                 (v, snd env)
stmt (Mem2 := e) env = let v = expr e env in
                                 (fst env, v)

-- Parseaza un program.
prog :: Prog -> Env -> Env
prog (s ::: p) env = let env1 = stmt s env in
                         prog p env1
prog Off env = env

-- Ruleaza un program, plecand de la env = (0, 0)
run :: Prog -> Env
run p = prog p (0, 0)


-- Exemple de programe
prg1 = Mem1 := V 3 ::: Mem2 := M Mem1 :+ V 5 ::: Off
prg2 = Mem2 := V 3 ::: Mem1 := V 4 ::: Mem2 := (M Mem1 :+ M Mem2) :+ V 5 ::: Off
prg3 = Mem1 := V 3 :+  V 3 ::: Off
prg4 = Mem1 := V 6 ::: Mem2 := (V 5 :/ V 2) ::: Off

-- Testam functionalitatile
-- toate variabilele definite mai jos au valoarea adevarat
test1 = run prg1 == (3, 8)
test2 = run prg2 == (4, 12)
test3 = run prg3 == (6, 0)
test4 = run prg4 == (6, 2)

{--
    Partea a 3-a
    Pentru a salva starea, am decis sa folosesc monada State Env
    De asemenea, pentru a putea trage dupa noi logurile, am decis sa folosesc 
    monada Writer. Astfel, folosesc un monad transformer, mai precis WriterT.
    M-am gandit sa tin state-ul ca fiind Maybe Env (pentru divizia la 0), dar 
    ar fi insemnat sa am 3 monade una intr-alta si devenea cam urat, asa ca 
    pentru a nu arunca o exceptie la imparirea la 0, consider rezultatul unei 
    impartiri gresite ca fiind 0.
--}

data StringWriter a = StringWriter { runStringWriter :: (a, [String]), getEnv :: a }

type M = StringWriter

type EnvM = M (Int,Int)

instance Show a => Show (StringWriter a) where
    show sw = let (a, b) = runStringWriter sw in
      "Output: " ++ show  b ++ "Value: " ++ show a

instance Monad StringWriter where
   return x = StringWriter (x, []) x
   sw >>= f = let (a, b) = runStringWriter sw in
              let (StringWriter (a1, b1) _) = f a in
                StringWriter (a1, b ++ b1) a1

instance Applicative StringWriter where
  pure = return
  a <*> b = do
    f <- a
    f <$> b

instance Functor StringWriter where
  fmap f a = f <$> a

exprM ::  Expr -> EnvM -> M Int
exprM (M Mem1) env = let (x, _) = getEnv env in
                         return x
exprM (M Mem2) env = let (_, x) = getEnv env in
                         return x
exprM (V x) _ = return x
exprM (e1 :+ e2) env = do
    v1 <- exprM e1 env
    v2 <- exprM e2 env
    return $ v1 + v2
exprM (e1 :/ e2) env = do
    v1 <- exprM e1 env
    v2 <- exprM e2 env
    if v2 == 0 then
        StringWriter (0, ["Eroare impartire la 0"]) 0
    else
        return $ v1 `div` v2

stmtM :: Stmt -> EnvM -> EnvM
stmtM (Mem1 := e) env = do
    v <- exprM e env
    e <- env
    StringWriter ((v, snd e), ["Mem1 setat la " ++ show v]) (v, snd e)
stmtM (Mem2 := e) env = do
    v <- exprM e env
    e <- env
    StringWriter ((fst e, v), ["Mem2 setat la " ++ show v]) (fst e, v)

-- Parseaza un program.
progM :: Prog -> EnvM -> EnvM
progM (s ::: p) env = do
    stmtM s env
progM Off env = env

-- Ruleaza un program, plecand de la env = (0, 0)
runM :: Prog -> EnvM
runM p = progM p $ return (0, 0)
