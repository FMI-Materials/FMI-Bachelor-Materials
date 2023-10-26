# 1
# a
def factori_primi(n):
    factori = dict()
    for i in range(2, n+1):
        if n % i != 0:
            continue
        factori[i] = 0
        while n % i == 0:
            factori[i] += 1
            n = n // i
    return factori

# b
def calc_numar(factori):
    n = 1
    for f in factori:
        x, y = factori[f], f
        n *= y ** x
    return n

#c
def cmmdc(n, m):
    f_n = factori_primi(n)
    f_m = factori_primi(m)

    f_comm = dict()
    for f in f_n:
        if f in f_m:
            f_comm[f] = min(f_n[f], f_m[f])

    return calc_numar(f_comm)

print(factori_primi(600))
print(calc_numar(factori_primi(600)))
print(cmmdc(120, 18))

# 2
# Considerăm 𝑛 spectacole 𝑆1, 𝑆2, ... , 𝑆𝑛 pentru care cunoaștem intervalele lor de desfășurare [𝑠 , 𝑓 ), [𝑠 , 𝑓 ), ... , [𝑠 , 𝑓 ),
# toate dintr-o singură zi. Având la dispoziție o singură sală, în care putem să planificăm un singur spectacol la un moment dat,
# să se determine numărul maxim de spectacole care pot >i plani>icate fără suprapuneri.
# Un spectacol 𝑆 poate >i programat după spectacolul 𝑆 dacă 𝑠 ≥ 𝑓 .

def to_minutes(time):
    hour = int(time.split(':')[0])
    minute = int(time.split(':')[1])
    return hour * 60 + minute


def appoint_spectacles(spectacles):
    spectacles.sort(key=lambda s: s[1])
    used = list()
    for spectacle in spectacles:
        if len(used) == 0 or used[-1][1] < spectacle[0]:
            used.append(spectacle)
    for spectacle in used:
        print(spectacle[2], sep=' ')
    print()


with open("spectacole.txt", "r") as r:
    lines = r.read().split('\n')
    spectacles = [(to_minutes(x[:5]), to_minutes(x[6:11]), x[12:]) for x in lines]
    appoint_spectacles(spectacles)

# 3
def max_cost(n, prices):
    dp = prices.copy()
    for i in range(0, n-1):
        for j in range(i+1, n):
            dp[j] = max(dp[j], prices[i] + dp[j-(i+1)])
    return dp[n-1]


print(max_cost(5, [2, 5, 6, 8, 10]))

# 4
def afis_punctaj(M, R):
    print("(", ",".join([str(x) for x in M]), ")", end=", ", sep="")
    p = sum(M)
    NM = M.copy()
    if p == R:
        return
    for i in range(0, len(NM)):
        NM[i] -= 1
        afis_punctaj(NM, R)
        NM[i] += 1

#afis_punctaj([5, 4, 7], 14)

