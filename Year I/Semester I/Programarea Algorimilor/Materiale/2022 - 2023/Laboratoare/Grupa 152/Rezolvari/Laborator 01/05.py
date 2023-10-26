x = int(input())
count = 0
while x:
    count += 1
    x &= x - 1
print(count)