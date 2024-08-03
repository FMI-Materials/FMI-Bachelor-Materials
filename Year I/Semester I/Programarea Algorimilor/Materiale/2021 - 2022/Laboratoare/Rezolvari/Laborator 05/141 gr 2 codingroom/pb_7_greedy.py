# lista lungimi intervale
l=[(20,1),(30,2),(20,3),(35,4)]
# functia de interclasare
def merge(lungime1,lungime2):
    return lungime1+lungime2
import heapq
h=[]
# introducerea valorilor in heap - tupluri (cheie=lungime, index)
for lungime in l:
    heapq.heappush(h,lungime) 

# la fiecare pas, se scot cele mai mici intervale si se adauga intervalul nou
last_pos=len(l)
while len(h)>1:
    last_pos+=1
    lungime1,poz1=heapq.heappop(h)
    lungime2,poz2=heapq.heappop(h)
    newLungime=(merge(lungime1,lungime2),last_pos)
    heapq.heappush(h,newLungime)
    print(f"L{last_pos} = L{poz1} + L{poz2} = {newLungime[0]}")

print(h)
    
