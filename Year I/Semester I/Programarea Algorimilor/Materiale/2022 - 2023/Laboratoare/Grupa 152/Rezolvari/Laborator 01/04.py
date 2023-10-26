x, n = map(int, input().split())
leftMask = 1 << (n + 1)
rightMask = (1 << n) - 1
leftSide = (x & -leftMask) >> 1
rightSide = x & rightMask
print(rightSide | leftSide)