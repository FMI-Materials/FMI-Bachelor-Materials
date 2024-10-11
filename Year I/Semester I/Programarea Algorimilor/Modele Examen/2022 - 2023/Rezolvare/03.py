n = int(input("n: "))
t = [int(x) for x in input().split()]

pred = [-1] * (n+1)
maxx = [1] * (n+1)

for i in range(1,n):
    for j in range(i):
        if maxx[i] < maxx[j] + 1 and t[i] > t[j]:
            maxx[i] = maxx[j] + 1
            pred[i] = j

ind = maxx.index(max(maxx))
sol = []

while ind != -1:
    sol.append(t[ind])
    ind = pred[ind]
