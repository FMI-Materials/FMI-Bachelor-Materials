n = int(input())
arr = [int(x) for x in input().split()]
arrXor = 0
for i in range(0, n):
    arrXor ^= arr[i]
print(arrXor)