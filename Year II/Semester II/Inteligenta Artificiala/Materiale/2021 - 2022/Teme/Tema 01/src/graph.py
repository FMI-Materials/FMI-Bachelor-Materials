import sys

from util import *
from copy import deepcopy, copy


class Node:
    def __init__(self, _id: str = "", px: int = 0, py: int = 0, insects: int = 0, max_weight: int = 0):
        """
        :param _id: str(Id nod)
        :param px: int(Poziția x)
        :param py: int(Poziția y)
        :param insects: int(Numărul de insecte de pe frunză)
        :param max_weight: int(Greutatea totală permisă)
        """
        self.id = _id
        self.pos = (px, py)
        self.insects = insects
        self.max_weight = max_weight

    def parse(self, data: str):
        """
        :param data: str(input)
        :return: Nod
        """
        data = data.split(" ")
        if len(data) != 5:
            raise Exception("Detalii frunză invalide")
        self.id = data[0]
        self.pos = (int(data[1]), int(data[2]))
        self.insects = int(data[3])
        self.max_weight = int(data[4])
        return self


class State:
    def __init__(self, node: Node, weight: int, eaten_insects: int):
        """
        :param node: Node(Frunza)
        :param weight: int(Greutatea curentă)
        :param eaten_insects: int(Numărul de insecte mâncate de pe frunză)
        """
        self.node = node
        self.pos = node.pos
        self.weight = weight
        self.eaten_insects = eaten_insects


class WalkingNode:
    def __init__(self, id: int, info: State, parent, cost=0, h=0):
        """
        :param id: int(Id nod)
        :param info: State(Starea curentă)
        :param parent: WalkingNode(Nodul părinte)
        :param cost: int(Costul din nodul start)
        :param h: int(Costul estimat până într-un nod scop)
        """
        self.id = id
        self.info = info
        self.parent = parent  # parintele din arborele de parcurgere
        self.g = cost
        self.h = h
        self.f = self.g + self.h

    def get_road(self):
        """
        :return: list[Node(Noduri părinte)]
        Implementare:
        Funcția parcurge nodurile părinte până în rădăcină
        """
        road = [self.info]
        node = self
        while node.parent is not None:
            road.insert(0, node.parent.info)
            node = node.parent
        return road

    def show_road(self):
        """
        Afișare drum parcurs din rădăcină
        """
        print(self)

    def get_eaten_insects(self, on_node: Node):
        """
        Calculare insecte mâncate de pe o frunză,
        se parcurge arborele de tați
        :param on_node: Node(Frunza curentă)
        :return: int(Numărul de insecte mâncate)
        """
        insects = 0
        current = self
        while current is not None:
            if current.info.pos == on_node.pos:
                insects += current.info.eaten_insects
            current = current.parent
        return insects

    def __repr__(self):
        """
        Reprezentare Nod
        """
        road = self.get_road()
        result = f'1) Broscuța se află pe frunza inițială: {road[0].node.id}({road[0].pos[0]},{road[0].pos[1]}).'
        result += f'\nGreutate broscuță:{road[0].weight}'
        for i in range(len(road) - 1):
            result += f'\n{i + 1}) Broscuța a sărit de la {road[i].node.id}({road[i].pos[0]}, {road[i].pos[1]}) la '
            result += f'{road[i + 1].node.id}({road[i + 1].pos[0]}, {road[i + 1].pos[1]}).'
            result += f'\nBroscuța a mâncat {road[i + 1].eaten_insects} insecte. '
            result += f'Greutate broscuță: {road[i + 1].weight}'
        result += f'\n{len(road)}) Broscuța a ajuns la mal în {len(road)} sărituri.'
        return result


