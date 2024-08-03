## Ex 1

 - A -> adevarat
 - B -> fals
 - C -> adevarat
 - D -> adevarat
 - E -> fals
 - F -> fals
 - G -> fals (```parola123``` -> decodata folosind MD5)

## Ex 2

```bash
gcc -D_PHOTON80_ -D_TABLE_ photon.c hotondriver.c -o photon80 sha2.c timer.c -O3
```
```bash
./photon80 -s
170 cycles per byte
```
```
./photon80 -f
S = 4, D = 5, Rate = 20, Ratep = 16, DigestSize = 80
```

Generare valori input:
```python
r = int(input("range = "))
word = "contor"
with open("input.txt", "w") as w:
   for i in range(r):
      w.write(word + str(i) + "\n")

```

Verificare colisiuni
```python
with open("output_test.txt", "r") as rt:
    test_lines = [x.replace("\n", "") for x in rt.readlines()][1:]
    test_lines = [x.split("::::: ")[1] for x in test_lines]

with open("output.txt", "r") as r:
    lines = [x.replace("\n", "") for x in r.readlines()][1:]
    lines = [x.split("::::: ")[1] for x in lines]

used = set()
has_collisions = False
idx = 0
for line in lines:
    # print("verified line "+str(idx))
    if line in used:
       has_collisions = True
       print(line + " has a collision")
    used.add(line)
    idx += 1
if has_collisions:
    print("Collisions found")
else:
    print("No collisions found")

```

Valorile din output.txt difera de cele din output_test.txt.

Nicio coliziune nu a fost gasita.

## Ex 3

 - 1 -> Functia data salveaza toate parolele criptate intr-o lista (sau set). Atunci cand dorim sa verificam o parola nu avem cum sa aflam carui utilizator ii corespunde. 
 - 2 -> Deoarece numele utilizatorilor sunt salvate hash-uite, pot exista coliziuni intre nume diferite. Ex: Daca ```Darius``` si ```Alex``` ofera acelasi hash, ```Alex``` nu isi va putea crea cont.
 - 3 -> Pentru o securitate mai buna, am avea nevoie de un salt atribuit fiecarei encriptari de parole.
 - 4 -> Salt-ul ar trebui sa fie generat random de fiecare data, nu salvat global intr-un fisier. Astfel, toate parolele create ar avea acelasi salt si parolele ar putea fii compromise printr-un simplu rainbow table attack.
 - 5 -> Aceasta functie stocheaza parolele folosind MD5, algoritm ce nu e destinat criptarii parolelor, datorita multiplelor vulnerabilitati gasite in algoritm.


