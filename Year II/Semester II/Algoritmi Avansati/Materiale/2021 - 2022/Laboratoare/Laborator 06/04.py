# calcularea determinantului unei matrice de 4x4

def determinant(a, b, c, d):

    m = [[a[0], a[1], a[0]**2 + a[1]**2, 1],
        [b[0], b[1], b[0]**2 + b[1]**2, 1],
        [c[0], c[1], c[0]**2 + c[1]**2, 1],
        [d[0], d[1], d[0]**2 + d[1]**2, 1]]
    
    a1 = m[0][0]* (m[1][1]* (m[2][2]* m[3][3] - m[3][2]* m[2][3]) - m[1][2]* (m[2][1]* m[3][3] - m[3][1]*m[2][3])+  m[1][3]* (m[2][1]* m[3][2] - m[3][1]*m[2][2]))  
    a2 = m[0][1]* (m[1][0]* (m[2][2]* m[3][3] - m[3][2]* m[2][3]) - m[1][2]* (m[2][0]* m[3][3] - m[3][0]*m[2][3])+ m[1][3]* (m[2][0]* m[3][2] - m[3][0]*m[2][2]))  
    a3 = m[0][2]* (m[1][0]* (m[2][1]* m[3][3] - m[3][1]* m[2][3]) - m[1][1]* (m[2][0]* m[3][3] - m[3][0]*m[2][3])+  m[1][3]* (m[2][0]* m[3][1] - m[3][0]*m[2][1]))  
    a4 = m[0][3]* (m[1][0]* (m[2][1]* m[3][2] - m[3][1]* m[2][2]) - m[1][1]* (m[2][0]* m[3][2] - m[3][0]*m[2][2])+  m[1][2]* (m[2][0]* m[3][1] - m[3][0]*m[2][1]))
    
    return a1 - a2 + a3 - a4

# main entry

patrulater = []

for i in range(4):
    coord = [int(x) for x in input().split()]
    patrulater.append(coord)

a = patrulater[0]
b = patrulater[1]
c = patrulater[2]
d = patrulater[3]

if determinant(a, b, c, d) > 0:
    print("AC: ILLEGAL")
else:
    print("AC: LEGAL")

if determinant(b, c, d, a) > 0:
    print("BD: ILLEGAL")
else:
    print("BD: LEGAL")