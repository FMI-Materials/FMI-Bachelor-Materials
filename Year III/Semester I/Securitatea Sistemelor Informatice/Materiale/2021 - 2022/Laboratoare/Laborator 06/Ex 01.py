seed = int(input("Introduceti seed: "))

# C1
try:
   while seed!=0:
       print("Hello")
       print(seed)
       seed=seed^seed
except KeyboardInterrupt:
   pass

# C2
try:
    while seed!=0:
       print(seed)
       seed=int(seed+seed/2)
except KeyboardInterrupt:
    pass

# C3
print(seed>>2)
