def ex13(d1, d2):
    return {k: d1.get(k, 0) + d2.get(k, 0) for k in d1.keys() | d2.keys()}


d1 = {'a': 1, 'b': 2, 'c': 2}
d2 = {'b': -1, 'c': 2, 'd': 3}
print(ex13(d1, d2))
