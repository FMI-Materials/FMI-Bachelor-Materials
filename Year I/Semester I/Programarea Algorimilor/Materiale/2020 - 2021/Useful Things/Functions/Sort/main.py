# sort() method = used with lists
# sort() function = used with iterables

students = ["Andrei", "Mihai", "George", "Vlad"]

students.sort()

for i in students:
    print(i)

print("Done for sort() method!\n")

students.sort(reverse=True)
for i in students:
    print(i)

print("Done for reversed sort() method!\n")

students2 = ("Andrei", "Mihai", "George", "Vlad")

sorted_students = sorted(students2, reverse=True)

for i in sorted_students:
    print(i)

print("Done for reversed sort() function!\n")


students3 = [("Andrei", "F", 60),
             ("Mihai", "A", 33),
             ("George", "D", 36),
             ("Vlad", "C", 78)]

grade = lambda grades: grades[1]
age = lambda ages: ages[2]
students3.sort(key=grade, reverse=True)
students3.sort(key=age, reverse=True)
for i in students3:
    print(i)

print("Done for sort() method using a key!\n")

students4 = (("Andrei", "F", 60),
             ("Mihai", "A", 33),
             ("George", "D", 36),
             ("Vlad", "C", 78))

sorted_students2 = sorted(students4, key=age)

for i in sorted_students2:
    print(i)

print("Done for sort() function using a key!\n")