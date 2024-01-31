def rucsac(W, weights, val):
    n = len(val)
    dp = [[0 for _ in range(W + 1)] for _ in range(n + 1)]
    for i in range(n + 1):
        for j in range(W + 1):
            if i == 0 or j == 0:
                dp[i][j] = 0
            elif weights[i - 1] <= j:
                dp[i][j] = max(val[i - 1] + dp[i - 1][j - weights[i - 1]], dp[i - 1][j])
            else:
                dp[i][j] = dp[i - 1][j]
    return dp[n][W]


w = [10, 20, 30]
val = [60, 100, 120]
W = 50
print(rucsac(W, w, val))
