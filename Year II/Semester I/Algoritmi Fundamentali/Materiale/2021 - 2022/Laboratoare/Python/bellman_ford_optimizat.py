'''
    Arcele pot avea si cost negativ
    graful nu contine circuite de cost negativ
    DETECTEAZA CIRCUITELE neafisand solutia optima
    Toate varfurile trebuie sa fie accesibile din nodul de start
    O(nm)

    Varianta optimizata
        -> oprire cand nu s-au mai actualizat etichete
        -> pastrare coada cu varfurile a caror eticheta s-a modificat
'''
n=6
graf={
    1:[(5,1),(6,2)],
    2:[(4,-100)],
    3:[(2,8),(5,4)],
    4:[(3,1)],
    5:[],
    6:[]
}
from collections import deque
#initializari
start=1
infinit=float("Inf")
dist = [float("Inf")] * (n+1)
dist[start] = 0
tata=[0]*(n+1)

def Bell():
    global dist, tata, infinit, start
    in_q = [0] * (n + 1)
    q = deque([])
    nr=[0]*(n+1)
    q.append(start)
    in_q[start]=1
    while len(q)>0:
        u = q.popleft()
        in_q[u]=0
        for (v,w) in graf[u]:
            if dist[u]<infinit and dist[u]+w<dist[v]:
                dist[v] = dist[u]+w
                tata[v] = u
                if in_q[v]==0:
                    q.append(v)
                    in_q[v]=1
                    nr[v]=nr[u]+1
                    if nr[v]>n-1:
                        return v #varful cu circuitul
    return None

print("Vectorul de distante este: ",dist[1:])
print("Vectorul de tati este: ", tata[1:])

#Facem n pași înapoi din v folosind vectorul tata (către s)
#fie x vârful în care am ajuns
#Afișăm circuitul care conține pe x folosind tata (din x până ajungem iar în x)
x=Bell()
print("Circuitul este: ")
def LANT(s):
    while s!=tata[s]:
        print(s, end=" ")
        s=tata[s]
    else:
        print(s, end=" ")
if x!=None:
    LANT(x)
else:
    print("Nu are circuit")