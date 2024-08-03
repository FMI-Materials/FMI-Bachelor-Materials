""" 10. Numele Pre-Nume
Scrieți un program care citește un șir de caractere și decide dacă
acesta este un nume corect al unei persoane.
Se consideră că un nume este corect dacă respectă următoarele proprietăți:
• Orice nume sau prenume conține doar litere.
• Orice nume sau prenume este format din cel puțin 3 litere.
• Orice nume sau prenume începe cu literă mare.
• Numele si prenumele sunt cel mult câte două, iar dacă sunt două atunci
sunt despărțite printr-o cratimă (‘-’)."""

sir1 = "Pop Andrei"
sir2 = "Pop-Mihai Ana"
sir3 = "Pop Vlad-Radu"
sir4 = "Pop-Mihai Oana-Dana"

sir5 = "Po-Mihai-iON Ana3-DanA"
persoane = [sir1, sir2, sir3, sir4, sir5]

for sir in persoane:
    print("\n" + sir)
    ok = True

    L = sir.split(" ")
    if len(L) != 2:
        print(L, "=> lungime != 2, nu e bine"); ok = False
    else:
        print(L, "=> lungime 2 OK")

        for i in [0,1]:
            x = "pre" * i + "nume"
            lista = L[i].split("-")
            if len(lista) not in {1,2}:
                print("-- ", x, "=", lista, " => prea multe", x); ok = False
            else:
                print("-- ", x, "=", lista, " => nr", x, "ok")

            for nume in lista:
                if len(nume) < 3:
                    print(nume, "are prea putine litere"); ok = False
                elif nume.isalpha() == False:
                    print(nume, "contine caractere care nu sunt litere"); ok = False
                elif nume[0].isupper() == False:
                    print(nume, "nu incepe cu litera mare"); ok = False
                elif nume[1:].islower() == False:
                    print(nume, "are si alte litere mari in afara de prima"); ok = False
                else:
                    print(nume, "este corect!")
    print("==> concluzie: (" + sir + ") " + "NU "*(1-int(ok)) + "este un nume corect.")