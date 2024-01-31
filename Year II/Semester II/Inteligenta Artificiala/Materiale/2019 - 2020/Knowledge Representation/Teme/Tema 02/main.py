import time

import pygame, sys, copy, math


ADANCIME_MAX = 2


def elem_identice(lista):
	if all(elem == lista[0] for elem in lista[1:]):
		return lista[0] if lista[0] != Joc.GOL else False
	return False


class Joc:

	NR_COLOANE = 8
	JMIN = None
	JMAX = None
	GOL = "#"

	@classmethod
	def initializeaza(cls, display, NR_COLOANE= 8, dim_celula = 100):
		cls.display = display
		cls.dim_celula = dim_celula
		cls.rosu_img = pygame.image.load("red.png")
		cls.rosu_img = pygame.transform.scale(
			cls.rosu_img,
			(
				dim_celula,
				math.floor(dim_celula * cls.rosu_img.get_height() / cls.rosu_img.get_width()),
			),
		)
		cls.alb_img = pygame.image.load("white.png")
		cls.alb_img = pygame.transform.scale(
			cls.alb_img,
			(
				dim_celula,
				math.floor(
					dim_celula * cls.alb_img.get_height() / cls.alb_img.get_width()
				),
			),
		)
		cls.celuleGrid = []  # este lista cu patratelele din grid
		for linie in range(NR_COLOANE):
			cls.celuleGrid.append([])
			for coloana in range(NR_COLOANE):
				patr = pygame.Rect(
					coloana * (dim_celula + 1),
					linie * (dim_celula + 1),
					dim_celula,
					dim_celula,
				)
				cls.celuleGrid[linie].append(patr)

	def deseneaza_grid(self, marcaj=None):  # tabla de exemplu este ["#","x","#","0",......]
		for linie in range(Joc.NR_COLOANE):
			for coloana in range(Joc.NR_COLOANE):
				if marcaj == (linie, coloana):
					# daca am o patratica selectata, o desenez cu verde
					culoare = (0, 255, 0)
				elif (linie + coloana) % 2 == 1:
					culoare = (0,0,0)
				else:
					culoare = (255, 255, 255)
					

				pygame.draw.rect(self.__class__.display, culoare, self.__class__.celuleGrid[linie][coloana])

				if self.matr[linie][coloana] == "rosu":
					self.__class__.display.blit(self.__class__.rosu_img,(coloana * (self.__class__.dim_celula + 1),
							linie * (self.__class__.dim_celula + 1) +
							( self.__class__.dim_celula - self.__class__.rosu_img.get_height()) // 2))
				elif self.matr[linie][coloana] == "alb":
					self.__class__.display.blit(self.__class__.alb_img,(coloana * (self.__class__.dim_celula + 1),
							linie * (self.__class__.dim_celula + 1) +
							(self.__class__.dim_celula - self.__class__.alb_img.get_height()) // 2))

		pygame.display.update()

	def __init__(self, tabla=None):
		self.piese = []
		if tabla:
			self.matr = tabla
		else:
			self.matr = [[] for _ in range(self.__class__.NR_COLOANE)]
			for i in range(self.__class__.NR_COLOANE):
				for j in range(self.__class__.NR_COLOANE):
					if i < 3 and (i + j) % 2 == 1:
						self.matr[i].append("rosu")
						self.piese.append(("rosu", i, j))
					elif i > 4 and (i + j) % 2 == 1:
						self.matr[i].append("alb")
						self.piese.append(("alb", i, j))
					else:
						self.matr[i].append(self.__class__.GOL)
				
	@classmethod
	def jucator_opus(cls, jucator):
		return cls.JMAX if jucator == cls.JMIN else cls.JMIN

	def mutari(self, jucator):
		l_mutari = []
		for piesa in self.piese:
			if piesa[0] == jucator:
				try:
					if self.matr[piesa[1] - 1][piesa[2] - 1] == Joc.GOL:
						copie_matr = copy.deepcopy(self.matr)
						copie_matr[piesa[1] - 1][piesa[2] - 1] = jucator
						copie_matr[piesa[1]][piesa[2]] = Joc.GOL
						if Joc(copie_matr) not in l_mutari:
							l_mutari.append(Joc(copie_matr))
				except IndexError:
					pass
				
				try:
					if self.matr[piesa[1] - 1][piesa[2] + 1] == Joc.GOL:
						copie_matr = copy.deepcopy(self.matr)
						copie_matr[piesa[1] - 1][piesa[2] + 1] = jucator
						copie_matr[piesa[1]][piesa[2]] = Joc.GOL
						if Joc(copie_matr) not in l_mutari:
							l_mutari.append(Joc(copie_matr))
				except IndexError:
					pass

				try:
					if self.matr[piesa[1] + 1][piesa[2] - 1] == Joc.GOL:
						copie_matr = copy.deepcopy(self.matr)
						copie_matr[piesa[1] + 1][piesa[2] - 1] = jucator
						copie_matr[piesa[1]][piesa[2]] = Joc.GOL
						if Joc(copie_matr) not in l_mutari:
							l_mutari.append(Joc(copie_matr))
				except IndexError:
					pass

				try:
					if self.matr[piesa[1] + 1][piesa[2] + 1] == Joc.GOL:
						copie_matr = copy.deepcopy(self.matr)
						copie_matr[piesa[1] + 1][piesa[2] + 1] = jucator
						copie_matr[piesa[1]][piesa[2]] = Joc.GOL
						if Joc(copie_matr) not in l_mutari:
							l_mutari.append(Joc(copie_matr))
				except IndexError:
					pass

		return l_mutari

	def numarPiese(self, jucator):
		nrPiese = 0
		for i in range(len(self.matr)):
			for j in range(len(self.matr[0])):
				if self.matr[i][j] == jucator:
					nrPiese += 1
		return nrPiese

	def final(self):
		pieseRosii = self.numarPiese("rosu")
		pieseAlbe = self.numarPiese("alb")
		if pieseRosii == 0:
			return "alb"
		elif pieseAlbe == 0:
			return "rosu"
		return False

	def estimeaza_scor(self, adancime, jucator):
		t_final = self.final()
		if adancime == 0:
			if t_final == self.__class__.JMAX:
				return 99 + adancime
			elif t_final == self.__class__.JMIN:
				return -99 - adancime
		else:
			return self.numarPiese(jucator)

	def sirAfisare(self):
		sir = "  |"
		sir += " ".join([str(i) for i in range(self.NR_COLOANE)]) + "\n"
		sir += "-" * (self.NR_COLOANE + 1) * 2 + "\n"
		for i in range(self.NR_COLOANE):  # itereaza prin linii
			sir += str(i) + " |" + " ".join([str(x) for x in self.matr[i]]) + "\n"
		return sir

	def __str__(self):
		return self.sirAfisare()

	def __repr__(self):
		return self.sirAfisare()


class Stare:

	def __init__(self, tabla_joc, j_curent, adancime, parinte=None, estimare=None):
		self.tabla_joc = tabla_joc
		self.j_curent = j_curent

		# adancimea in arborele de stari
		self.adancime = adancime

		# estimarea favorabilitatii starii (daca e finala) sau al celei mai bune stari-fiice (pentru jucatorul curent)
		self.estimare = estimare

		# lista de mutari posibile din starea curenta
		self.mutari_posibile = []

		# cea mai buna mutare din lista de mutari posibile pentru jucatorul curent
		self.stare_aleasa = None

	def mutari(self):
		l_mutari = self.tabla_joc.mutari(self.j_curent)
		joc_opus = Joc.jucator_opus(self.j_curent)
		l_stari_mutari = [Stare(mutare, joc_opus, self.adancime - 1, parinte = self) for mutare in l_mutari]
		return l_stari_mutari

	def __str__(self):
		sir = str(self.tabla_joc) + "(Jucator curent:" + self.j_curent + ")\n"
		return sir

	def verificaMutare(self, piesaInitiala, piesaFinala):
		# verifica daca pozitia pe care dorim sa mutam
		# piesa se afla la un spatiu fata de pozitia curenta
		if piesaInitiala[0] == piesaFinala[0] - 1 and piesaInitiala[1] == piesaFinala[1] - 1: return True
		if piesaInitiala[0] == piesaFinala[0] - 1 and piesaInitiala[1] == piesaFinala[1] + 1: return True
		if piesaInitiala[0] == piesaFinala[0] + 1 and piesaInitiala[1] == piesaFinala[1] - 1: return True
		if piesaInitiala[0] == piesaFinala[0] + 1 and piesaInitiala[1] == piesaFinala[1] + 1: return True

		return False


def min_max(stare):

	if stare.adancime == 0 or stare.tabla_joc.final():
		stare.estimare = stare.tabla_joc.estimeaza_scor(stare.adancime, stare.j_curent)
		return stare

	# calculez toate mutarile posibile din starea curenta
	stare.mutari_posibile = stare.mutari()

	# aplic algoritmul minimax pe toate mutarile posibile (calculand astfel subarborii lor)
	mutariCuEstimare = [min_max(mutare) for mutare in stare.mutari_posibile]

	if stare.j_curent == Joc.JMAX:
		# daca jucatorul e JMAX aleg starea-fiica cu estimarea maxima
		stare.stare_aleasa = max(mutariCuEstimare, key=lambda x: x.estimare)
	else:
		# daca jucatorul e JMIN aleg starea-fiica cu estimarea minima
		stare.stare_aleasa = min(mutariCuEstimare, key=lambda x: x.estimare)
	stare.estimare = stare.stare_aleasa.estimare
	return stare


def alpha_beta(alpha, beta, stare):
	if stare.adancime == 0 or stare.tabla_joc.final():
		stare.estimare = stare.tabla_joc.estimeaza_scor(stare.adancime, stare.j_curent)
		return stare

	if alpha > beta:
		return stare  # este intr-un interval invalid deci nu o mai procesez

	stare.mutari_posibile = stare.mutari()

	if stare.j_curent == Joc.JMAX:
		estimare_curenta = float("-inf")

		for mutare in stare.mutari_posibile:
			# calculeaza estimarea pentru starea noua, realizand subarborele
			stare_noua = alpha_beta(alpha, beta, mutare)

			if estimare_curenta < stare_noua.estimare:
				stare.stare_aleasa = stare_noua
				estimare_curenta = stare_noua.estimare
			if alpha < stare_noua.estimare:
				alpha = stare_noua.estimare
				if alpha >= beta:
					break

	elif stare.j_curent == Joc.JMIN:
		estimare_curenta = float("inf")

		for mutare in stare.mutari_posibile:

			stare_noua = alpha_beta(alpha, beta, mutare)

			if estimare_curenta > stare_noua.estimare:
				stare.stare_aleasa = stare_noua
				estimare_curenta = stare_noua.estimare

			if beta > stare_noua.estimare:
				beta = stare_noua.estimare
				if alpha >= beta:
					break
	stare.estimare = stare.stare_aleasa.estimare

	return stare


def afis_daca_final(stare_curenta):
	final = stare_curenta.tabla_joc.final()
	if final:
		if final == "remiza":
			print("Remiza!")
		else:
			print("A castigat " + final)

		return True

	return False


def main():
	# initializare algoritm
	raspuns_valid = False
	while not raspuns_valid:
		tip_algoritm = input(
			"Algorimul folosit? (raspundeti cu 1 sau 2)\n 1.Minimax\n 2.Alpha-beta\n "
		)
		if tip_algoritm in ["1", "2"]:
			raspuns_valid = True
		else:
			print("Nu ati ales o varianta corecta.")

	Joc.JMAX = "alb"
	Joc.JMIN = "rosu"

	# initializare tabla
	tabla_curenta = Joc()
	print("Tabla initiala")
	print(str(tabla_curenta))

	# creare stare initiala
	stare_curenta = Stare(tabla_curenta, "rosu", ADANCIME_MAX)

	# setari interf grafica
	pygame.init()
	pygame.display.set_caption("Lazaroiu Teodora - Dame")
	# dimensiunea ferestrei in pixeli
	# dim_celula=..
	ecran = pygame.display.set_mode(size = (807, 807))
	Joc.initializeaza(ecran)

	de_mutat = False
	tabla_curenta.deseneaza_grid()
	while True:

		if stare_curenta.j_curent == Joc.JMIN:
			for event in pygame.event.get():
				if event.type == pygame.QUIT:
					pygame.quit()
					sys.exit()
				elif event.type == pygame.MOUSEBUTTONDOWN:
					pos = pygame.mouse.get_pos()

					for linie in range(Joc.NR_COLOANE):
						for coloana in range(Joc.NR_COLOANE):

							if Joc.celuleGrid[linie][coloana].collidepoint(pos):
								# verifica daca punctul cu coord pos se afla in dreptunghi
								if (stare_curenta.tabla_joc.matr[linie][coloana] == Joc.JMIN):
									# daca am selectat un patrat care e selectat deja
									if (de_mutat and linie == de_mutat[0] and coloana == de_mutat[1]):
										de_mutat = False
										stare_curenta.tabla_joc.deseneaza_grid()
									# daca am selectat un patratel ce trebuie mutat
									else:
										de_mutat = (linie, coloana)
										stare_curenta.tabla_joc.deseneaza_grid(de_mutat)
								elif (stare_curenta.tabla_joc.matr[linie][coloana] == Joc.GOL):
									if de_mutat:
										#### eventuale teste legate de mutarea simbolului
										piesaInitiala = (de_mutat[0], de_mutat[1])
										piesaFinala = (linie, coloana)
										if (stare_curenta.verificaMutare(piesaInitiala, piesaFinala)):
											stare_curenta.tabla_joc.matr[linie][coloana] = Joc.JMIN
											stare_curenta.tabla_joc.matr[de_mutat[0]][de_mutat[1]] = Joc.GOL
											de_mutat = False
											stare_curenta.tabla_joc.deseneaza_grid()

											print("\nTabla dupa mutarea jucatorului")
											print(str(stare_curenta))

											# testez daca jocul a ajuns intr-o stare finala
											# si afisez un mesaj corespunzator in caz ca da
											if afis_daca_final(stare_curenta):
												break

											# S-a realizat o mutare. Schimb jucatorul cu cel opus
											stare_curenta.j_curent = Joc.jucator_opus(stare_curenta.j_curent)

		# --------------------------------
		else:  # jucatorul e JMAX (calculatorul)
			# Mutare calculator

			# preiau timpul in milisecunde de dinainte de mutare
			t_inainte = int(round(time.time() * 1000))
			if tip_algoritm == "1":
				stare_actualizata = min_max(stare_curenta)
			else:
				stare_actualizata = alpha_beta(-500, 500, stare_curenta)
			stare_curenta.tabla_joc = stare_actualizata.stare_aleasa.tabla_joc
			print("Tabla dupa mutarea calculatorului")
			print(str(stare_curenta))

			stare_curenta.tabla_joc.deseneaza_grid()
			t_dupa = int(round(time.time() * 1000))
			print('Calculatorul a "gandit" timp de '+ str(t_dupa - t_inainte)+ " milisecunde.")

			if afis_daca_final(stare_curenta):
				break

			# S-a realizat o mutare. Schimb jucatorul cu cel opus
			stare_curenta.j_curent = Joc.jucator_opus(stare_curenta.j_curent)


if __name__ == "__main__":
	main()
	while True:
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				pygame.quit()
				sys.exit()
