from graph import Graph, WalkingNode
from time import time
from util import *
from copy import copy

total_nodes, max_nodes = 0, 0

start_time = 0


def build_road(graph: Graph, current_node: WalkingNode, limit: int, timeout: float):
    """
    Construire drum
    :param graph: Graph(Graful nostru - cu detaliile problemei)
    :param current_node: WalkingNode(Nodul curent)
    :param limit: int(Limita de căutare)
    :param timeout: float(timpul maxim alocat)
    :return: Solution(soluția găsită)
    """
    global total_nodes, max_nodes

    if graph.test_scope(current_node.info):
        return True, 0, current_node

    if current_node.f > limit:
        return False, current_node.f, None

    mini = float('inf')

    if not DEBUG and check_time_limit(start_time, timeout):
        return False, mini, None

    successors = graph.generate_successors(current_node, False)
    max_nodes = max(max_nodes, len(successors))
    total_nodes += len(successors)
    for s in successors:
        arrived, lim, scope_node = build_road(graph, WalkingNode(-1, s.info, current_node, s.g, s.h), limit, timeout)

        if arrived:
            return True, 0, scope_node
        mini = min(mini, lim)

    return False, mini, None


# niv = 1, facem dfs pana la nivel 1, daca am intalnit un scop => ne-am oprit, daca nu atunci distanta de la nodStart
# pana la nodScop >= 2 niv = 2 , ......, daca nu atunci distanta de la nodStart pana la NodScop >= 3 ....
def ida_star(graph, nsol, timeout):
    """
    IDA*
    :param graph: Graful nostru - cu detaliile problemei
    :param nsol: Numărul de soluții calculate
    :param timeout: Timpul limită alocat
    :return: list[Solution(soluții găsite)]
    """

    global start_time

    start_time = time()
    solutions = []
    current_solution = Solution(graph)

    # niv = h(startNod) facem dfs din nodurile care au niv >= f, daca f > niv nu apelam dfs pe succesori,
    # niv = min({f(nod) | f(nod) > niv si nod este o frunza a arborelui expandat})
    level = graph.calculate_h(graph.start)
    start_node = WalkingNode(-1, graph.start, None, 0, level)
    while True:
        # Verificam limita de timp
        if not DEBUG and check_time_limit(start_time, timeout):
            return solutions

        arrived, limit, scope_node = build_road(graph, start_node, level, timeout)
        if arrived:
            # Update date soluție curentă
            current_solution.total_nodes = total_nodes
            current_solution.max_nodes = max_nodes
            current_solution.solution = scope_node
            current_solution.time = time() - start_time
            current_solution.i += 1
            # Salvăm soluția
            solutions.append(copy(current_solution))
            nsol -= 1
            if nsol <= 0:
                return solutions
        if limit == float('inf'):
            print("Nu exista drum!")
            break
        level = limit
    return solutions
