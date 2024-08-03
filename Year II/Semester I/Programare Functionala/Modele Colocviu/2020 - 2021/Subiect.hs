-- :l colocviu_Dima_Oana_Teodora_241.hs
import Data.List
import Data.Char
------------------------
--r_cifre_do
--ex1
--1)
r11do :: [String] -> Bool
r11do l 
      | null l = False
      | reverse h == h = True || t'
      | otherwise =t'
      where 
            h= head l 
            t= tail l 
            t'=r11do t
--Teste:
-- *Main> r11do ["ana", "are"]
--True
-- *Main> r11do ["maria", "ana", "are"]
--True
-- *Main> r11do ["maria", "are", "ion"] 
--False  
--2)
r12do :: [String] -> Bool
r12do l = length [ w | w<-l , reverse w==w] >0 
--Teste
-- *Main> r12do ["ana", "are"]
--True
-- *Main> r12do ["maria", "are", "ion"]
--False
--3)
r13do :: [String] -> Bool
r13do l = length (filter(\w-> reverse w == w) l) >0 
--Teste
-- *Main> r13do ["maria", "ana", "ion"]
--True
-- *Main> r13do ["maria", "are", "ion"]
--False
-- *Main> r13do []
--False
--4)
r14do :: [String] -> Bool
r14do l= r11do l==r13do l
-- *Main> quickCheck r14do
-- +++ OK, passed 100 tests.
-------------------------------------
--ex2

r22do :: [Int]-> [Int]
r22do l = foldr ( \ l b -> r23do l b ) [] l

r23do :: [Int] -> Int-> [Int]
r23do l b 
      | last l ==13 && b/=0 =  l : 0: (last l) :b  
      | last l == 13 && b==0 = l 0: (last l) 
      | last l==3 || last l==7 || last l==11 ||last l==101 && b==0 =  l :(last l):b
      |last l==3 || last l==7 || last l==11 || last l==101 && b/=0 = l :(last l):0:b
      |otherwise =  l: (last l) : b

Dupa instalare cu Chocolatey
https://www.haskell.org/platform/windows.html



Atentie! urmatoarele sunt in command prompt obisnuit (run as admin):



choco install haskell-dev
refreshenv



Se creaza un director de lucru, de exemplu exhaskell



command prompt (posibil sa fie nevoie ca admin)

 cd exhaskell (te duci in director)

 cabal update

 c:\Users\...\exhaskell> cabal install --lib --package-env . QuickCheck



Se creaza un fisier .hs (notepd/++ save Alltipes si numele)



import Test.QuickCheck



In acel director il stie