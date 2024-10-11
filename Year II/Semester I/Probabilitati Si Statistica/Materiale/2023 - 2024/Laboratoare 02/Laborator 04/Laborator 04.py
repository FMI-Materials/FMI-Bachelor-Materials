import numpy as np
import matplotlib.pyplot as plt

# probabilitati conditionate + formula lui Bayes
# + alte tipuri de randomness (inafara de uniforma)
# P(B|A) = P(intersect(B,A)) / P(A)
    # prob lui B conditionata de A

N = 1_000_000
n = 0
areBoala = 0
areTestPoz = 0
areTestNeg = 0
nuAreBoala = 0
counter = 0
douaTeste = 0
for i in range(N):
    prob = np.random.rand()
    if prob <= 0.02:
        areBoala += 1
        probBoala = np.random.rand()
        probBoala2 = np.random.rand()

        if probBoala <= 0.98:
            douaTeste += 1

        if probBoala2 <= 0.98:
            douaTeste += 1

        if probBoala <= 0.98:
            areTestPoz += 1
        else:
            areTestNeg += 1
    else:
        temp = np.random.rand()
        if temp <= 0.05:
            areBoala += 1
        nuAreBoala += 1

print("Are boala si testul depisteaza corect:",areTestPoz/areBoala,sep=" ")
print("Are boala si testul nu depisteaza corect:",areTestNeg/areBoala,sep=" ")
print("2 teste poz are boala:",douaTeste/areBoala,sep=" ")
