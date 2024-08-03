def muta(x, i,j):
    if x>1:
        muta(x-1, i, 6-i-j) #turnul de manevra fiind 3 mutandu-se intre 2 ramane al treilea
        print(i, j, sep=" ")
        muta(x-1, 6-i-j, j) #in sens invers
    else:
        print(i, j, sep=" ")
muta(3,1,2)
