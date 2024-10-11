# lambda functions = function written in 1 line using lambda keyword
#                    accepts any number of arguments, but only has one expression
#                    (think of it as a shortcut)
#                    (useful if needed for a short period of time, throw-away)

# IMPORTANT! THE FORMULA:
# lambda parameters:expression

# First method without lambda
def double(x):
    return x * 2

print(double(5))                            # it prints 10

# Second method with lambda
double = lambda x: x * 2
multiply = lambda x, y: x * y
add = lambda x, y, z: x + y + z
full_name = lambda first_name, last_name: first_name + " " + last_name
age_check = lambda age: True if age >= 18 else False

print(double(5))                            # it prints 10
print(multiply(5, 6))                       # it prints 30
print(add(5, 6, 7))                         # it prints 18
print(full_name("Hello", "World!"))         # it prints "Hello World!"
print(age_check(12))                        # it prints False
print(age_check(18))                        # it prints True