#cum impartim in cuvinte o propozitie cu mai multi separatori:spatiu,.

#varianta 1- inlocuim toti separatorii cu spatiu si folosim metoda split din str
#(facand cate un replace pentru fiecare separator s.replace(",","") sau folosind translate)
prop = "aceasta,   este... prima ora..., de seminar"
ls=prop.translate(str.maketrans(",.;"," "*3)).split(" ")
print(ls)

#varianta 2 -re.split("tipar") tipar -expresii regulate
import re
prop = "aceasta,  este... prima ora..., de seminar .,"
prop= prop.strip(",. ")
ls=re.split("[ ,.]",prop) #[]-multime de caractere
print(ls)
ls=re.split("[ ,.]+",prop) #[caractere]+-cuvinte de lungime cel putin 1 peste multimea de caractere
print(ls)
#re.sub - inlocuire tipar

#sa se afiseze cuv din propozitie ordonate lexicografic
prop = "aceasta,  este... prima ora..., de seminar .,"
print(" ".join(sorted(re.split("[ ,.]+",prop.strip(",. ")))))

#jurnal Anei
prop="Astăzi am cumpărat pâine de 5 RON, pe lapte am dat 10 RON, iar de 15 RON am cumpărat niște cașcaval"
#varianta 1 - parcurgem sirul caracter cu caracter si testam daca este cifra caracterul curent- formam un numar cifra cu cifra (isdigit(), int(Str)
#Tema

#varianta 2 -cu split si facem suma doar pentru cuvintele formate doar din cifre
ls=re.split("[ ,.!]+",prop)
print(ls)
#din ls pastram doar sirurile formate din cifre - pe care le transformam in int
numere=[]
for x in ls:
    if x.isdigit():
        numere.append(int(x))
rez=sum(numere)
#cu comprehensiune:
print(sum([int(x) for x in re.split("[ ,.!]+",prop) if x.isdigit()]))

#varianta 3
#impartim sirul folosind ca separatori orice caracter care nu este cifra
ls=re.split("\D+",prop) #\D-caracter care nu este cifra !!siruri vide la inceput si sfarsit
print(ls)