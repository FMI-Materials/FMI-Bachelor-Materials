def hello():
    print("Hello")

hi = hello
hello()                     # it prints "Hello"
hi()                        # it prints "Hello"

say = print
say("Wow it works!")      # it prints "Wow it works!"