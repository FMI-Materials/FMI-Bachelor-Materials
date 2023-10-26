v = [1, 8, 5, 4]
S = 11
n = len(v)
nr = [S + 1 for i in range(S + 1)]  # infinit- S+1
moneda = [0 for i in range(S + 1)]
nr[0] = 0
moneda[0] = -1
for s in range(1, S + 1):
    nr[s] = S + 1  # infinit
    moneda[s] = -1
    for i in range(n):
        if (v[i] <= s) and nr[s - v[i]] + 1 < nr[s]:
            nr[s] = nr[s - v[i]] + 1
            moneda[s] = v[i]
print(f"Numarul minim de monede: {nr[S]}")
if nr[S] < S + 1:
    s = S
    while s > 0:
        print(moneda[s], end=" ")
        s = s - moneda[s]
else:
    print("Nu se poate plati suma S")
