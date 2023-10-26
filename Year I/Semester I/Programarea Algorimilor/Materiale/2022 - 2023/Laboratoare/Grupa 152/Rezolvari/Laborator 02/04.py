s = input()
n = len(s)
for i in range(1, (n + 1) // 2):
    print(s[i:n - i].center(n))