# Graful problemei
class Graph:
    def __init__(self, file_path: str, heuristic: str = "admisibila_1"):
        """
        :param file_path: str(Fișier de input)
        :param heuristic: str(Tipul euristicii - banala | admisibila_1 | admisibila_2 | neadmisibila)
        """
        self.heuristic = heuristic
        with open(file_path, "r") as r:
            self.radius = int(r.readline())
            total_distance = calculate_distance((self.radius, 0))
            initial_weight = int(r.readline())
            start_node = r.readline().replace('\n', '')
            line = r.readline()
            self.nodes = []
            self.start = None
            while line:
                node = Node().parse(line)
                line = r.readline()
                # Frunza curentă este în afara lacului!
                if calculate_distance(node.pos) >= total_distance:
                    continue
                self.nodes.append(node)
                if node.id == start_node:
                    self.start = State(node, initial_weight, 0)
            if self.start is None:
                raise Exception("Nod de start inexistent")
            if self.test_scope(self.start):
                raise Exception("Nodul de start este nod scop")
            if not self.can_continue(self.start):
                raise Exception("Starea inițială nu are soluții")

    def test_scope(self, node_info: State):
        """
        Funcția ce testează dacă nodul dat este scop
        :param node_info: State(starea curenta)
        :return: bool
        """
        dist_required = calculate_distance((self.radius, 0))
        dist = dist_required - calculate_distance(node_info.pos)
        if dist > 0 and node_info.weight - 1 <= 0:
            return False
        return dist <= (node_info.weight / 3)

    def generate_successors(self, parent_node: WalkingNode, ignore_h=True):
        """
        Funcția de generare a succesorilor sub forma de noduri in arborele de parcurgere
        :param parent_node: WalkingNode(nodul părinte, ce urmează a fi expandat)
        :param ignore_h: bool(Calculăm h'?)
        :return: list[WalkingNode(succesori)]
        """
        successors_list = []
        initial_state = parent_node.info

        if not self.can_continue(initial_state):
            return []

        for node in deepcopy(self.nodes):
            node.insects -= parent_node.get_eaten_insects(node)

            if node.pos != parent_node.info.pos:
                dist = calculate_distance(node.pos, parent_node.info.pos)

                current_state = State(node, initial_state.weight, 0)

                if dist > current_state.weight / 3:
                    continue
                if (current_state.weight - 1) > node.max_weight:
                    continue

                max_add = max(0, min(node.insects, node.max_weight - (current_state.weight - 1)))

                for eat in range(max_add + 1):
                    current_state.weight = initial_state.weight + eat - 1
                    current_state.eaten_insects = eat
                    h = 0
                    if not ignore_h:
                        h = self.calculate_h(current_state)
                    # varianta cu costul 1:
                    # cost = 1
                    cost = calculate_distance(current_state.pos, parent_node.info.pos)
                    new_state = WalkingNode(-1, deepcopy(current_state), parent_node, parent_node.g + cost, h)
                    successors_list.append(new_state)

        return successors_list

    def can_continue(self, node_info: State):
        """
        Verificăm dacă din starea curentă se mai poate ajunge într-o stare finală
        :param node_info: State(Starea curentă)
        :return: bool
        """
        if self.test_scope(node_info):
            return True
        if node_info.weight - 1 <= 0:
            return False
        furthest_node = self.nodes[0]
        for node in self.nodes:
            if calculate_distance(node.pos) > calculate_distance(furthest_node.pos):
                furthest_node = node
        remaining_distance = calculate_distance((self.radius, 0)) - calculate_distance(furthest_node.pos)
        max_valid_gain = max([node.max_weight for node in self.nodes])
        total_gain = sum([node.insects for node in self.nodes]) + node_info.weight
        max_gain = min(max_valid_gain, total_gain)
        return remaining_distance < max_gain / 3

    def calculate_h(self, node_info: State):
        """
        Funcția de calculare h, implementată prin 4 tipuri de euristici
        :param node_info: State(starea curentă)
        :return: int(h' = numărul de noduri estimate până la destinație)
        """
        remaining_distance = calculate_distance((self.radius, 0)) - calculate_distance(node_info.pos)
        if self.heuristic == "banala":
            # Euristică Banala
            return remaining_distance
        elif self.heuristic == "admisibila_1":
            # Euristică admisibilă 1
            total_add_weight = sum([node.insects for node in self.nodes])
            max_valid_weight = max([node.max_weight for node in self.nodes])
            max_weight = min(max_valid_weight, total_add_weight)

            def get_next_nodes(start_node: Node, max_jump: float):
                current_dist = calculate_distance(start_node.pos)
                next_nodes = []
                for node in self.nodes:
                    dist = calculate_distance(node.pos)
                    dist_diff = calculate_distance(node.pos, start_node.pos)
                    if dist_diff <= max_jump and dist > current_dist:
                        next_nodes.append((node, dist_diff))
                return next_nodes

            def bfs(start_node: Node, max_weight: float):
                nodes_list = [(start_node, 0)]

                while len(nodes_list) > 0:
                    current_node = nodes_list.pop(0)
                    if self.test_scope(State(current_node[0], max_weight, 0)):
                        return current_node[1]
                    next_nodes = get_next_nodes(current_node[0], max_weight / 3)
                    for node in next_nodes:
                        if node not in nodes_list:
                            nodes_list.append((node[0], node[1] + current_node[1]))
                return sys.maxsize

            return bfs(node_info.node, max_weight)
        elif self.heuristic == "admisibila_2":
            # Euristică admisibilă 2
            max_add_weight = max([node.insects for node in self.nodes])
            max_valid_weight = max([node.max_weight for node in self.nodes])
            available_weight = node_info.weight

            def get_next_nodes(start_node: Node, max_jump: float):
                current_dist = calculate_distance(start_node.pos)
                next_nodes = []
                for node in self.nodes:
                    dist = calculate_distance(node.pos)
                    dist_diff = calculate_distance(node.pos, start_node.pos)
                    if dist_diff <= max_jump and dist > current_dist:
                        next_nodes.append((node, dist_diff))
                return next_nodes

            def bfs(start_node: Node, available_weight: float):
                nodes_list = [(start_node, 0)]

                while len(nodes_list) > 0:
                    new_nodes_list = []
                    for current_node in nodes_list:
                        if self.test_scope(State(current_node[0], available_weight, 0)):
                            return current_node[1]
                        next_nodes = get_next_nodes(current_node[0], available_weight / 3)

                        for node in next_nodes:
                            if node not in new_nodes_list:
                                new_nodes_list.append((node[0], node[1] + current_node[1]))
                    nodes_list = new_nodes_list

                    available_weight = min(available_weight + max_add_weight - 1, max_valid_weight)
                return sys.maxsize

            return bfs(node_info.node, available_weight)
        elif self.heuristic == "neadmisibila":
            # Euristică neadmisibilă
            h = calculate_distance(self.start.pos, self.nodes[0].pos)
            for i in range(1, len(self.nodes)):
                if self.nodes[i].id != self.start.node.id and remaining_distance < calculate_distance(
                        (self.radius, 0)) - calculate_distance(self.nodes[i].pos):
                    h += calculate_distance(self.nodes[i - 1].pos, self.nodes[i].pos)
            return h

    '''
    # Calculate h - varianta cu costul 1
    def calculate_h(self, node_info: State):
        """
        Funcția de calculare h, implementată prin 4 tipuri de euristici
        :param node_info: State(starea curentă)
        :return: int(h' = numărul de noduri estimate până la destinație)
        """
        if self.test_scope(node_info):
            return 0
        if self.heuristic == "banala":
            # Euristică Banala
            return 1
        elif self.heuristic == "admisibila_1":
            # Euristică admisibilă 1
            total_add_weight = sum([node.insects for node in self.nodes])
            max_valid_weight = max([node.max_weight for node in self.nodes])
            max_weight = min(max_valid_weight, total_add_weight)

            remaining_distance = calculate_distance((self.radius, 0)) - calculate_distance(node_info.pos)

            return remaining_distance // (max_weight / 3)
        elif self.heuristic == "admisibila_2":
            # Euristică admisibilă 2
            max_add_weight = max([node.insects for node in self.nodes])
            max_valid_weight = max([node.max_weight for node in self.nodes])
            available_weight = node_info.weight

            def get_next_nodes(start_node: Node, max_jump: float):
                current_dist = calculate_distance(start_node.pos)
                next_nodes = []
                for node in self.nodes:
                    dist = calculate_distance(node.pos)
                    dist_diff = calculate_distance(node.pos, start_node.pos)
                    if dist_diff <= max_jump and dist > current_dist:
                        next_nodes.append((node, dist_diff))
                return next_nodes

            def bfs(start_node: Node, available_weight: float):
                nodes_list = [(start_node, 0)]

                while len(nodes_list) > 0:
                    new_nodes_list = []
                    for current_node in nodes_list:
                        if self.test_scope(State(current_node[0], available_weight, 0)):
                            return current_node[1]
                        next_nodes = get_next_nodes(current_node[0], available_weight / 3)

                        for node in next_nodes:
                            if node not in new_nodes_list:
                                new_nodes_list.append((node[0], node[1] + 1))
                    nodes_list = new_nodes_list

                    available_weight = min(available_weight + max_add_weight - 1, max_valid_weight)
                return sys.maxsize

            return bfs(node_info.node, available_weight)
        elif self.heuristic == "neadmisibila":
            # Euristică neadmisibilă
            remaining_distance = calculate_distance((self.radius, 0)) - calculate_distance(node_info.pos)
            h = 0
            for i in range(1, len(self.nodes)):
                if self.nodes[i].id != self.start.node.id and remaining_distance < calculate_distance(
                        (self.radius, 0)) - calculate_distance(self.nodes[i].pos):
                    h += 1
            return h
    '''

    def __repr__(self):
        """
        Funcția de reprezentare a grafului
        :return: str
        """
        sir = ""
        for (k, v) in self.__dict__.items():
            sir += "{} = {}\n".format(k, v)
        return sir
