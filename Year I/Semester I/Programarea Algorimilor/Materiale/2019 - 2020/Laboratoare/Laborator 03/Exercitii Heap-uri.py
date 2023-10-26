import heapq as HQ
l=[3,2,1]
HQ.heapify(l)
print(l)
HQ.heappush(l,4)
print(l)
HQ.heappush(l,3)
print(l)
print(HQ.heappop(l))
print(l)