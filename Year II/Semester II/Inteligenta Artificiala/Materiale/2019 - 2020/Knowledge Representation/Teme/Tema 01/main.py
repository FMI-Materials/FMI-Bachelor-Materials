import copy
import sys

# informatii despre un nod din arborele de parcurgere
class NodParcurgere:
    def __init__(self, info, parinte, cost=0, h=0):
        self.info = info
        self.parinte = parinte
        self.g = cost
        self.h = h
        self.f = self.g + self.h

    def obtineDrum(self):
        l = [self]
        nod = self
        while nod.parinte is not None:
            l.insert(0, nod.parinte)
            nod = nod.parinte
        return l

    def afisDrum(self, afisCost = False, afisLung = False):
        s = ""
        l = self.obtineDrum()
        for nod in l:
            s = s + str(nod) + "\n"
        if afisCost:
            s = s + "Cost: " + str(self.g) + "\n"
        if afisCost:
            s = s + "Lungime: " + str(len(l)) + "\n"
        return s

    def contineInDrum(self, infoNodNou):
        nodDrum = self
        while nodDrum is not None:
            if infoNodNou == nodDrum.info:
                return True
            nodDrum = nodDrum.parinte

        return False

    def __repr__(self):
        sir = ""
        sir += str(self.info)
        return sir


    def __str__(self):
        sir = ""
        maxInalt = max([len(stiva) for stiva in self.info])
        for inalt in range(maxInalt, 0, -1):
            for stiva in self.info:
                if len(stiva) < inalt:
                    sir += "  "
                else:
                    sir += stiva[inalt - 1] + " "
            sir += "\n"
        sir += "-" * (2 * len(self.info) - 1)
        return sir


class Graph:
    # functia pentru initializarea grafului
    def __init__(self, nume_fisier):
        f = open(nume_fisier, "r")
        self.nivel_scop = int(f.readline())
        continutFisier = f.read()  # citesc tot continutul fisierului
        self.start = self.obtineStive(continutFisier)

    # functie pentru memorarea stivelor de blocuri din fiecare nod
    def obtineStive(self, sir):
        stiveSiruri = sir.strip().split("\n")
        listaStive = [sirStiva.strip().split(", ")
        if sirStiva != "-" else [] for sirStiva in stiveSiruri]
        return listaStive

    # functie care testeaza daca vecinii unei stive sunt liberi
    def testeaza_vecini(self, nodCurentInfo, istiva):
        # cazul in care stiva se afla in marginea din stanga
        if istiva == 0:
            if len(nodCurentInfo[istiva + 1]) == 0:
                return True
        # cazul in care stiva se afla in marginea din dreapta
        elif istiva == len(nodCurentInfo) - 1:
            if len(nodCurentInfo[istiva - 1]) == 0:
                return True
        else:
            if len(nodCurentInfo[istiva + 1]) == 0 and len(nodCurentInfo[istiva - 1]) == 0:
                return True
        return False

    # testeaza daca configuratia este una finala
    def testeaza_scop(self, nodCurentInfo):
        # aflam inaltimea celei mai mari stive din nod si
        # verificam daca este de inaltimea ceruta
        inaltime_maxima = max([len(l) for l in nodCurentInfo])
        if inaltime_maxima == self.nivel_scop:
            for istiva, stiva in enumerate(nodCurentInfo):
                if len(stiva) == inaltime_maxima and self.testeaza_vecini(nodCurentInfo, istiva):
                    return True
        return False


    # va genera succesorii sub forma de noduri in arborele de parcurgere
    def genereazaSuccesori(self, nodCurent, tip_euristica="euristica banala"):
        listaSuccesori = []
        stive_c = nodCurent.info
        nr_stive = len(stive_c)
        for i in range(nr_stive):

            # ignoram stivele vide
            if len(stive_c[i]) == 0:
                continue

            copie_interm = copy.deepcopy(stive_c)
            bloc = copie_interm[i].pop()  # iau varful stivei
            for j in range(nr_stive):  # j = indicele stivei pe care pun blocul
                if i == j:  # nu punem blocul de unde l-am luat
                    continue
                # se creaza o noua lista de blocuri si adaugam blocul
                stive_n = copy.deepcopy(copie_interm)
                stive_n[j].append(bloc)

                # costul unei mutari este dat de
                # inaltimea de care a fost luat
                costMutareBloc = len(bloc)
                if not nodCurent.contineInDrum(stive_n):
                    nod_nou = NodParcurgere(stive_n, nodCurent, cost = nodCurent.g + costMutareBloc,
                        h = self.calculeaza_h(stive_n, tip_euristica))
                    listaSuccesori.append(nod_nou)
        return listaSuccesori

    # euristica banala
    def calculeaza_h(self, infoNod, tip_euristica="euristica banala"):

        # pentru euristica banala se va return 0
        # daca nodul este solutie, si 1 altfel
        if tip_euristica == "euristica banala":
            if self.testeaza_scop(infoNod):
                return 0
            return 1

        # pentru prima euristica admisibila se va returna
        # numarul de coloane din configuratie ce nu au vecinii vizi
        elif tip_euristica == "euristica admisibila 1":
            h = 0
            for iStiva, stiva in enumerate(infoNod):
                if self.testeaza_vecini(infoNod, iStiva) != True:
                    h += 1
            return h

        # pentru a doua euristica admisibila se va returna
        # numarul de coloane ce nu respecta inaltimea ceruta
        elif tip_euristica == "euristica admisibila 2":
            h = 0
            for stiva in infoNod:
                if len(stiva) != self.nivel_scop:
                    h += 1
            return h

        # pentru euristica neadmisibila se va returna suma
        # lungimilor coloanelor ce nu respecta inaltimea
        # ceruta, inmultite cu 1000
        elif tip_euristica == "euristica neadmisibila":
            h = 0
            for stiva in infoNod:
                if len(stiva) != self.nivel_scop:
                    h += len(stiva) * 1000
            return h

    def __repr__(self):
        sir = ""
        for (k, v) in self.__dict__.items():
            sir += "{} = {}\n".format(k, v)
        return sir


