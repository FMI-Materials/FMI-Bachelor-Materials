import Data.Char

r11bd [] = 1
r11bd (a:tail) = if (elem (toLower a) "haskell") then
                     10 * r11bd(tail)
                 else
                     1 * r11bd(tail)

r12bd l = product(map (\x -> if elem (toLower x) "haskell" then 10 else 1) l)

r13bd l = foldr (\a accum -> if elem (toLower a) "haskell" then accum*10 else accum*1) 1 l 
r14bd l = (r11bd l) == (r13bd l)
main = print("hello")
