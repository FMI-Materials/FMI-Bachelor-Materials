import os.path
import random
import time
import copy
import pygame
import sys

BEGGINER_DEPTH = 2
MEDIUM_DEPTH = 3
ADVANCED_DEPTH = 4

"""Interfață grafică"""


class Button:
    def __init__(self, display=None, left=0, top=0, w=0, h=0, background_color=(53, 80, 115),
                 background_color_hover=(89, 134, 194), text="", font="arial", fontDimensiune=16,
                 culoareText=(255, 255, 255),
                 value=None):
        self.left = None
        self.top = None
        self.display = display
        self.background_color = background_color
        self.background_color_hover = background_color_hover
        self.text = text
        self.font = font
        self.w = w
        self.h = h
        self.selectat = False
        self.fontDimensiune = fontDimensiune
        self.culoareText = culoareText
        # creez obiectul font
        fontObj = pygame.font.SysFont(self.font, self.fontDimensiune)
        self.rendered_text = fontObj.render(self.text, True, self.culoareText)
        self.dreptunghi = pygame.Rect(left, top, w, h)
        # aici centram textul
        self.text_rectangle = self.rendered_text.get_rect(center=self.dreptunghi.center)
        self.value = value

    def select(self, sel):
        self.selectat = sel
        self.draw()

    def select_by_coord(self, coord):
        if self.dreptunghi.collidepoint(coord):
            self.select(True)
            return True
        return False

    def update_rectangle(self):
        self.dreptunghi.left = self.left
        self.dreptunghi.top = self.top
        self.text_rectangle = self.rendered_text.get_rect(center=self.dreptunghi.center)

    def draw(self):
        color = self.background_color_hover if self.selectat else self.background_color
        pygame.draw.rect(self.display, color, self.dreptunghi)
        self.display.blit(self.rendered_text, self.text_rectangle)


class GrupButoane:
    def __init__(self, buttons_list=None, selected_index=0, spatiuButoane=10, left=0, top=0):
        if buttons_list is None:
            buttons_list = []
        self.buttons_list = buttons_list
        self.selected_index = selected_index
        self.buttons_list[self.selected_index].selectat = True
        self.top = top
        self.left = left
        left_current = self.left
        for b in self.buttons_list:
            b.top = self.top
            b.left = left_current
            b.update_rectangle()
            left_current += (spatiuButoane + b.w)

    def select_by_coord(self, coord):
        for ib, b in enumerate(self.buttons_list):
            if b.select_by_coord(coord):
                self.buttons_list[self.selected_index].select(False)
                self.selected_index = ib
                return True
        return False

    def draw(self):
        for b in self.buttons_list:
            b.draw()

    def get_value(self):
        return self.buttons_list[self.selected_index].value


"""Setări Joc"""


