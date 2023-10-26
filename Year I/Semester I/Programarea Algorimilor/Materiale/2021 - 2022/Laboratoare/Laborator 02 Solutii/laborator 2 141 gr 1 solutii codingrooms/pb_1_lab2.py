#cu replace
s = input("Cuvantul citit:")
x = s[0]
s = s.replace(x, '') #toate aparitiile
print(f"După ștergerea literei '{x}' șirul obținut este \"{s}\" de  lungime  {len(s)}")
print("După ștergerea literei '{}' șirul obținut este \"{}\" de  lungime  {}".format(x,s,len(s)))
#cu index

sir=input("")
x=sir[0]
i=0
while i<len(sir):
    if sir[i]==x:
        sir=sir[:i]+sir[i+1:]
    else:
        i=i+1
print(f"După ștergerea literei {x} șirul obținut este {sir} de lungime {len(sir)}" )