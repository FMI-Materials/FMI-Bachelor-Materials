d1={
    "ana": 1,
    "are": 2,
    "mere": 3
}
d2={
    "ana":2,
    "multe":1
}
for x in d2:
    if x in d1:
        d1[x]=d1[x]+d2[x]
    else:
        d1[x]=d2[x]
print(d1)