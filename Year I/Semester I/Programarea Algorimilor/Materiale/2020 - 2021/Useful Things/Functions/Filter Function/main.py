# filter() = creates a collection of elements from an iterable for which a function returns true

# filter(function, iterable)

friends = [("Andrei", 19),
           ("Mihai", 21),
           ("Gigel", 16),
           ("Catalin", 17)]

age = lambda data: data[1] >= 18

drinking_buddies = list(filter(age, friends))

for i in drinking_buddies:
    print(i)