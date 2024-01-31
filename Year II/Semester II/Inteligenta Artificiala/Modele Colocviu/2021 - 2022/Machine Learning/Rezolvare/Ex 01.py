def similaritate(s1, s2, p):
    count = 0
    s1 = [x for x in s1]
    s2 = [x for x in s2]
    for i in range(0, len(s1) - p + 1):
        for j in range(0, len(s2) - p + 1):
            if s1[i:i+p] == s2[j:j+p]:
                count = count + 1

    return count

# sim = similaritate("ananas copt", "banana verde", 4)