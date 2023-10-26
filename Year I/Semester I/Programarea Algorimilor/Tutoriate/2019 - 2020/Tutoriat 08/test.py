# 3

def afis_punctaj(M, R):
    print("(", ",".join([str(x) for x in M]), ")", end=", ", sep="")
    p = sum(M)
    NM = M.copy()
    if p == R:
        return
    for i in range(0, len(NM)):
        NM[i] -= 1
        afis_punctaj(NM, R)
        NM[i] += 1

afis_punctaj([5, 4, 7], 14)