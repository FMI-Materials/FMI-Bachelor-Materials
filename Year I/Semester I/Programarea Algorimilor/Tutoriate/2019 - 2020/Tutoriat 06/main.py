# 1
def to_minutes(time):
    hour = int(time.split(':')[0])
    minute = int(time.split(':')[1])
    return hour * 60 + minute


def appoint_spectacles(spectacles):
    spectacles.sort(key=lambda s: s[1])
    used = list()
    for spectacle in spectacles:
        if len(used) == 0 or used[-1][1] < spectacle[0]:
            used.append(spectacle)
    for spectacle in used:
        print(spectacle[2], sep=' ')
    print()


with open("spectacole.txt", "r") as r:
    lines = r.read().split('\n')
    spectacles = [(to_minutes(x[:5]), to_minutes(x[6:11]), x[12:]) for x in lines]
    appoint_spectacles(spectacles)


# 2
def appoint_spectacles2(spectacles):
    spectacles.sort(key=lambda s: s[0])
    halls = list()
    for spectacle in spectacles:
        if len(halls) == 0:
            halls.append(spectacle[1])
        else:
            found = False
            for i in range(len(halls)):
                if halls[i] < spectacle[0]:
                    halls[i] = spectacle[1]
                    found = True
                    break
            if not found:
                halls.append(spectacle[1])
    print(len(halls))
    print()


with open("spectacole.txt", "r") as r:
    lines = r.read().split('\n')
    spectacles = [(to_minutes(x[:5]), to_minutes(x[6:11]), x[12:]) for x in lines]
    appoint_spectacles2(spectacles)


# 4
def minimize_delay(activities):
    activities.sort(key=lambda a: a[1])
    t = 0
    delay = 0
    for activity in activities:
        print(t, t + activity[0], sep=' ', end=' ')
        t += activity[0]
        print(max(0, t - activity[1]))
        delay += max(0, t - activity[1])
    print(delay)
    print()


with open("activitati.txt", "r") as r:
    n = r.readline()
    lines = r.read().split('\n')
    activities = [(int(x.split()[0]), int(x.split()[1])) for x in lines]
    minimize_delay(activities)


# 5
def pay_sum(money, amount):
    money.sort(reverse=True)
    for note in money:
        times = 0
        while amount > 0 and note <= amount:
            times += 1
            amount -= note
        if times == 0:
            continue
        print(note, times, sep=' x ')
    print()


with open("bani.txt", "r") as r:
    money = [int(x) for x in r.readline().split()]
    amount = int(r.readline())
    pay_sum(money, amount)


# 6
def create_tower(cubes):
    cubes.sort(key=lambda c: c[0], reverse=True)
    tower = [cubes[0]]
    for cube in cubes:
        if cube[1] != tower[-1][1]:
            tower.append(cube)
    tower.reverse()
    for cube in tower:
        print(cube[0], cube[1], sep=' ')
    print()


with open("cuburi.txt", "r") as r:
    r.readline()
    cubes = [(int(x.split()[0]), x.split()[1]) for x in r.read().split('\n')]
    create_tower(cubes)
