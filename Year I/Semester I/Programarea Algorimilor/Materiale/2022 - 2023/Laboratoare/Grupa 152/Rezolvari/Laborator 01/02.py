import math
x = int(input())
if not(x & (x - 1)):
    print(int(math.log2(x)))
else:
    print("Not a pow of 2")
