fin = open("date.in")

n = int(fin.readline())
alfabet = fin.readline().split()
q0 = int(fin.readline())
qFinale = [int(x) for x in fin.readline().split()]
tranzitii = dict()
tranzitiiInverse = dict()
loopTranzitii = dict()
for i in range(n + 2):
    tranzitii[i] = []
    tranzitiiInverse[i] = []
    loopTranzitii[i] = []
for i in fin:
    a, lit, b = i.split()
    a = int(a)
    b = int(b)
    if a != b:
        tranzitii[a].append((lit, b))
        tranzitiiInverse[b].append(a)
    else:
        loopTranzitii[a].append(lit + "*")

# creez o noua stare finala unica
for i in qFinale:
    tranzitii[i].append(("", n))
    tranzitiiInverse[n].append(i)

# creez o noua stare initiala
tranzitii[n + 1].append(("", q0))
tranzitiiInverse[q0].append(n + 1)
q0 = n + 1

fin.close()


def eliminareStare(i):
    for qIntrare in tranzitiiInverse[i]:
        if qIntrare <= i:
            continue
        for inTranzitie in tranzitii[qIntrare]:
            if inTranzitie[1] == i:
                for outTranzitie in tranzitii[i]:
                    if outTranzitie[1] <= i:
                        continue
                    for loopTranzitie in (loopTranzitii[i] if len(loopTranzitii[i]) > 0 else [""]):
                        s = inTranzitie[0] + loopTranzitie + outTranzitie[0]
                        if qIntrare != outTranzitie[1]:
                            t = (s, outTranzitie[1])
                            if t not in tranzitii[qIntrare]:
                                tranzitii[qIntrare].append(t)
                            if qIntrare not in tranzitiiInverse[outTranzitie[1]]:
                                tranzitiiInverse[outTranzitie[1]].append(qIntrare)
                        else:
                            s = "(" + s + ")*"
                            if s not in loopTranzitii[outTranzitie[1]]:
                                loopTranzitii[outTranzitie[1]].append(s)


for i in range(n):
    eliminareStare(i)

reg = None
for i in tranzitii[n + 1]:
    if i[1] == n:
        if reg is None:
            reg = "(" + i[0] + ")"
        else:
            reg += " + (" + i[0] + ")"

print(reg)
