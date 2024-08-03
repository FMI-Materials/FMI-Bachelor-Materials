r = int(input("range = "))
word = "contor"
with open("input.txt", "w") as w:
   for i in range(r):
      w.write(word + str(i) + "\n")
