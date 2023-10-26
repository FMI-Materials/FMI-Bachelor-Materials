s = input()
k = int(input())
copie_s=s
#un sir nu se poate modifica, orice modificare => obiect nou

#Varianta 1 - sir nou in care ignoram pozitia k
rez = ""
for i in range(len(s)):
    if i!=k:
        rez += s[i]
s = rez
print(s)

#varianta 2 - cu feliere
s=copie_s
s = s[:k] + s[k+1:]
print(s)