class Game:
    """
    Clasa care definește jocul.
    """
    COLUMNS = 8
    JMIN = 'a'
    JMAX = 'n'
    EMPTY = '#'
    # 1 - left, 0 - right
    ORIENTATION = 1

    grid_cells = None
    end_game_button = None



    def __init__(self, table=None):  # Game()
        self.calculated_moves = dict()
        self.calculated_piece_moves = dict()
        if table is not None:
            self.matrix = table
            return
        self.matrix = [[self.EMPTY for _ in range(self.COLUMNS)] for _ in range(self.COLUMNS)]
        self.matrix[0] = [self.EMPTY if i % 2 == self.ORIENTATION else self.JMIN for i in range(self.COLUMNS)]
        self.matrix[1] = [self.EMPTY if i % 2 != self.ORIENTATION else self.JMIN for i in range(self.COLUMNS)]
        self.matrix[2] = [self.EMPTY if i % 2 == self.ORIENTATION else self.JMIN for i in range(self.COLUMNS)]
        self.matrix[5] = [self.EMPTY if i % 2 != self.ORIENTATION else self.JMAX for i in range(self.COLUMNS)]
        self.matrix[6] = [self.EMPTY if i % 2 == self.ORIENTATION else self.JMAX for i in range(self.COLUMNS)]
        self.matrix[7] = [self.EMPTY if i % 2 != self.ORIENTATION else self.JMAX for i in range(self.COLUMNS)]

    def draw_grid(self, marked_line=None, marked_column=None, marked_player=None):

        for ind in range(self.COLUMNS ** 2):
            line = ind // self.COLUMNS
            column = ind % self.COLUMNS

            if (line + column) % 2 == self.ORIENTATION:
                color = (255, 255, 255)
            elif column == marked_column and line == marked_line:
                color = (100, 100, 100)
            else:
                color = (10, 10, 10)
            if self.matrix[line][column].lower() == marked_player:
                color = (10, 200, 10)

            pygame.draw.rect(self.display, color, self.grid_cells[ind])
            piece_img = None
            if self.matrix[line][column] == 'a':
                piece_img = self.a_img
            elif self.matrix[line][column] == 'A':
                piece_img = self.a_king_img
            elif self.matrix[line][column] == 'n':
                piece_img = self.n_img
            elif self.matrix[line][column] == 'N':
                piece_img = self.n_king_img
            if piece_img:
                self.display.blit(piece_img,
                                  (column * (self.cell_size + 1), line * (self.cell_size + 1) + self.top_offset))

        self.end_game_button.draw()
        pygame.display.update()

    @classmethod
    def opposite_player(cls, player):
        return cls.JMAX if player == cls.JMIN else cls.JMIN

    @classmethod
    def initialize(cls, display, cell_size=100):
        def load_image(name):
            img = pygame.image.load(os.path.join("assets", name))
            return pygame.transform.scale(img, (cell_size, cell_size))

        cls.end_game_button = Button(display=display, left=10, top=10, w=90, h=30, text="Oprire joc",
                                     background_color=(200, 0, 0), background_color_hover=(255, 0, 0))
        cls.top_offset = 50
        cls.display = display
        cls.cell_size = cell_size
        cls.a_img = load_image("a.png")
        cls.a_king_img = load_image("a_king.png")
        cls.n_img = load_image("n.png")
        cls.n_king_img = load_image("n_king.png")
        cls.grid_cells = []
        for line in range(Game.COLUMNS):
            for column in range(Game.COLUMNS):
                square = pygame.Rect(column * (cell_size + 1), line * (cell_size + 1) + cls.top_offset, cell_size,
                                     cell_size)
                cls.grid_cells.append(square)

    def player_pieces(self, player, case_sensitive=False):
        """
        Calculare piese player
        :param player: player (a sau n)
        :param case_sensitive: Conteaza daca e rege sau nu?
        :return: int(numarul de piese)
        """
        counter = 0
        for i in range(self.COLUMNS):
            if not case_sensitive:
                counter += len([0 for x in self.matrix[i] if x.lower() == player])
            else:
                counter += len([0 for x in self.matrix[i] if x == player])
        return counter

    def final(self):
        """
        Verificare joc final
        :return: bool(False)|char(Jucator)|String("draw")
        """
        if self.player_pieces(self.JMIN) == 0:
            return self.JMAX
        elif self.player_pieces(self.JMAX) == 0:
            return self.JMIN
        elif len(self.moves(self.JMIN)) == 0:
            return self.JMAX
        elif len(self.moves(self.JMAX)) == 0:
            return self.JMIN
        elif len(self.moves(self.JMIN)) == 0 and len(self.moves(self.JMAX)) == 0:
            return 'draw'
        return False

    def valid_spot(self, x, y):
        """
        Verificare pozitie pe tabla
        :param x: Pozitia x
        :param y: Pozitia y
        :return: bool(pozitie valida)
        """
        return 0 <= x < self.COLUMNS and 0 <= y < self.COLUMNS

    def piece_moves(self, x, y, player):
        """
        Toate mutarile posibile ale unei piese dintr-o locatie specificata
        :param x: Pozitia x
        :param y: Pozitia y
        :param player: Jucatorul curent
        :return: Pair(Joc cu tabla actualizata, pozitie noua)
        Implementare:
        Pentru piesele care nu sunt regi, mutarile posibile sunt:
           - dreapta sus, stanga sus - pentru n
           - dreapta jos, stanga jos - pentru a
        Regii pot parcurge toate aceste pozitii
        In cazul in care urmatoarea pozitie nu este goala, dar este ocupata de un player din echipa opusa,
        verificam daca il putem captura (sarind peste el) - capturarea se poate face si repetat.
        Exemplu:
          # # # # #      # # # # n
          # # # a #      # # # # #
          # # # # #  --> # # # # #
          # a # # #      # # # # #
          n # # # #      # # # # #
        """
        if (x, y, player) in self.calculated_piece_moves:
            return self.calculated_piece_moves[(x, y, player)]
        moves = []
        if self.matrix[x][y] == 'n':
            dx, dy = [-1, -1], [-1, 1]
        elif self.matrix[x][y] == 'a':
            dx, dy = [1, 1], [-1, 1]
        else:  # King
            dx, dy = [-1, 1, -1, 1], [1, 1, -1, -1]

        for k in range(len(dx)):
            nx, ny = dx[k] + x, dy[k] + y
            current_matr = copy.deepcopy(self.matrix)
            if not self.valid_spot(nx, ny) or self.matrix[nx][ny].lower() == player:
                continue
            if self.matrix[nx][ny] != self.EMPTY:
                n2x, n2y = dx[k] + nx, dy[k] + ny
                while self.matrix[nx][ny].lower() == self.opposite_player(player) and self.valid_spot(n2x, n2y) and \
                        self.matrix[n2x][n2y] == self.EMPTY:
                    current_matr[nx][ny] = self.EMPTY
                    nx, ny = n2x, n2y
                    n2x, n2y = dx[k] + nx, dy[k] + ny
            if self.matrix[nx][ny] != self.EMPTY:
                continue
            current_matr[nx][ny] = current_matr[x][y]
            current_matr[x][y] = Game.EMPTY
            if player == 'n' and nx == 0:
                current_matr[nx][ny] = current_matr[nx][ny].upper()
            elif player == 'a' and nx == Game.COLUMNS - 1:
                current_matr[nx][ny] = current_matr[nx][ny].upper()
            moves.append((Game(current_matr), (nx, ny)))
        self.calculated_piece_moves[(x, y, player)] = copy.deepcopy(moves)
        return moves

    def moves(self, player):
        """
        Genereaza toate mutarile posibile ale unui player
        :param player: Jucatorul curent
        :return: List[Pair(Joc cu tabla actualizata, pozitie noua)]
        Implementare:
        Algoritmul moves parcurge toate patratelele in care se afla jucatorul dat
        si genereaza prin functia piece_moves toate mutarile posibile
        """
        if player in self.calculated_moves:
            return self.calculated_moves[player]
        moves = []
        for i in range(self.COLUMNS):
            for j in range(self.COLUMNS):
                if self.matrix[i][j].lower() == player:
                    moves.extend(self.piece_moves(i, j, player))
        self.calculated_moves[player] = copy.deepcopy(moves)
        return moves

    def estimate_score_1(self, depth=0):
        """
        Functia de estimare scor (varianta 1)
        :param depth: Adancimea arborelui minimax sau alpha-beta
        :return: int(scor)
        Implementare:
         - Cazul in care jucatorul castiga, returnam 99 + depth
         - Cazul in care jucatorul pierde, returnam = -99 - depth
         - Cazul de remiza (nu ne intereseaza mutarea) = 0
         - Altfel:
             - Calculam diferenta de piese dintre jucatori (maximizand JMAX si minimizand JMIN)
             - Calculam diferenta de regi dintre jucatori (maximizand JMAX si minimizand JMIN)
             - Returnam suma proportionata dintre cele 2 (in ordinea importantei: mutarile posibile, numarul de regi)
        """
        t_final = self.final()
        if t_final == self.JMAX:
            return 99 + depth
        elif t_final == self.JMIN:
            return -99 - depth
        elif t_final == 'draw':
            return 0
        else:
            pieces_diff = self.player_pieces(self.JMAX) - self.player_pieces(self.JMIN)
            kings_diff = self.player_pieces(self.JMAX.upper(), True) - self.player_pieces(self.JMIN.upper(), True)
            return 1 * pieces_diff + 2 * kings_diff

    def estimate_score_2(self, depth=0):
        """
        Functia de estimare scor (varianta 2)
        :param depth: Adancimea arborelui minimax sau alpha-beta
        :return: int(scor)
        Implementare:
         - Cazul in care jucatorul castiga, returnam 1000 + depth
         - Cazul in care jucatorul pierde, returnam -1000 - depth
         - Cazul de remiza (nu ne intereseaza mutarea) = 0
         - Altfel:
             - Calculam diferenta de piese dintre jucatori (maximizand JMAX si minimizand JMIN)
             - Calculam diferenta de regi dintre jucatori (maximizand JMAX si minimizand JMIN)
             - Calculam numarul de mutari posibile pentru JMAX si pentru JMIN
             - Returnam suma proportionata dintre cele 3 (in ordinea importantei: mutarile posibile, numarul de regi, numarul de piese)
        Eficienta: Fata de prima varianta de estimare, aceasta varianta este mai costisitoare din punct de vedere al timpului de rulare
        """
        t_final = self.final()
        if t_final == self.JMAX:
            return 1000 + depth
        elif t_final == self.JMIN:
            return -1000 - depth
        elif t_final == 'draw':
            return 0
        else:
            pieces_diff = self.player_pieces(self.JMAX) - self.player_pieces(self.JMIN)
            kings_diff = self.player_pieces(self.JMAX.upper(), True) - self.player_pieces(self.JMIN.upper(), True)
            possible_moves = len(self.moves(self.JMAX)) - len(self.moves(self.JMIN))
            return 1 * pieces_diff + 2 * kings_diff + 4 * possible_moves

    def estimate_score(self, depth, estimate_function="computer_1"):
        """
        :param depth: Adâncimea arborelui minimax sau alpha-beta
        :param estimate_function: funcția de estimare - varianta 1 sau 2
        :return: int(scorul estimat de una dintre cele 2 funcții)
        """
        if estimate_function == "computer_1":
            return self.estimate_score_1(depth)
        return self.estimate_score_2(depth)

    def to_string(self):
        """
        Afisare tabla de joc
        :return: String(tabla de joc)
        """
        sir = "  |"
        sir += " ".join([chr(ord('a') + i) for i in range(self.COLUMNS)]) + "\n"
        sir += "-" * (self.COLUMNS + 1) * 2 + "\n"
        for i in range(self.COLUMNS):
            sir += str(i) + " |" + " ".join(self.matrix[i]) + "\n"
        return sir

    def __str__(self):
        return self.to_string()

    def __repr__(self):
        return self.to_string()


