def intersectie(inecuatii):
    xmaxim = 1000001
    ymaxim = 1000001
    xminim = -1000001
    yminim = -1000001

    for inecuatie in inecuatii:

        # calculam valorile extreme pentru fiecare semiplan

        leftbound = -1000001
        rightbound = 1000001
        upperbound = 1000001
        lowerbound = -1000001

        # daca e semiplan orizontal
        if inecuatie[0] == 0:
            if inecuatie[1] < 0:
                lowerbound = (-1) * inecuatie[2] / inecuatie[1]
            else:
                upperbound = (-1) * inecuatie[2] / inecuatie[1]

        # daca este semiplan vertical
        else:
            if inecuatie[0] < 0:
                leftbound = (-1) * inecuatie[2] / inecuatie[0]
            else:
                rightbound = (-1) * inecuatie[2] / inecuatie[0]

        # daca e semiplan orizontal
        if inecuatie[0] == 0:
            yminim = max(yminim, lowerbound)
            ymaxim = min(ymaxim, upperbound)

        # daca e semiplan vertical
        else:
            xminim = max(xminim, leftbound)
            xmaxim = min(xmaxim, rightbound)

    if yminim > ymaxim or xminim > xmaxim:
        return "VOID"
    elif xminim != yminim != -1000001 and xmaxim != ymaxim != 1000001:
        return "BOUNDED"
    else:
        return "UNBOUNDED"

inecuatii = []

n =  int(input())

# lista de liste cu valori [[a,b,c],..]
# corespuzatoare inecuatiei ax + by + c <= 0

for i in range(n):
    line = [int(x) for x in input().split()]

    inecuatii.append(line)

output = intersectie(inecuatii)

print(output)