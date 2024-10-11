# walrus operator :=
# Python 3.8

# assignment expression aka walrus operator
# assigns values to variable as part of a larger expression

happy = True

print(happy)                    # it prints True

print(happy == True)            # ERROR

print(happy_walrus := True)     # it prints True

# First method without walrus operator
foods = list()
while True:
    food = input("What food do you like?: ")
    if food == "quit":
        break
    foods.append(food)

# Second method with walrus operator
foods2 = list()
while food := input("What food do you like?: ") != "quit":
    foods2.append(food)