class State:
    """
    Clasa folosita de algoritmii minimax si alpha-beta
    O instanta din clasa state este un nod din arborele minimax
    Are ca proprietate table de joc
    Functioneaza cu conditia ca in cadrul clasei Game sa fie definiti JMIN si JMAX (cei doi jucatori posibili)
    De asemenea cere ca in clasa Game sa fie definita si o metoda numita moves() care ofera lista cu configuratiile posibile in urma mutarii unui player
    """

    def __init__(self, game_table, j_curent, depth, parent=None, estimate=None):
        self.game_table = game_table
        self.j_curent = j_curent

        self.nodes = 0

        # adancimea in arborele de stari
        self.depth = depth

        # estimarea favorabilitatii starii (daca e finala) sau al celei mai bune stari-fiice (pentru jucatorul curent)
        self.estimate = estimate

        # lista de moves posibile (tot de tip State) din starea curenta
        self.possible_moves = []

        # cea mai buna move din lista de moves posibile pentru jucatorul curent
        # e de tip State (cel mai bun succesor)
        self.chosen_state = None

    def moves(self):
        l_mutari = self.game_table.moves(self.j_curent)  # lista de informatii din nodurile succesoare
        juc_opus = Game.opposite_player(self.j_curent)

        # mai jos calculam lista de noduri-fii (succesori)
        l_stari_mutari = [State(move[0], juc_opus, self.depth - 1, parent=self) for move in l_mutari]

        return l_stari_mutari

    def __str__(self):
        sir = str(self.game_table) + "(Juc curent:" + self.j_curent + ")\n"
        return sir


