cout = open("Txt Files/Txt_07.txt", "w")


def search(cuv, *args):
    for i in args:
        cin = open(i)
        cout.write(i + " : ")
        count = found = 0
        for line in cin.readlines():
            count += 1
            if cuv in line:
                cout.write(str(count) + " ")
                found = 1
        if not found:
            cout.write("Nu exista")
        cout.write('\n')
        cin.close()


search("-16", "Txt Files/negative_pozitive.txt", "Txt Files/Triplete_pitagorice.txt")
cout.close()
