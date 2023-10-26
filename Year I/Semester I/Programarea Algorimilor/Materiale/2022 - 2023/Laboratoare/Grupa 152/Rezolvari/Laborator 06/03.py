def ex3():
    L = [line.strip().center(50) for line in open("Txt Files/poezie.txt", "r").readlines()]
    for line in L:
        print(line)


ex3()
