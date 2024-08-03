s = input("Sirul este:")
i = 0
m = len(s)
n = m//2
while i < m-i:
    print(s[i:m-i].center(10))
    i += 1
print("---")
i = 0
m = len(s)
n = m//2
while i < m-i:
    print(f"{s[i:m-i]:^10}") #afisat centrat pe 10 caractere
    i += 1
print("---")