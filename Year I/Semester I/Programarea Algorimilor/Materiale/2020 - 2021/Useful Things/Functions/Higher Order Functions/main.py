# Higher Order Function = a function that either:
#                         1. accepts a function as an argument
#                               or
#                         2. returns a function
#                         (In python, functions are also treated as objects)

# 1.
def loud(text):
    return text.upper()

def quiet(text):
    return text.lower()

def hello(func):
    text = func("Hello")
    print(text)

hello(loud)     # it prints "HELLO"
hello(quiet)    # it prints "hello"

# 2.
def divisor(x):
    def dividend(y):
        return y / x
    return dividend

divide = divisor(2) # x = 2

print(divide(10))   # it prints 5.0
                    # y = 10