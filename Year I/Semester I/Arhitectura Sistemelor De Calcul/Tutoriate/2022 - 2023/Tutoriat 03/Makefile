#Cred ca va va fi de mare ajutor la proiect!

#In loc sa recompilati si sa rulati puteti scrie in terminal: "make"
#In loc de "nume_cod_sursa.s" puneti numele programului vostru
#In loc de "nume_executabil" puneti numele de "output" al programului dupa
#compilare, puteti pune orice nume doriti voi, singura conditie este sa nu
#aiba nicio extensie( fara . )
#Puteti scrie comanda "make clean" daca doriti sa stergeti executabilul
#( comanda optionala )

#Creati un fisier "makefile" si scrieti in el codul de mai jos SAU 
#il puteti volosi codul prezent dupa ce ati modificar nume_executabil si
#nume_cod_sursa

run: nume_executabil
	./nume_executabil < input.txt

nume_executabil: nume_cod_sursa.s
	gcc -m32 nume_cod_sursa.s -o nume_executabil -no-pie

make clean:
	rm nume_executabil
