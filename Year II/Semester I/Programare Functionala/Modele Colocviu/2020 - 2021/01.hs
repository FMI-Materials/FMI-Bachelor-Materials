
r21bd c = (c=='.' || c==';' || c==':' || c=='!' || c=='?' || c==')')
r22bd :: [Char] -> [Char]
r22bd [] = ""
r22bd [a] = [a]
r22bd (a:b:tail) = if a==' ' then
                       if r21bd b then
                          b:r22bd(tail)
                       else
                          a:b:r22bd(tail)
                    else
                        if b=='(' then
                           ' ':b:r22bd(tail)
                        else
                           a:b:r22bd(tail)

r23bd [] = ""
r23bd [a] = [a]
r23bd (a:b:tail) = if a==' ' then
                      if r21bd b then
                         b:r23bd(tail)
                      else
                         a:b:r23bd(tail)
                   else
                       if b=='(' then
                          ' ':b:r23bd(tail)
                       else
                          a:b:r23bd(tail)
r24bd l = r23bd(r22bd l)
main = print("hello")
