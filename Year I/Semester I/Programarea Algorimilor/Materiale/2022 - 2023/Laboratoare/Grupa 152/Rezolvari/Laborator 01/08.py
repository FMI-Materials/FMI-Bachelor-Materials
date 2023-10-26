n = int(input())
arr = [float(x) for x in input().split()]
difMax = 0
ziMax = 0
crestere = False 
for i in range(0, n - 1):
    if arr[i + 1] - arr[i] > difMax:
        difMax = arr[i + 1] - arr[i]
        ziMax = i + 1
        crestere = True
if crestere:
    print("Cea mai mare crestere a fost de", int(difMax * 100) / 100, "si a avut loc intre zilele", ziMax, "si", ziMax + 1)
else:
    print("Nu a avut loc nici o crestere")
