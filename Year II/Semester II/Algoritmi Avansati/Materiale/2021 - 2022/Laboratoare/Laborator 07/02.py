def intersectie(inecuatii, punct):
    xmaxim = 1000001
    ymaxim = 1000001
    xminim = -1000001
    yminim = -1000001

    for inecuatie in inecuatii:
        
        # punem coordonatele punctului in ecuatiei dreptei
        # si testam daca se afla in semiplan
        if inecuatie[0] * punct[0] + inecuatie[1] * punct[1] + inecuatie[2] >= 0:
            continue

        # aflam marginirile punctului dat
        
        # semiplan orizontal
        if inecuatie[0] == 0:
            if (-1) * inecuatie[2] / inecuatie[1] < punct[1]:
                yminim = max(yminim, (-1) * inecuatie[2] / inecuatie[1])
            else:
                ymaxim = min(ymaxim, (-1) * inecuatie[2] / inecuatie[1])

        # semiplan vertical
        else:
            if (-1) * inecuatie[2] / inecuatie[0] < punct[0]:
                xminim = max(xminim, (-1) * inecuatie[2] / inecuatie[0])
            else:
                xmaxim = min(xmaxim, (-1) * inecuatie[2] / inecuatie[0])

    # trebuie sa fie marginit pe toate axele
    # pentru a fi intr-un dreptunghi
    
    if xmaxim != 1000001 and ymaxim != 1000001 and xminim != -1000001 and yminim != -1000001:
        return("YES\n" + "{:.6f}".format((xmaxim - xminim) * (ymaxim - yminim)))
    
    return("NO")

inecuatii = []

n =  int(input())

# lista de liste cu valori [[a,b,c],..]
# corespuzatoare inecuatiei ax + by + c <= 0

for i in range(n):
    line = [int(x) for x in input().split()]

    inecuatii.append(line)

puncte = []

m = int(input())

for i in range(m):
    line = [float(x) for x in input().split()]

    puncte.append(line)

for punct in puncte:

    output = intersectie(inecuatii, punct)
    print(output)