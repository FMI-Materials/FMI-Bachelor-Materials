#varianta 1 - citirea intregului fisier returnat ca str
f=open("propozitii.in")
s=f.read() #corespunzator sfarsitului de linie => \n in sir
print(s)
print(repr(s))
f.close()
print("-------")
#varianta 2.1 -  citire linie cu linie folosind readline
f=open("propozitii.in")
s=f.readline() #include si caracterul corespunzator sfarsitului de linie => \n in sir
while s!="":
    print(repr(s))
    s=f.readline()
f.close()

print("--------")
#varianta 2.2 -  citire linie cu linie iterator
f=open("propozitii.in")
s=f.readline()
print(repr(s))
for linie in f:
    print(repr(linie))

f.close()