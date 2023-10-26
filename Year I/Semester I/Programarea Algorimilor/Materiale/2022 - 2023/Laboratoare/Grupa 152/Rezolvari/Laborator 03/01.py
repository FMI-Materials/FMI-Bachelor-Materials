cin = open("Txt Files/test.in")
cout = open("Txt Files/test.out", "w")


def correct(s):
    i, j = s.find('*'), s.find('=')
    return ((int(s[:i]) * int(s[i + 1:j]) is int(s[j + 1:])))


count = 1
for lane in cin.readlines():
    endl = lane.find('\n')
    if correct(lane):
        count += 1
        lane = lane[:endl] + " Corect\n"
    else:
        i = lane.find('*')
        j = lane.find('=')
        lane = lane[:endl] + " Gresit " + str(int(lane[:i]) * int(lane[i + 1:j])) + '\n'
    cout.write(lane)

cout.write("Nota " + str(count))
cin.close()
cout.close()