def a_star(gr, nrSolutiiCautate, nume_fisier, tip_euristica):
    c = [NodParcurgere(gr.start, None, 0, gr.calculeaza_h(gr.start))]
    f = open(nume_fisier, "w")

    while len(c) > 0:
        nodCurent = c.pop(0)
        if gr.testeaza_scop(nodCurent.info):
            f.write(nodCurent.afisDrum(afisCost = True, afisLung = True))
            f.write("\n=======================\n")
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                return

        lSuccesori = gr.genereazaSuccesori(nodCurent, tip_euristica = tip_euristica)
        for s in lSuccesori:
            i = 0
            gasit_loc = False
            for i in range(len(c)):
                if c[i].f >= s.f:
                    gasit_loc = True
                    break
            if gasit_loc:
                c.insert(i, s)
            else:
                c.append(s)
    f.close()


inputFolder = sys.argv[1]
outputFolder = sys.argv[2]
nrSolutiiCautate = int(sys.argv[3])

print("Alege tipul de euristica: ")
print("1. Euristica banala")
print("2. Euristica admisibila 1")
print("3. Euristica admisibila 2")
print("4. Euristica neadmisibila")

alegere = int(input())

if alegere == 1:
    gr = Graph(inputFolder + "\input1.txt")
    a_star(gr, nrSolutiiCautate, outputFolder + "\output1.txt", tip_euristica="euristica banala")
elif alegere == 2:
    gr = Graph(inputFolder + "\input2.txt")
    a_star(gr, nrSolutiiCautate, outputFolder + "\output2.txt", tip_euristica="euristica admisibila 1")
elif alegere == 3:
    gr = Graph(inputFolder + "\input3.txt")
    a_star(gr, nrSolutiiCautate, outputFolder + "\output3.txt", tip_euristica="euristica admisibila 2")
elif alegere == 4:
    gr = Graph(inputFolder + "\input4.txt")
    a_star(gr, nrSolutiiCautate, outputFolder + "\output4.txt", tip_euristica="euristica neadmisibila")
else:
    print("Optiunea nu exista")

