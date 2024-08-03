s = input()
cs=s

greseala = input()
corectare = input()

#a)
s = s.replace(greseala, corectare)
print(s)

#b)
s=cs
k = s.count(greseala)

if k > 2:
    print("textul contine prea multe greseli, doar 2 au fost corectate")

    s = s.replace(greseala, corectare, 2)
    print(s)


