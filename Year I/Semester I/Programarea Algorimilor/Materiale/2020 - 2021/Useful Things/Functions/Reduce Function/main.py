# reduce() = apply a function to an iterable and reduce it to a single cumulative value.
#            performs function on first two elements and repeats process until 1 value remains.

# reduce(function, iterable)

import functools

letters = ["H", "E", "L", "L", "O"]
word = functools.reduce(lambda x, y,: x + y, letters)
print(word)  # it prints "HELLO"

factorial = [5, 4, 3, 2, 1]
result = functools.reduce(lambda x, y,: x * y, factorial)
# Step 1: 5 * 4 = 20
# Step 2: 20 * 3 = 60
# Step 3: 60 * 2 = 120
# Step 4: 120 * 1 = 120
print(result)  # it prints 120
