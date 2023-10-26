foldr :: (a -> b -> b) -> b -> [a] -> b
foldr op neutru [] = neutru
foldr op neutru (a:as) = a `op` (foldr op neutru as)


-- foldr op neutru [x, y, z] == x `op` (y `op` (z `op` neutru))

foldr op neutru = agg
  where
    agg [] = neutru
    agg (a:as) = a `op` agg as


