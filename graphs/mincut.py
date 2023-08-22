import random
import numpy as np

def karger_min_cut(edges: list, vertices: list) -> int:
    """Returns the result of the Karger min cut algorithm"""
    while len(vertices) > 2:
        index = random.choice(range(len(edges)))
        edge_to_remove = edges[index]
        u = edge_to_remove[0]
        v = edge_to_remove[1]
        edges = [(edge[0], u) if edge[1] == v else edge for edge in edges]
        edges = [(u, edge[1]) if edge[0] == v else edge for edge in edges]
        edges = [edge for edge in edges if edge != (u,u)]
        vertices.remove(v)
    return len(edges)/2


edges = []
vertices = []

file = open('data/kargerMinCut.txt', 'r')
while True:
    line = file.readline()
    if not line:
        break
    else:
        nodes = line.strip().split("\t")
    nodes = [int(c) for c in nodes]
    u = nodes[0]
    vertices.append(u)
    for v in nodes[1:len(nodes)]:
        edges.append((u,v))
file.close()

results = [karger_min_cut(edges.copy(), vertices.copy()) for i in range(100)]
    
print(min(results))


