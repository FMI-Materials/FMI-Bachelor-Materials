#str.translate - inlocuirea simultana a mai multor caractere + stergerea mai multor caractere
#translate - parametru un tabel de inlocuiri (dictionar) care se obtine folosind metdoa maketrans

s="aceasta este prima  ora"
#inlocuim a->b e->f
tabel = str.maketrans("ae","bf")#sir1- caracterele pe care vrem sa le inlocuim,
# sir2 -caracterele corespunzatoare cu care inlocuim; sir1 si sir2 tb sa aiba aceeasi lungime;
# se va inlocui sir1[i]->sir2[i]
#se poate apela cu "".maketrans, s.maketrans- nu are nevoie de un obiect pt a fi apelat=>
# il putem apelca cu tip.maketrans
print(tabel)
s=s.translate(tabel)
print(s)

#putem sterge mai multe caractere
# Exp: inlocuim a->b + stergem semnele de punctuatie
s="aceasta,, este., prima  ora"
s=s.translate(str.maketrans("a","b",",.")) #sir1,sir2, sir3-sirul caracterelor care vor fi sterse
print(s)

#daca vrem doar stergerea semnelor
s="aceasta,, este., prima  ora"
s=s.translate(str.maketrans("","",",.")) #sir1,sir2, sir3-sirul caracterelor care vor fi sterse
print(s)

#inlocuirea mai multor  caractere cu siruri (nu neaparat tot cu caractere)
s="1 mar 1 creion 2 struguri"
d={"1":"un", "2":"doi"}
s=s.translate(str.maketrans(d))
print(s)



