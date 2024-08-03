import Data.Char
import Data.List
--ex1
--cittire sir de la tastatura
prelStr s = map toUpper s
ioString = do
            s <- getLine
            putStrLn $ "Intrare\n" ++ s
            let sout = prelStr s
            putStrLn $ "Iesire\n" ++ sout
--ex2
--citire de la tastatura numar
prelNo n = sqrt n
ioNumber = do
            n <- readLn :: IO Double -- tipul numarului
            putStrLn $ "Intrare\n" ++ (show n) --show 3 => "3"
            let nout = prelNo n
            putStrLn $ "Iesire"
            print nout  --afisare rezultat
--ex3
--citire fisier de intrare afisare rez in fisier de iesire
--prelStr s = map toUpper s
inputFile = do
            sin <- readFile "Input.txt" --readFile returneaza mereu rezultat de tipul String
            putStrLn $ "Intrare\n" ++ sin --afisare pe ecran
            let sout = prelStr sin        
            putStrLn $ "Iesire\n" ++ sout --afisare pe ecran
            writeFile "Output.txt" sout    --afisare in fisier

----------Exercitii----------