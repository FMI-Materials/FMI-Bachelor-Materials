#Siruri de caractere

#accesare, feliere s[0], s[-1], s[1:4]
#parcurgere for c in s
#operatori: +, *n, relationali >
#len, max, min
#CAUTARE: 
#operatori in, not in
#count, s.index(x,i,j) => ValueError, s.find -> -1 dc x nu exista, rfind, rindex, endswith
#MODIFICARE => obiect nou s=s.functie()

#stergem caracterul de pozitia k: s=s[:k]+s[k+1:]

#replace s=s.replace(vechi, nou[,nr_max_inlocuri]) default inlocuieste toate aparitiile
#lower(), upper(), title()
#islower(), isdigit(), isalpha()

#center

#IMPARTIRE si LIPIRE de siruri
#split
prop="ana    are mere"
ls=prop.split() #lista de cuvinte
print(ls)
ls=prop.split(" ") #un separator
print(ls)
ls=prop.split(" ",maxsplit=1) #un separator
print(ls)


#join
prop="ana    are mere"
ls=prop.split() #lista de cuvinte
print(ls)
s=" ".join(ls) #separator.join(lista de cuvinte)
print(s) #un singur spatiu intre cuvinte

prop="ana    are mere"
ls=prop.split(" ") #lista de cuvinte
print(ls)
s=" ".join(ls) #separator.join(lista de cuvinte)
print(s) #atatea spatii intre cuvinte cate erau in sirul initial

#format
x=10
y=14
#x=0b101
#10+14=24
print(x,"+",y,"=",x+y, sep="")
print("{}+{}={}".format(x,y,x+y))
print("{:8}+{}={:.2f}".format(x,y,x+y))

print(f"{x}+{y}={y}+{x}={x+y:.2f}")
