d1 = {'A': 1, 'B': 2, 'C': 3}
d2 = {'B': 2, 'C': 3, 'D': 4}

K = d1.keys() | d2.keys()
d = {k: d1.get(k, 0) + d2.get(k, 0) for k in K}
print(d)
