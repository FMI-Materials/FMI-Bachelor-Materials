

["na","x","lal"] >>= (\x -> [length x, ord (head x)])

[2, 113, 1, 124, 3, 111]



newtype Writer log a = Writer { runWriter :: ( a , log ) }


data Writer log a = Writer (a, log)

runWriter :: Writer log a -> (a, log)
runWriter (Writer (x, logx)) = (x, logx)



newtype Reader env a = Reader { runReader :: env -> a }

data Reader env a = Reader (env -> a)

runReader :: Reader env a -> env -> a
runReader (Reader f) = f


local f r = Reader (runReader r . f)


runReader (local f r) env = (runReader r . f) env = runReader r (f env)



ma :: Reader env a
k :: a -> Reader env b

ma >>= k = Reader f
  where
    f :: env -> b
    f env = runReader (k a) env
      where
        a = runReader ma env


var :: String -> Reader Env Bool
var x = do
  env <- get
  Just b <- lookup x env
  return b
  

newtype State state a = State { runState :: state -> (a, state) }

data State state a = State (state -> (a, state))

runState :: State state a -> state -> (a, state)
runState (State f) = f

ma :: State state a
runState ma :: state -> (a, state)

k :: a -> State state b


instance Monad (State state) where
  return a = State (\state -> (a, state))
  (ma >>= k) :: State state b = State f
    where
      f state = (b, bstate)
        where
          (a, astate) = runState ma state
          (b, bstate) = runState (k a) astate
  
  
set :: state -> State state ()
set s = State (\_ -> ((), s))

modify :: (state -> state) ->  State state ()
modify f = do
  s <- get
  let s' = f s
  set s'

set s === modify (const s)
  

  
modify f = State ( \ s − > ( () , f s ) )


  
  
  
  
  
rnd
  = do
    modify ( \ seed − > cMULTIPLIER ∗ seed + cINCREMENT)
    get
  
  
rnd :: State Word32 Word32

runState rnd 0

runState (modify ( \ seed − > cMULTIPLIER ∗ seed + cINCREMENT) >>= (\_ -> get)) 0

f 0



get :: State Word32 Word32
get = State (\seed -> (seed, seed))

  
  
runState (ma >>= k) 0  = runState get ( cMULTIPLIER ∗ 0 + cINCREMENT) === (cMULTIPLIER ∗ 0 + cINCREMENT,  cMULTIPLIER ∗ 0 + cINCREMENT)

  
runState (modify ( \ seed − > cMULTIPLIER ∗ seed + cINCREMENT)) 0 = ( () , cMULTIPLIER ∗ 0 + cINCREMENT) )
  
  



















