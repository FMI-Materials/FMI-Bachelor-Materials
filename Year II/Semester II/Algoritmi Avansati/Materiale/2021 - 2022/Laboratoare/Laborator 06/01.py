# pozitia unui punct fata de un poligon

def determinant(p, q, r):
    
    det = q[0] * r[1] + p[0] * q[1] + p[1] * r[0]
    det = det - q[0] * p[1] - r[0] * q[1] - r[1] * p[0]

    return det
    

def estePeLatura(punct, poligon):

    check = False

    n = len(poligon)
    for i in range(n):
        if determinant(poligon[i%n], poligon[(i+1)%n], punct) == 0:
            check = True

    return check

def seIntersecteaza(latura1, latura2):
    check = True

    # verificam daca coordonatele primei laturi se afla
    # de o parte si de a alta a celei de a doua laturi

    if determinant(latura1[0], latura2[0], latura2[1]) > 0:
        semn1 = "+"
    else:
        semn1 = "-"

    if determinant(latura1[1], latura2[0], latura2[1]) > 0:
        semn2 = "+"
    else:
        semn2 = "-"

    if semn1 == semn2:
        check = False

    # verificam daca coordonatele celei de a doua laturi se afla
    # de o parte si de a alta a primei laturi

    if determinant(latura2[0], latura1[0], latura1[1]) > 0:
        semn1 = "+"
    else:
        semn1 = "-"

    if determinant(latura2[1], latura1[0], latura1[1]) > 0:
        semn2 = "+"
    else:
        semn2 = "-"

    if semn1 == semn2:
        check = False

    return check

def numarIntersectii(punct, punctDeparte, poligon):
    l1 = [punct, punctDeparte]
    count = 0

    n = len(poligon)

    for i in range(n):
        l2 = [poligon[i%n], poligon[(i+1)%n]]
        if seIntersecteaza(l1, l2) == True:
            count = count + 1

    return count

# main entry

poligon = []
puncte = []
xmax = -100000
ymax = -100000

n = int(input())

for i in range(n):
    coord = [int(x) for x in input().split()]
    if coord[0] > xmax:
        xmax = coord[0]
    if coord[1] > ymax:
        ymax = coord[1]
    poligon.append(coord)

n = int(input())

for i in range(n):
    coord = [int(x) for x in input().split()]
    puncte.append(coord)

# determinarea pozitiei fiecarui punct

# alegerea punctului "departe"

xmax = xmax + 1
ymax = ymax + 1
punctDeparte = [xmax, ymax]

for punct in puncte:

    # vom testa daca punctul se
    # afla pe vreuna dintre laturi

    if estePeLatura(punct, poligon) == True:
        print("BOUNDARY")
        continue

    if numarIntersectii(punct, punctDeparte, poligon) % 2 == 0:
        print("OUTSIDE")
    else:
        print("INSIDE")