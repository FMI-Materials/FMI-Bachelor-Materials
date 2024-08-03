import heapq
s = 0
h = []
i=1
for x in input().split():
    heapq.heappush(h, (int(x),i))
    i+=1
while len(h) > 1:
    x,i1 = heapq.heappop(h)
    y,i2 = heapq.heappop(h)
    print(f"{i1} de lungime {x} + {i2} de lungime {y} => {i}")
    s = x + y + s
    heapq.heappush(h, (x+y,i))
    i+=1
x = heapq.heappop(h)

print(s)