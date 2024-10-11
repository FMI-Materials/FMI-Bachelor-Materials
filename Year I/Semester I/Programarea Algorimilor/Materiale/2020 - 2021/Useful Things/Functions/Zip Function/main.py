# zip(*iterable) = aggreable elements from two or more iterables (list, tuples, sets, etc.)
#                  creates a zip object paired elements stored in tuples for each element

usernames = ["Robertto", "Mihai", "George"]
passwords = ("ceva@", "a1242541", "george2001")

users = zip(usernames, passwords)

print(type(users))  # it prints <class 'zip'>

# # cast to a list
# users = list(users)
#
# print(type(users))  # it prints <class 'list'>

# for i in users:
#     print(i)
#
# # it prints ('Robertto', 'ceva@')
# #           ('Mihai', 'a1242541')
# #           ('George', 'george2001')

# cast to a dictionary
users = dict(users)

for key, value in users.items():
    print(key + " : " + value)

# it prints Robertto : ceva@
#           Mihai : a1242541
#           George : george2001