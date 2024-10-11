import numpy as np
import matplotlib.pyplot as plt

def exercise1():

    # True means heads and False tail
    def correctThrow():
        r = np.random.rand()
        if r >= 0.5:
            return True
        return False

    # True means heads and False tail
    def incorrectThrow():
        r = np.random.rand()
        if r >= 0.7:
            return False
        return True

    n1 = 0
    n2 = 0
    N  = 10000
    Pi = 0
    probabilitiesVectorCorrect = []
    probabilitiesVectorIncorrect = []


    for i in range(N):
        if correctThrow():
            n1 += 1
        if incorrectThrow():
            n2 += 1
        probabilitiesVectorCorrect.append(n1/(i+1))
        probabilitiesVectorIncorrect.append(n2/(i+1))

    plt.figure(figsize=(10, 6))
    plt.plot(range(1, N + 1), probabilitiesVectorCorrect, label="Correct Throw Probability")
    plt.plot(range(1, N + 1), probabilitiesVectorIncorrect, label="Incorrect Throw Probability")
    plt.xlabel('Number of Throws')
    plt.ylabel('Probability')
    plt.legend()
    plt.title('Probability vs. Number of Throws')
    plt.grid(True)
    plt.show()
        
    print(f"Correct Throw Chance:{n1/N}\nIncorrect Throw Chance:{n2/N}")

def exercise2():
    def correctDice():
        return np.random.randint(1,7)

    def incorrectDice():
        r = np.random.rand()
        if r > 0.75:
            return 1
        elif r > 0.5:
            return 2
        elif r > 0.3:
            return 3
        elif r > 0.15:
            return 4
        elif r > 0.05:
            return 5
        else: 
            return 6
    
    N = 10000
    correct = 0
    incorrect = 0
    diceFace = int(input('Enter dice face: '))
    for i in range(N):
        if diceFace == correctDice():
            correct += 1
        if diceFace == incorrectDice():
            incorrect += 1
        
    print(f"Correct Throw Chance:{correct/N}\nIncorrect Throw Chance:{incorrect/N}")


def exercise3(numberOfThrows):
    def generate(N,k):
        x = np.random.randint(2,size=N)
        count = 0
        # get nr of sequences [1,1,1,1]
        target1 = [1 for i in range(k)]
        target2 = [0 for i in range(k)]
        for i in range(N - len(target1) + 1):
            if list(x[i:i+len(target1)]) == target1:
                return True
            if list(x[i:i+len(target2)]) == target2:
                return True
        
        return False

    nr = 0
    for i in range(numberOfThrows):
        if generate(100,10):
            nr += 1
    print(nr/numberOfThrows)



def exercise4():
    def throwRedDice():
        redDice = np.random.rand()
        if redDice > 0.83:
            return 4
        return 1

    def throwGreenDice():
        redDice = np.random.rand()
        if redDice > 0.83:
            return 3
        return 6
    
    def throwBlackDice():
        redDice = np.random.rand()
        if redDice > 0.5:
            return 2
        return 5
    
    def getWinner(N):
        rg = 0
        bg = 0
        rb = 0
        for i in range(N):
            r = throwRedDice()
            g = throwGreenDice()
            b = throwBlackDice()

            if r > g:
                rg += 1
            if r > b:
                rb += 1
            if b > g:
                bg += 1

        return (rg,rb,bg)
    
    N = 10000
    rg,rb,bg = getWinner(N)

    print(rg,rb,bg,sep=' ')
        
    print(f'Rosu bate Negru: {rb/N}')
    print(f'Rosu bate Verde: {rg/N}')
    print(f'Verde bate Rosu: {1 - rg/N}')
    print(f'Verde bate Negru: {1 - bg/N}')
    print(f'Negru bate Rosu: {1 - rb/N}')
    print(f'Negru bate Verde: {bg/N}')
    
exercise4()