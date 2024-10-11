import numpy as np
import matplotlib.pyplot as plt

def ex1_vector():
    N = 100_000
    A = np.random.randint(1,7,N)
    B = np.random.randint(1,7,N)
    C = A + B

    p1 = np.mean(A == 1)
    p2 = np.mean(B == 6)
    p3 = np.mean(C == 7)
    p4 = np.mean((A == 1) & (C == 7))
    p5 = np.mean((B == 6) & (C == 7))
    p6 = np.mean((A == 1) & (B == 6) & (C == 7))

    print("P ca A sa fie 1:", p1)
    print("P ca B sa fie 6:", p2)
    print("P ca suma sa fie 7:", p3)
    print("P independent A de C:", p4, "| A * C =", p1 * p3)
    print("P independent B de C:", p5, "| B * C =", p2 * p3)
    print("P independent A de B si de C:", p6, "| A * B =", p1 * p2 * p3)


def ex1():
    N = 100_000

    p1 = 0
    p2 = 0
    p3 = 0
    p4 = 0
    p5 = 0
    p6 = 0

    for i in range(N):
        firstDice = np.random.randint(1,7)
        secondDice = np.random.randint(1,7)

        sum = firstDice + secondDice

        if firstDice == 1:
            p1 += 1

        if secondDice == 6:
            p2 += 1
        
        if sum == 7:
            if firstDice == 1:
                p4 += 1

            if secondDice == 6:
                p5 += 1
            
            p3 += 1

        if firstDice == 1 and secondDice == 6 and sum == 7:
            p6 += 1

    print("P ca A sa fie 1:",p1/N)
    print("P ca B sa fie 6:",p2/N)
    print("P ca suma sa fie 7:",p3/N)
    print("P independent A de C:",p4/N,"| A * C =",(p1*p3)/(N*N))
    print("P independent B de C:",p5/N,"| B * C =",(p2*p3)/(N*N))
    print("P independent A de B si de C:",p6/N,"| A * B =",(p1*p2*p3)/(N*N*N))

# ca doua evenimente sa fie independente <=> P(A intersectat B) = P(A) * P(B) <=> p(A|B) = P(A) <=> P(B|A) = P

def ex2():
    N = 100_000

    N = 100_000
    A = np.random.randint(1,7,N)
    B = np.random.randint(1,7,N)
    C = A + B

    p1 = np.mean(A <= 2)
    p2 = np.mean(C == 7)
    p3 = np.mean(B % 2 == 0)
    p4 = np.mean((A <= 2) & (C == 7))
    p5 = np.mean((A <= 2) & (B % 2 == 0))
    p6 = np.mean((C == 7) & (B % 2 == 0))
    p7 = np.mean((A <= 2) & (C == 7) & (B % 2 == 0))

    print("P ca A sa fie <= 2:", p1)
    print("P ca suma sa fie 7:", p2)    
    print("P ca B sa fie par:", p3)
    print("P independent A de C:",p4,"| A * C =",p1*p2)
    print("P independent A de B:",p5,"| A * B =",(p1*p3))
    print("P independent B de C:",p6,"| B * C =",(p2*p3))
    print("P independent A de B si de C:",p7,"| A * B =",p1*p2*p3)


def ex3():
    N = 100_000

    # X apartine [a,b] inclus in (-1,1)
    # Y apartine [c,d] inclus in (-1,1)

    # P(X intersectat Y) = P(x apartine [a,b] si Y apartine [c,d])

    limit = np.random.uniform(0,1,N)

    interval = [-limit,limit]

    X = np.random.uniform(-1,1,N)
    Y = np.random.uniform(-1,1,N)
    p1 = np.mean(-np.round(X,2) == np.round(Y,2))

    p2 = np.mean(((X >= interval[0]) & (X <= interval[1])) & ((Y >= interval[0]) & (Y <= interval[1])))
    p3 = np.mean(((X >= interval[0]) & (X <= interval[1])))
    p4 = np.mean((Y >= interval[0]) & (Y <= interval[1]))

    print("P ca Y = -X:",p1)
    print("P ca X independent de Y",p2,"| X * Y:",p3*p4)

    p5 = np.mean(((X >= interval[0]) & (X <= interval[1])) & ((Y >= interval[0]) & (Y <= interval[1])) & (-np.round(X,2) == np.round(Y,2)))
    p6 = np.mean(((X >= interval[0]) & (X <= interval[1])))
    p7 = np.mean((Y >= interval[0]) & (Y <= interval[1]))

    print("P ca X independent de Y",p5,"| X * Y:",p6*p7)
    
# tema sa facem un joc similar cu ex5 pe care sa il rezolvam 
def game(M,sum):
    N = 10_000
    throws = np.random.randint(0,2,N)
    count = 0
    for throw in throws:
        throw = np.random.randint(0,2)
        count += 1

        if throw == 0:
            sum += 1  
        else:
            sum -= 1  

        if sum == 0:
            return (0,count)
        elif sum == M:
            return (1,count)

    return(0,count)

def ex5():
    N = 1000
    M = 100
    sum = 80
    p = 0

    for i in range(N):
        (result, count) = game(M,sum)

        if result == 1:
            p += 1

    print("Prob ca sa castige jocul:",p/N)

ex5()