""" Algoritmul MinMax """


def min_max(state, estimate_function="computer_1"):
    # daca sunt la o frunza in arborele minimax sau la o state finala
    if state.depth == 0 or state.game_table.final():
        state.estimate = state.game_table.estimate_score(state.depth, estimate_function)
        state.nodes = 1
        return state

    # calculez toate mutarile posibile din starea curenta
    state.possible_moves = state.moves()

    # aplic algoritmul minimax pe toate mutarile posibile (calculand astfel subarborii lor)
    # expandez(constr subarb) fiecare nod x din moves posibile
    moves_with_estimate = [min_max(x, estimate_function) for x in state.possible_moves]
    state.nodes += sum([x.nodes for x in moves_with_estimate])

    if state.j_curent == Game.JMAX:
        # daca jucatorul e JMAX aleg starea-fiica cu estimarea maxima
        state.chosen_state = max(moves_with_estimate, key=lambda x: x.estimate)
        # def f(x): return x.estimate -----> key=f
    else:
        # daca jucatorul e JMIN aleg starea-fiica cu estimarea minima
        state.chosen_state = min(moves_with_estimate, key=lambda x: x.estimate)

    state.estimate = state.chosen_state.estimate
    return state


""" Algoritmul Alpha Beta """


def alpha_beta(alpha, beta, state, estimate_function="computer_1"):
    if state.depth == 0 or state.game_table.final():
        state.estimate = state.game_table.estimate_score(state.depth, estimate_function)
        state.nodes = 1
        return state

    if alpha > beta:
        return state  # este intr-un interval invalid deci nu o mai procesez

    state.possible_moves = state.moves()

    if state.j_curent == Game.JMAX:
        current_estimation = float('-inf')  # in aceasta variabila calculam maximul

        # Ordonarea succesorilor înainte de expandare (bazat pe estimare)
        state.possible_moves.sort(key=lambda x: x.game_table.estimate_score(state.depth, estimate_function),
                                  reverse=True)

        for move in state.possible_moves:
            # calculează estimarea pentru starea nouă, realizând subarborele
            # aici construim subarborele pentru new_state
            new_state = alpha_beta(alpha, beta, move, estimate_function)
            state.nodes += new_state.nodes
            if current_estimation < new_state.estimate:
                state.chosen_state = new_state
                current_estimation = new_state.estimate
            if alpha < new_state.estimate:
                alpha = new_state.estimate
                if alpha >= beta:
                    break

    elif state.j_curent == Game.JMIN:
        current_estimation = float('inf')

        # Ordonarea succesorilor înainte de expandare (bazat pe estimare)
        state.possible_moves.sort(key=lambda x: x.game_table.estimate_score(state.depth, estimate_function))

        for move in state.possible_moves:
            # calculează estimarea
            # aici construim subarborele pentru new_state
            new_state = alpha_beta(alpha, beta, move, estimate_function)
            state.nodes += new_state.nodes
            if current_estimation > new_state.estimate:
                state.chosen_state = new_state
                current_estimation = new_state.estimate
            if beta > new_state.estimate:
                beta = new_state.estimate
                if alpha >= beta:
                    break

    state.estimate = state.chosen_state.estimate

    return state


