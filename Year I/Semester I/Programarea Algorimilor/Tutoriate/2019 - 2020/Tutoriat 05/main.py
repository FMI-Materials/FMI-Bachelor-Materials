# 1
def checkGrid(grid):
    # rows
    for x in range(0, 3):
        row = set([grid[x][0], grid[x][1], grid[x][2]])
        if len(row) == 1 and grid[x][0] != 0:
            return grid[x][0]

    # columns
    for x in range(0, 3):
        column = set([grid[0][x], grid[1][x], grid[2][x]])
        if len(column) == 1 and grid[0][x] != 0:
            return grid[0][x]

    # diagonals
    diag1 = set([grid[0][0], grid[1][1], grid[2][2]])
    diag2 = set([grid[0][2], grid[1][1], grid[2][0]])
    if len(diag1) == 1 or len(diag2) == 1 and grid[1][1] != 0:
        return grid[1][1]

    return 0


winner_is_2 = [[2, 2, 0],
               [2, 1, 0],
               [2, 1, 1]]
winner_is_1 = [[1, 2, 0],
               [2, 1, 0],
               [2, 1, 1]]

winner_is_also_1 = [[0, 1, 0],
                    [2, 1, 0],
                    [2, 1, 1]]

no_winner = [[1, 2, 0],
             [2, 1, 0],
             [2, 1, 2]]

also_no_winner = [[1, 2, 0],
                  [2, 1, 0],
                  [2, 1, 0]]

print(checkGrid(also_no_winner))

# 3

import random


def compare_numbers(number, user_guess):
    cowbull = [0, 0]  # cows, then bulls
    for i in range(len(number)):
        if number[i] == user_guess[i]:
            cowbull[1] += 1
        else:
            cowbull[0] += 1
    return cowbull


playing = True  # gotta play the game
number = str(random.randint(0, 9999))  # random 4 digit number
guesses = 0

print("Let's play a game of Cowbull!")  # explanation
print("I will generate a number, and you have to guess the numbers one digit at a time.")
print("For every number in the wrong place, you get a cow. For every one in the right place, you get a bull.")
print("The game ends when you get 4 bulls!")
print("Type exit at any prompt to exit.")

while playing:
    user_guess = input("Give me your best guess!")
    if user_guess == "exit":
        break
    cowbullcount = compare_numbers(number, user_guess)
    guesses += 1

    print("You have " + str(cowbullcount[0]) + " cows, and " + str(cowbullcount[1]) + " bulls.")

    if cowbullcount[1] == 4:
        playing = False
        print("You win the game after " + str(guesses) + "! The number was " + str(number))
        break  # redundant exit
    else:
        print("Your guess isn't quite right, try again.")
# 5

def gcd(my_list):
    result = my_list[0]
    for x in my_list[1:]:
        if result < x:
            temp = result
            result = x
            x = temp
        while x != 0:
            temp = x
            x = result % x
            result = temp
    return result


def insertionSort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key


arr = [12, 11, 13, 22, 5, 6]
insertionSort(arr)
print(arr)

# 11: Complexitate: O(n*log(n))
intervals = [[570, 670], [500, 590], [600, 680], [690, 840], [930, 1005], [730, 790], [700, 795], [900, 960]]

def calculateLengths(intervals):
    intervals.sort()
    total = 0
    current_start = intervals[0][0]
    current_end = intervals[0][1]
    for interval in intervals:
        if interval[0] < current_end:
            current_end = max(current_end, interval[1])
        else:
            total += current_end - current_start
            current_start = interval[0]
            current_end = interval[1]
    total += current_end - current_start
    return total


print(calculateLengths(intervals))

# 12: Complexitate: O(log(b))
def powers(a, b):
    p = 1
    while p < a:
        p *= 2
    while p <= b:
        print(p, end=" ")
        p *= 2

powers(4, 100)

# 13: Complexitate: O(n)
def partialSort(v):
    i = 0
    j = len(v) - 1
    while i < j:
        while i < len(v) and v[i] < 0:
            i = i + 1
        while j >= 0 and v[j] >= 0:
            j = j - 1
        if i < j:
            v[i], v[j] = v[j], v[i]
    return v

print(partialSort([102, -11, -2, 44, 33, -100, 33]))
