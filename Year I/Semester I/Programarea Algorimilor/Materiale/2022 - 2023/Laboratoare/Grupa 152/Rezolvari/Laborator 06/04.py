def ex4(s1, s2):
    max = 0
    for i in range(len(s2)):
        for j in range(i, len(s2)):
            if s2[i:j + 1] in s1:
                if j - i + 1 > max:
                    max = j - i + 1
    return max


s1, s2 = input(), input()
print(ex4(s1, s2))
