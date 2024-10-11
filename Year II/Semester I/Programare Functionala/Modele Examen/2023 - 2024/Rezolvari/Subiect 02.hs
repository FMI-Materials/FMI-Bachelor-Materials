-- ========== P3 ==========     
newtype ReaderM env a = ReaderM { runReaderM :: env -> Either String a }

instance Monad (ReaderM env) where
    return a = ReaderM (\_ -> Right a) 
    ma >>= k = ReaderM f
        where f env = case runReaderM ma env of
                        Left str -> Left str
                        Right a -> runReaderM (k a) env

instance Applicative (ReaderM env)
instance Functor (ReaderM env)

-- Only done P3 because the others ones are the same 
-- ======================== 
