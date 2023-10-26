def ex10(T):
    return sorted(T, key=lambda x: {x[1], -x[0]})


print(ex10([(1, 2), (2, 1), (2, 3), (1, 3)]))
