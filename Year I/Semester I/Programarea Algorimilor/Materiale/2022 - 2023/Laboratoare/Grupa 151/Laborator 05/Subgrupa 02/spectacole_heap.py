import heapq
# https://www.geeksforgeeks.org/heap-queue-or-heapq-in-python/

fin = open("spectacole.txt")
s = [line.strip() for line in fin.readlines()]
n = len(s)

L=[]

for i in range(n):
    L.append(s[i].split())
    L[i][0] = L[i][0].split("-")
L.sort()

R=[[L[0]]]

heap = [(L[0][0][1], 0)]
for i in range(1,n):
    ver = 0
    if heap[0][0] <= L[i][0][0]:
        popped = heapq.heappop(heap)
        nr_salii = popped[1]
        heapq.heappush(heap, (L[i][0][1], nr_salii))
        R[nr_salii].append(L[i])
    else:
        nr_salii = len(R)
        heapq.heappush(heap, (L[i][0][1], nr_salii))
        R.append([L[i]])
    # for j in range(len(R)):
    #     if L[i][0][0] >= R[j][len(R[j])-1][0][1]:
    #         R[j].append(L[i])
    #         ver = 1
    #         break
    # if ver == 0:
    #     R.append([L[i]])

print(len(R))
for i in R:
    for j in range(len(i)):
        print("({}-{} {})".format(i[j][0][0],i[j][0][1],i[j][1]), end=", " if j < len(i)-1 else "\n")