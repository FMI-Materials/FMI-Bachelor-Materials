""" 13. Se citește un număr natural N.
a)	Să se genereze și afișeze o matrice de dimensiune NxN,
cu elementele de la 1 la N*N - în ordine crescătoare,
de la stânga la dreapta și de sus în jos.
b)	Pentru a parcurge elementele matricei în spirală, pornind
din colțul din stânga-sus (spre dreapta, în jos, spre stânga, în sus, …),
să se obțină întâi o listă având elemente de tip tuplu (linie, coloană)
care să reprezinte pozițiile ce trebuie parcurse în această spirală.
c)	Folosind lista de tupluri de mai sus, să se afișeze elementele
din matrice aflate la acele poziții."""

""" a) """
N = int(input("N = "))
mat = [[lin*N+col+1 for col in range(N)] for lin in range(N)]

print("\nMatricea este: ")
print("\t", end="")
for col in range(N):
    print(col, end="\t")
for lin in range(N):
    print("\n" + str(lin), end="\t")
    for col in range(N):
        print(mat[lin][col], end="\t") # tab

""" b) """
# lista_poz = [(0, 0), (0, 1), ..., (0, N-2),
#              (0, N-1), (1, N-1), ..., (N-2, N-1),
#              (N-1, N-1), (N-1, N-2), ..., (N-1, 1),
#              (N-1, 0), (N-2, 0), ..., (1, 0),
#              (1, 1), (1, 2), ...]

lista_poz = []
for k in range(0, (N+1)//2): # k = nr_contur
    lista_poz.extend([(k, j) for j in range(k, (N-1)-k)]) # la dreapta
    lista_poz.extend([(i, (N-1)-k) for i in range(k, (N-1)-k)]) # in jos
    lista_poz.extend([((N-1)-k, jj) for jj in range((N-1)-k, k, -1)]) # la stanga
    lista_poz.extend([(ii, k) for ii in range((N-1)-k, k, -1)]) # in sus
if N%2 != 0: # elementul din centru, daca N impar
    lista_poz.append((N//2, N//2))
print("\n\nLista pozitiilor din spirala este:\n", lista_poz)

""" c) """
spirala = [mat[i][j] for (i,j) in lista_poz]
print("\nElementele din spirala sunt:\n", spirala)