'''
    Fluxuri maxime in retele de transport
    implementare folosind Bf
'''


def BFS():
    global graph, s, t, n, parent
    visited = [False] * (n)
    queue = []
    queue.append(s)
    visited[s] = True
    while queue:
        u = queue.pop(0)
        for ind, val in enumerate(graph[u]):
            if visited[ind] == False and val > 0:
                queue.append(ind)
                visited[ind] = True
                parent[ind] = u
    return True if visited[t] else False

def FordFulkerson():
    global graph, s, t, n, parent

    max_flow = 0

    while BFS():
        path_flow = float("Inf")
        cs = t
        while cs != s:
            path_flow = min(path_flow, graph[parent[cs]][cs])
            cs = parent[cs]

        max_flow += path_flow

        v = t
        while v != s:
            u = parent[v]
            graph[u][v] -= path_flow #arc direct
            graph[v][u] += path_flow #arc invers
            v = parent[v]

    return max_flow

n=6
# graf dat prin matricea de capacitati
#     s  1  2  3  4  t
graph = [[0, 6, 0, 8, 0, 0],  # s
     [0, 0, 4, 0, 3, 0],  # 1
     [0, 0, 0, 0, 0, 7],  # 2
     [0, 0, 0, 0, 4, 2],  # 3
     [0, 0, 0, 0, 0, 9],  # 4
     [0, 0, 0, 0, 0, 0]]  # t

s = 0  # S
t = 5  # T
parent = [-1] * (n)
print("Max flow: ", FordFulkerson())