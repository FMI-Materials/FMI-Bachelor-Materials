# list comprehension = a way to create a new list with less syntax
#                      can mimic certain lambda functions, easier to read
#                      list = [expression for item in iterable]

squares = []                # create an empty list
for i in range(1, 11):      # create a for loop
    squares.append(i * i)   # define what each loop iteration should do
print(squares)              # it prints [1, 4, 9, 16, 25, 36, 49, 64, 81, 100]

squares2 = [i * i for i in range(1, 11)]
print(squares2)             # it prints [1, 4, 9, 16, 25, 36, 49, 64, 81, 100]
                            # so its the same :)



# list comprehension = a way to create a new list with less syntax
#                      can mimic certain lambda functions, easier to read
#                      list = [expression for item in iterable if conditional]

students = [100, 90, 80, 70, 60, 50, 40, 30, 0]

passed_students = list(filter(lambda x: x >= 60, students))
print(passed_students)       # it prints [100, 90, 80, 70, 60]

passed_students2 = [i for i in students if i >= 60]
print(passed_students2)      # it prints [100, 90, 80, 70, 60]
                             # so its the same :)



# list comprehension = a way to create a new list with less syntax
#                      can mimic certain lambda functions, easier to read
#                      list = [expression (if/else) for item in iterable]

passed_students3 = [i if i>= 60 else "FAILED" for i in students]
print(passed_students3)     # it prints [100, 90, 80, 70, 60, 'FAILED', 'FAILED', 'FAILED', 'FAILED']