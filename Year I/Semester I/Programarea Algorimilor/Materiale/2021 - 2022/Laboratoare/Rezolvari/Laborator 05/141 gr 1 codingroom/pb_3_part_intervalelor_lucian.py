import heapq
h = []
sali = []
n = int(input())
l = input().split()
nrsali = 0
heapq.heappush(h, (int(l[1]), 0))
sali.append([])
sali[nrsali].append((int(l[0]), int(l[1])))
for i in range(n-1):
    l = input().split()
    x = int(l[0])
    y = int(l[1])
    timp, sala = heapq.heappop(h)
    if timp <= x:
        heapq.heappush(h, (y, sala))
        sali[sala].append((x, y))
    else:
        nrsali += 1
        sali.append([])
        sali[nrsali].append((x, y))
        heapq.heappush(h, (timp, sala))
        heapq.heappush(h, (y, nrsali))
print(nrsali+1)
for line in sali:
    for s in line:
        x, y = s
        print(f"[{x}, {y}]", end = " ")
    print()