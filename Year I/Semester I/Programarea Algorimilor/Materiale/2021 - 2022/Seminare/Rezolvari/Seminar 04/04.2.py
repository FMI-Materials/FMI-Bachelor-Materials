def pozitiv(x):
    return x>0



def filtreaza(*numere,functie=None):
    if functie is None:
        return list(numere)
    """
    ls=[]
    for nr in numere:
        if functie(nr):
            ls.append(nr)
            
    return ls
    """
    return [nr for nr in numere if functie(nr)]

print(filtreaza(3,-1,6,8,-3,functie=pozitiv))

print(filtreaza("ana","are","10","mere",functie=str.isalpha))

print(filtreaza(3,-1,6,8,-3))

#suplimentar - exista filter si map
print(*filter(pozitiv,[3,-1,6,8,-3]))
print(*filter(None,[3,-1,6,8,0,-3]))
ls=[3,-1,6,8,0,-3]
print(list(map(abs,ls))) #aplica functia data ca prim parametru fiecaruri elemen al listei (abs(x) for x in ls)