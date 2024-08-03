#solutie cu replace
sir=input()
X=sir[0]
sir=sir.replace(sir[0],"")
print(f"După ștergerea literei '{X}' șirul obținut este \"{sir}\" de lungime {len(sir)}")


#soultie cu cautare pozitie cu pozitie si stergere cu feliere

s=input("s=")
i=0
x=s[0]
while i<len(s):
   if s[i]==x:
      s=s[:i]+s[i+1:]
   else: i=i+1
print(s)

# merge si cu for descrescator, daca parcurgem sirul de la dreapta spre stanga
s = input("s=")
x=s[0]
for i in range(len(s)-1, -1, -1):
    if s[i] == x:
        s = s[:i] + s[i+1:]
print(s)