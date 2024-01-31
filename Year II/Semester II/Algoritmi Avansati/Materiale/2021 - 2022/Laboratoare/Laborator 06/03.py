# calcularea determinantului unei matrice de 4x4

def determinant(punct, triunghi):

    m = [[triunghi[0][0], triunghi[0][1], triunghi[0][0]**2 + triunghi[0][1]**2, 1],
        [triunghi[1][0], triunghi[1][1], triunghi[1][0]**2 + triunghi[1][1]**2, 1],
        [triunghi[2][0], triunghi[2][1], triunghi[2][0]**2 + triunghi[2][1]**2, 1],
        [punct[0], punct[1], punct[0]**2 + punct[1]**2, 1]]
    
    a1 = m[0][0]* (m[1][1]* (m[2][2]* m[3][3] - m[3][2]* m[2][3]) - m[1][2]* (m[2][1]* m[3][3] - m[3][1]*m[2][3])+  m[1][3]* (m[2][1]* m[3][2] - m[3][1]*m[2][2]))  
    a2 = m[0][1]* (m[1][0]* (m[2][2]* m[3][3] - m[3][2]* m[2][3]) - m[1][2]* (m[2][0]* m[3][3] - m[3][0]*m[2][3])+ m[1][3]* (m[2][0]* m[3][2] - m[3][0]*m[2][2]))  
    a3 = m[0][2]* (m[1][0]* (m[2][1]* m[3][3] - m[3][1]* m[2][3]) - m[1][1]* (m[2][0]* m[3][3] - m[3][0]*m[2][3])+  m[1][3]* (m[2][0]* m[3][1] - m[3][0]*m[2][1]))  
    a4 = m[0][3]* (m[1][0]* (m[2][1]* m[3][2] - m[3][1]* m[2][2]) - m[1][1]* (m[2][0]* m[3][2] - m[3][0]*m[2][2])+  m[1][2]* (m[2][0]* m[3][1] - m[3][0]*m[2][1]))
    
    return a1 - a2 + a3 - a4

# main entry

triunghi = []
puncte = []

for i in range(3):
    coord = [int(x) for x in input().split()]
    triunghi.append(coord)

n = int(input())

for i in range(n):
    coord = [int(x) for x in input().split()]
    puncte.append(coord)

for punct in puncte:

    if determinant(punct, triunghi) == 0:
        print("BOUNDARY")
    elif determinant(punct, triunghi) < 0:
        print("OUTSIDE")
    else:
        print("INSIDE")