def show_if_final(current_state):
    """
    Afisare stare finala
    :param current_state: State-ul curent al jocului
    :return: bool(este stare finala)
    """
    final = current_state.game_table.final()
    if final:
        if final == "draw":
            print("Remiza!")
        else:
            print("A câștigat " + final)
            current_state.game_table.draw_grid(marked_player=final)
        return True
    return False


def draw_options(display, tabla_curenta):
    btn_alg = GrupButoane(
        top=30,
        left=30,
        buttons_list=[
            Button(display=display, w=80, h=30, text="minimax", value="minimax"),
            Button(display=display, w=80, h=30, text="alphabeta", value="alphabeta")
        ],
        selected_index=0)
    btn_juc = GrupButoane(
        top=100,
        left=30,
        buttons_list=[
            Button(display=display, w=35, h=30, text="a", value="a"),
            Button(display=display, w=35, h=30, text="n", value="n")
        ],
        selected_index=1)
    btn_nivel = GrupButoane(
        top=170,
        left=30,
        buttons_list=[
            Button(display=display, w=90, h=30, text="Incepător", value=BEGGINER_DEPTH),
            Button(display=display, w=90, h=30, text="Mediu", value=MEDIUM_DEPTH),
            Button(display=display, w=90, h=30, text="Avansat", value=ADVANCED_DEPTH),
        ],
        selected_index=0)
    btn_mod = GrupButoane(
        top=240,
        left=30,
        buttons_list=[
            Button(display=display, w=110, h=30, text="Juc v Juc", value={"a": "player", "n": "player"}),
            Button(display=display, w=110, h=30, text="Juc v Calc", value={"a": "player", "n": "computer_2"}),
            Button(display=display, w=110, h=30, text="Calc v Calc", value={"a": "computer_2", "n": "computer_1"}),
        ],
        selected_index=1)
    ok = Button(display=display, top=310, left=30, w=40, h=30, text="ok", background_color=(155, 0, 55))
    btn_alg.draw()
    btn_juc.draw()
    btn_nivel.draw()
    btn_mod.draw()
    ok.draw()
    while True:
        for ev in pygame.event.get():
            if ev.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif ev.type == pygame.MOUSEBUTTONDOWN:
                pos = pygame.mouse.get_pos()
                if not btn_alg.select_by_coord(pos) and not btn_juc.select_by_coord(
                        pos) and not btn_nivel.select_by_coord(pos) and not btn_mod.select_by_coord(pos):
                    if ok.select_by_coord(pos):
                        display.fill((0, 0, 0))
                        tabla_curenta.draw_grid()
                        return btn_juc.get_value(), btn_alg.get_value(), btn_nivel.get_value(), btn_mod.get_value()
        pygame.display.update()


