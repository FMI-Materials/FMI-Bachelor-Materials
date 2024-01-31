from graph import Graph, WalkingNode
from util import *
from time import time
from copy import copy


def a_star_optimized(graph, nsol, timeout):
    """
    A* optimizat - cu liste open si closed
    :param graph: Graful nostru - cu detaliile problemei
    :param nsol: Numărul de soluții calculate
    :param timeout: Timpul limită alocat
    :return: list[Solution(soluții găsite)]
    """



    start_time = time()
    solutions = []
    current_solution = Solution(graph)

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
            open_node = in_list(open_list, s)
            closed_node = in_list(closed_list, s)
            if open_node is None and closed_node is None:
                i = 0
                found_spot = False
                for i in range(len(open_list)):
                    # diferenta e ca ordonez dupa f
                    if open_list[i].f >= s.f:
                        found_spot = True
                        break
                if found_spot:
                    open_list.insert(i, s)
                else:
                    open_list.append(s)
                continue

            if open_node is not None:
                if open_node.f > s.f:
                    open_list.remove(open_node)
                    i = 0
                    found_spot = False
                    for i in range(len(open_list)):
                        # diferenta e ca ordonez dupa f
                        if open_list[i].f >= s.f:
                            found_spot = True
                            break
                    if found_spot:
                        open_list.insert(i, s)
                    else:
                        open_list.append(s)
                    break

            if closed_node is not None:
                if closed_node.f > s.f:
                    closed_list.remove(closed_node)
                    closed_list.append(s)
                    break

    return solutions
