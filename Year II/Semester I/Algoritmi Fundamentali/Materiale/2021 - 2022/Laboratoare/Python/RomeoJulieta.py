f = open("rj.in")

line=f.readline()
v=line.split()
n=int(v[0])
m=int(v[1])
def zero(n,m): #matrice de n*m cu zerouri
    matrice=[]
    for i in range(n):
        ma=[]
        for j in range(m):
            ma.append(0)
        matrice.append(ma)
    return matrice
romeo=zero(n,m)
julieta=zero(n,m)


for i in range(n):
    line=f.readline()
    #-1 pe unde e x
    # 99999999 daca e locuinta lui romeo in matricea julietei si invers
    for j in range (m):
        if line[j]=='R':
            romeo[i][j]=0
            rlin=i
            rcol=j
            julieta[i][j]=99999999
        elif line[j]=='J':
            romeo[i][j] = 99999999
            jlin = i
            jcol = j
            julieta[i][j] = 0
        elif line[j]=='X':
            romeo[i][j]=julieta[i][j]=-1
        else:
            romeo[i][j] = julieta[i][j] = 99999999
f.close()

def in_matrice(x,y):
    if x < 0 or y < 0 or x >=n or j >=m:
        return False
    return True

from collections import deque
coada = deque([])
b = []
dx = [-1, -1, -1, 0, 1, 1, 1, 0]
dy = [-1, 0, 1, 1, 1, 0, -1, -1]

def drum(mat):
    while len(coada)>0:
        pair = coada.popleft()
        i = pair[0]
        j = pair[1]

        for directie in range(0,8):
            i_urm = i + dx[directie]
            j_urm = j + dy[directie]

            if in_matrice(i_urm, j_urm) == True and mat[i_urm][j_urm] > mat[i][j] + 1:
                mat[i_urm][j_urm]  = mat[i][j] + 1
                coada.append((i_urm, j_urm))

coada.append((rlin, rcol))
drum(romeo)
coada.append((jlin, jcol))
drum(julieta)

rezl = 1
rezc = 1
mini = 999999999
for i in range(n):
    for j in range(m):
        if romeo[i][j] == julieta[i][j] and romeo[i][j] != -1 and romeo[i][j] < mini:
            mini = romeo[i][j]
            rezl = i + 1
            rezc = j + 1
print(f"{mini + 1} {rezl} {rezc}")
