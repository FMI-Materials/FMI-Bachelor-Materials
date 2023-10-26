L = [-31, 13, 45, -21, 100, -16, 78]


def negative_pozitive(L):
    negative = []
    pozitive = []
    for i in L:
        negative.append(i) if i < 0 else pozitive.append(i)
    return negative, pozitive


s = input()
cout = open(s, "w")
negative, pozitive = negative_pozitive(L)
cout.write(f"Negative: {negative}\nPozitive: {pozitive}")