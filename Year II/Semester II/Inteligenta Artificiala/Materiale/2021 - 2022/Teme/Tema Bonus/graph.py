import sys
from copy import copy

class WalkingNode:
    def __init__(self, info: str, parent, cost=0, h=0):
        self.info = info
        self.parent = parent
        self.g = cost
        self.h = h
        self.f = self.g + self.h

    def get_road(self):
        road = [self.info]
        node = self
        while node.parent is not None:
            road.insert(0, node.parent.info)
            node = node.parent
        return road

    def show_road(self):
        print(self)

    def __repr__(self):
        parent_repr = ""
        if self.parent is not None:
            parent_repr = f", parinte='{self.parent.info}'"
        return f"Nod('{self.info}', g={self.g}, f={self.f}{parent_repr})"

    def __str__(self):
        road = self.get_road()
        result = " -> ".join(road)
        result += f" cost({self.g})"
        return result


class Graph:
    def __init__(self):
        self.nodes = [chr(ord('a') + i) for i in range(7)]
        self.start = 'a'
        self.scopes = ['f']

        self.connections = dict()
        self.connections[('a', 'e')] = 5
        self.connections[('a', 'b')] = 7
        self.connections[('a', 'f')] = 17
        self.connections[('b', 'g')] = 3
        self.connections[('b', 'd')] = 4
        self.connections[('d', 'c')] = 2
        self.connections[('c', 'b')] = 3
        self.connections[('c', 'f')] = 3
        self.connections[('e', 'a')] = 1
        self.connections[('e', 'g')] = 9
        self.connections[('e', 'f')] = 14
        self.connections[('g', 'c')] = 2

        self.estimates = dict()
        self.estimates['b'] = 8
        self.estimates['c'] = 3
        self.estimates['d'] = 5
        self.estimates['e'] = 9
        self.estimates['g'] = 5
        self.estimates['f'] = 0

    def test_scope(self, node):
        return node in self.scopes

    def calculate_h(self, node):
        if node not in self.estimates:
            return sys.maxsize
        return self.estimates[node]

    def generate_successors(self, current_node):
        successors = list()
        for node in self.nodes:
            if (current_node.info, node) in self.connections:
                g = self.connections[(current_node.info, node)]
                successors.append(WalkingNode(node, copy(current_node), current_node.g + g, self.calculate_h(node)))
        return successors