f=open("puncte.in")
d = {}
for linie in f:
    #print(linie.split(maxsplit=2))
    ls = linie.split(maxsplit=2)
    x = int(ls[0])
    y = int(ls[1])
    eticheta = ls[2].rstrip("\n")
    d[(x,y)] = eticheta #cheie tuplu -imutabil, nu mergea [x,y]
print(d)
f.close()

f=open("interogari.in")
for linie in f:
    x,y,operatie = [int(x) for x in linie.split()]
    if operatie==1: #interogarea etichetei punctului (x,y)
        """
        if (x,y) in d:
            eticheta = d[(x, y)]
        else:
            eticheta = "nu exista"
        print(f"({x},{y}) {eticheta}")
        """

        print(f"({x},{y}) {d.get((x,y),'nu exista')}")

        """
        try:
            print(f"({x},{y}) {d[(x, y)]}")
        except:
            print(f"({x},{y}) nu exista")
        """
    else:
        """
        if (x,y) in d:
            del d[(x,y)]
        """
        d.pop((x,y),"nu exista")
        """
        try:
            del d[(x,y)]
        except:
            pass
        """
print(d)
f.close()