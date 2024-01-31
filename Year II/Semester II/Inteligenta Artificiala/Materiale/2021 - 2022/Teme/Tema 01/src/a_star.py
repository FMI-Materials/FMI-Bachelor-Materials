from graph import Graph, WalkingNode
from time import time
from util import *
from copy import copy


def a_star(graph, nsol, timeout):
    """
    Algoritmul A* - neoptimizat
    :param graph: Graful nostru - cu detaliile problemei
    :param nsol: Numărul de soluții calculate
    :param timeout: Timpul limită alocat
    :return: list[Solution(soluții găsite)]
    """

    start_time = time()
    solutions = []
    current_solution = Solution(graph)

    # În coada vom avea doar noduri de tip WalkingNode (nodurile din arborele de parcurgere)
    open_list = [WalkingNode(-1, graph.start, None, 0, graph.calculate_h(graph.start))]
    closed_list = []

    while len(open_list) > 0:
        # Verificam limita de timp
        if not DEBUG and check_time_limit(start_time, timeout):
            return solutions

        # Preluăm nodul curent
        current_node = open_list.pop(0)
        closed_list.append(current_node)

        # Salvăm datele soluției curente
        current_solution.total_nodes += len(open_list)
        current_solution.max_nodes = max(current_solution.max_nodes, len(open_list))

        # Testam daca nodul curent este scop
        if graph.test_scope(current_node.info):
            # Update date soluție curentă
            current_solution.solution = current_node
            current_solution.time = time() - start_time
            current_solution.i += 1
            # Salvăm soluția
            solutions.append(copy(current_solution))
            nsol -= 1
            if nsol <= 0:
                return solutions

        successors = graph.generate_successors(current_node, False)

        for s in successors:
            node_open = in_list(open_list, s)
            if node_open is not None:
                if node_open.f > s.f:
                    open_list.remove(node_open)
                    insert_node(s, open_list)
                continue
            node_closed = in_list(closed_list, s)
            if node_closed is not None:
                if node_closed.f > s.f:
                    closed_list.remove(node_closed)
                    insert_node(s, open_list)
                continue
            insert_node(s, open_list)

    return solutions
