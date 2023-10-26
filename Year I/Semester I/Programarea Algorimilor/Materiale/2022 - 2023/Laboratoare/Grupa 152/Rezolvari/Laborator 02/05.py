prop = input()
sirCorect, sirGresit = map(str, input().split())
if sirGresit not in prop:
    print("Nu exista greseli in sir")
else:
    poz = prop.find(sirGresit)
    prop = prop.replace(sirGresit, sirCorect, 1)
    count = 1
    while sirGresit in prop[poz + 1:] and count <= 2:
        count += 1
        poz = prop.find(sirGresit)
        prop = prop.replace(sirGresit, sirCorect, 1)
    else:
        if count > 2:
            print("Textul contine prea multe greseli, doar 2 au fost corectate")
        else:
            print(prop)