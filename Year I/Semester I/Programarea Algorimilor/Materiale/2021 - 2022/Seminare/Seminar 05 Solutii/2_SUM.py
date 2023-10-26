v=[-7,-6,-5,-2,-1,0,1,2,3,4,5]
n=len(v)

#Solutie O(n**2), fara memorie suplimentara
print("Solutie O(n**2), fara memorie suplimentara:")
for i in range(n-1):
    for j in range(i+1,n):
        if v[i]+v[j] == 0:
            print(v[i], v[j])

#solutie O(n) cu vector de frecvente - pentru numere intregi mici, de exemplu mai mici decat 100:
#solutia se poate adapta  si pentru cazul in care vectorul nu este ordonat, parcurgand intai vectorul pentru a actualiza frecv, apoi pentru a afisa perechile
print("Solutie O(n) cu vector de frecvente")
frecv = [False for i in range(101)]
for i in range(n-1,-1,-1):
    if v[i]>0:
        frecv[v[i]]=True
    else:
        if frecv[-v[i]]==True:
            print(v[i],-v[i])

#solutie O(n) mediu cu dictionar - de fapt cu set,in dictionar toate cheile ar avea asociate valoarea True
#solutia se poate adapta  si pentru cazul in care vectorul nu este ordonat
print("Solutie O(n) cu dictionar/set")
frecv = set() #frecv={}
for i in range(n-1,-1,-1):
    if v[i]>0:
        frecv.add(v[i]) #frecv[v[i]]=True
    else:
        if -v[i] in frecv:
            print(v[i],-v[i])



#Solutie O(n), fara memorie suplimentara - doi indici i si j, unul parcurge sirul de la inceput, celalalt de la sfarsit
print("Solutie O(n), fara memorie suplimentara")
i=0
j=n-1
while i<j:
    if v[i]+v[j]==0:
        print(v[i], v[j])
        i += 1
        j -= 1
        while i<n and v[i-1]==v[i]:
            i+=1
        while j>0 and v[j+1] == v[j]:
            j-=1
    else:
        if v[i] + v[j] < 0:
            i += 1
        else:
            j -= 1