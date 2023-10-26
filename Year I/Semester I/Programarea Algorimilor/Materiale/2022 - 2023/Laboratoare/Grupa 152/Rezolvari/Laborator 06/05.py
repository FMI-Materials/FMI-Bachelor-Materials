def ex5(s):
    for ch in "!?.":
        s = s.replace(ch, "$")
    return f"Sirul este alcatuit din {len(s.split('$'))} propozitii. Cea mai lunga propozitie are {max([len(x) for x in s.split('$')])} caractere"


s = input()
print(ex5(s))
