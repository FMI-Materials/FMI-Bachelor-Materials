#solutie cu split
p = input("propozitie : ")
s = input("cuvant cautat : ")
t = input ("inlocuire : ")
p = p.split(" ")
for i in range(len(p)):
    if p[i] == s:
        p[i] = t
p=" ".join(p)
print(p)

#solutii - cu inlocuire " "+s+" ", " "+t+" "- tema

