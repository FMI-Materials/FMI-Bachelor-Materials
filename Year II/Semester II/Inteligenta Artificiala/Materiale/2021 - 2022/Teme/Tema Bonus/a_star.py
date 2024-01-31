from util import *
from graph import *


def a_star(graph):
    open_list = [WalkingNode(graph.start, None, 0, graph.calculate_h(graph.start))]
    closed_list = []

    while len(open_list) > 0:

        # print("open=", open_list, sep="")
        print("closed=", closed_list, sep="")
        current_node = open_list.pop(0)
        closed_list.append(current_node)

        if graph.test_scope(current_node.info):
            return current_node

        successors = graph.generate_successors(current_node)

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

    return None


if __name__ == '__main__':
    graph = Graph()
    print(a_star(graph))
