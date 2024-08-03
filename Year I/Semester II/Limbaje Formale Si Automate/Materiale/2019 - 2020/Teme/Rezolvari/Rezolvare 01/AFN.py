def AFN(stare,cuv):
    if not cuv and stare in Final:    #daca cuvantul s-a terminat si a ajuns intr-o stare finala, cuvantul este acceptat
        global ok
        ok=1
    elif cuv and ok==0:             #altfel ma plimb prin noduri
        for x in L:
            if x[2] == cuv[:1] and x[0] == stare:        #daca starea curenta are arc cu litera din cuvantul curent apelez recursiv functia
                AFN(x[1],cuv[1:])


f=open("AFN.in")
Initial=f.readline().strip()                            # citesc starea initiala
Final=[x for x in f.readline().split()]                 # citesc starile finale
cuv=f.readline().strip()                                # citesc cuvantul ce trebuie verificat de automat
L=[(line.split()[0],line.split()[1],line.split()[2]) for line in f.readlines()]     #citesc tranzitiile sub forma: din starea 1 merge in starea 2 cu litera a
ok=0
#S = []          #pentru verificarea tranzitiilor
#S.append(Initial)
#stiva, lambda
for x in L:
    if x[0] == Initial and x[2]==cuv[:1]:
        #S.append(x[1])
        AFN(x[1],cuv[1:])
        #S=S[:-1]
    elif cuv=='lambda' and Final.count(Initial) == 1:   #daca avem lambda, verific daca starea initiala este si stare finala
        ok=1
if ok==1:
    print("Cuvantul este acceptat")
else:
    print("Cuvantul nu este acceptat")

 #bbabaaa