class Logger:
    """
    Clasa de game_logger, afisam in consola:
      - Durata jocului
      - Numărul de noduri generate (în arborele minimax, respectiv alpha-beta) la fiecare move.
      - La final afișăm numărul minim, maxim, mediu și mediana pentru numarul de noduri generat pentru fiecare move.
    """

    def __init__(self, algorithm):
        self.algorithm = algorithm
        self.min_nodes = sys.maxsize
        self.max_nodes = 0
        self.moves_nodes = []

        self.moves_a = 0
        self.moves_n = 0

        self.start_time = time.time()
        self.current_time = time.time()

        self.current_state = None

    def get_current_time_diff(self, time_start=None):
        if time_start is None:
            time_start = self.start_time
        return round((time.time() - time_start) * 1000)

    def update_moves(self, current_state):
        if current_state.j_curent.lower() == 'n':
            self.moves_n += 1
        if current_state.j_curent.lower() == 'a':
            self.moves_a += 1

    def update_nodes(self, nodes):
        print(f"\nAu fost generate {nodes} noduri")
        self.min_nodes = min(self.min_nodes, nodes)
        self.max_nodes = max(self.max_nodes, nodes)
        self.moves_nodes.append(nodes)

    def update_current_state(self, new_state, player="calculator"):
        """
        Afișare timp de gândire după fiecare move
        :param player: Calculator sau Utilizator
        """
        print(
            f"{player[0].upper() + player[1:]}ul a \"gândit\" timp de {self.get_current_time_diff(self.current_time)} milisecunde.")
        print(f"Scor {player}: {new_state.game_table.estimate_score_2()}")
        print(f"\nTabla dupa mutarea {player}ului: ")
        print(str(new_state))
        self.current_state = new_state
        self.current_time = time.time()

    def to_string(self):
        str = f"\nJocul a durat {self.get_current_time_diff()} ms."
        str += f"\nMutări a: {self.moves_a}"
        str += f"\nMutări n: {self.moves_n}"
        str += f"\nAlgoritmul {self.algorithm} a generat un număr minim de {self.min_nodes} noduri și maxim de {self.max_nodes} noduri "
        if len(self.moves_nodes) < 2:
            return str
        mean_nodes = round(sum(self.moves_nodes) / len(self.moves_nodes))
        str += f"\nMedia nodurilor generate este de {mean_nodes} pe mutare"
        median_nodes = self.moves_nodes[len(self.moves_nodes) // 2 + len(self.moves_nodes) % 2]
        str += f"\nMediana nodurilor generate este de {median_nodes} pe mutare"
        return str

    def __str__(self):
        return self.to_string()

    def __repr__(self):
        return self.to_string()


def main():
    # setări interfață grafică
    pygame.init()
    pygame.display.set_caption("Buhai Darius - Dame")
    # dimensiunea ferestrei in pixeli
    w = 50
    ecran = pygame.display.set_mode(size=(Game.COLUMNS * (w + 1) - 1, Game.COLUMNS * (w + 1) - 1 + 50))
    Game.initialize(ecran, cell_size=w)

    # inițializare table
    current_table = Game()  # apelam constructorul
    print("Tabla initiala")
    print(str(current_table))

    Game.JMIN, algorithm, depth, game_mode = draw_options(ecran, current_table)
    Game.JMAX = 'n' if Game.JMIN == 'a' else 'a'
    if Game.JMAX == 'a':
        game_mode['n'], game_mode['a'] = game_mode['a'], game_mode['n']

    current_state = State(current_table, 'n', depth)
    current_table.draw_grid()

    # inițializăm game_logger - informații joc
    game_logger = Logger(algorithm)

    selected_square = None
    while True:
        if game_mode[current_state.j_curent] == "player":
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                if event.type == pygame.MOUSEMOTION:
                    pos = pygame.mouse.get_pos()  # coordonatele cursorului
                    for np in range(len(Game.grid_cells)):
                        if Game.grid_cells[np].collidepoint(pos):
                            current_state.game_table.draw_grid(marked_line=np // Game.COLUMNS,
                                                               marked_column=np % Game.COLUMNS)
                            break
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    pos = pygame.mouse.get_pos()
                    if Game.end_game_button.select_by_coord(pos):
                        print(str(game_logger))
                        pygame.quit()
                        sys.exit()
                    for np in range(len(Game.grid_cells)):
                        if Game.grid_cells[np].collidepoint(pos):
                            line = np // Game.COLUMNS
                            column = np % Game.COLUMNS

                            found_valid = False
                            if selected_square is not None:
                                valid_moves = current_state.game_table.piece_moves(selected_square[0],
                                                                                   selected_square[1],
                                                                                   current_state.j_curent)
                                found_valid = False
                                for valid_move in valid_moves:
                                    if (line, column) == valid_move[1]:
                                        current_state.game_table = valid_move[0]
                                        found_valid = True
                                        break
                            if not found_valid and current_state.game_table.matrix[line][
                                column].lower() == current_state.j_curent:
                                selected_square = (line, column)

                            if found_valid:
                                # Afisam noua tabla
                                current_state.game_table.draw_grid()

                                # Afisam timpul de gandire, scorul si noua tabla
                                game_logger.update_current_state(current_state, "utilizator")
                                game_logger.update_moves(current_state)

                                if show_if_final(current_state):
                                    break
                                selected_square = None

                                # S-a realizat o move. Schimb jucatorul cu cel opus
                                current_state.j_curent = Game.opposite_player(current_state.j_curent)

        else:  # jucătorul e JMAX (calculatorul)
            # Mutare calculator
            print("Acum mută calculatorul cu simbolul", current_state.j_curent)

            # state actualizata e starea mea curenta in care am setat chosen_state (mutarea urmatoare)
            if algorithm == "minimax":
                stare_actualizata = min_max(current_state, game_mode[current_state.j_curent])
            else:
                stare_actualizata = alpha_beta(-500, 500, current_state, game_mode[current_state.j_curent])

            # Aici se face de fapt mutarea
            current_state.game_table = stare_actualizata.chosen_state.game_table
            current_state.game_table.draw_grid()

            # Afisam timpul de gandire, scorul si noua tabla
            game_logger.update_nodes(stare_actualizata.nodes)
            game_logger.update_current_state(current_state, "calculator")
            game_logger.update_moves(current_state)

            if show_if_final(current_state):
                break

            # S-a realizat o move. Schimb jucătorul cu cel opus
            current_state.j_curent = Game.opposite_player(current_state.j_curent)

    print(str(game_logger))


if __name__ == "__main__":
    main()
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
