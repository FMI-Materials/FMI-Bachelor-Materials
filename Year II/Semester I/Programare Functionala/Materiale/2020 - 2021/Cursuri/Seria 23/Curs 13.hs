(return >=> k) a == k a
(\a -> return a >>= k) a == k a

return a >>= k == k a
