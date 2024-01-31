from graph import Graph, WalkingNode
from time import time
from util import *
from copy import copy


def uniform_cost_search(graph, nsol, timeout):
    """
    Algoritmul UCS
    :param graph: Graful nostru - cu detaliile problemei
    :param nsol: Numărul de soluții calculate
    :param timeout: Timpul limită alocat
    :return: list[Solution(soluții găsite)]
    """
    start_time = time()
    solutions = []
    current_solution = Solution(graph)

    # Inițializăm queue cu nodul de start
    c = [WalkingNode(-1, graph.start, None)]

    while len(c) > 0:
        # Verificam limita de timp
        if not DEBUG and check_time_limit(start_time, timeout):
            return solutions

        current_node = c.pop(0)
        # Salvăm datele soluției curente
        current_solution.total_nodes += len(c)
        current_solution.max_nodes = max(current_solution.max_nodes, len(c))

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

        successors = graph.generate_successors(current_node)
        for s in successors:
            i = 0
            found_spot = False
            for i in range(len(c)):
                if c[i].g >= s.g:
                    found_spot = True
                    break
            if found_spot:
                c.insert(i, s)
            else:
                c.append(s)
    return solutions

