from copy import deepcopy
from queue import Queue


class DirectedWeightedGraph:
    def __init__(self, n_nodes):  # start from 1
        self.n_nodes = n_nodes

        self.edges = {u: [] for u in range(self.n_nodes + 1)}

        self.capacity = {}
        self.residual = {}

    def __getitem__(self, u):
        return self.edges[u]

    def reset_residual(self):
        self.residual = {}
        for uv, cap in self.capacity.items():
            self.residual[uv] = cap

    def add(self, u, v, cap):  # (u, v) = w
        self.edges[u].append(v)
        self.capacity[(u, v)] = cap
        self.residual[(u, v)] = cap

    def _name(self):
        return "DirectedWeightedGraph"

    def __repr__(self):
        s = f"{self._name()}:\n"
        for u, vs in self.edges.items():
            s += f"\t{u} => ["
            s += ", ".join([f"{v}({self.residual[(u,v)]}|{self.capacity[(u,v)]})" for v in vs])
            s += "]\n"
        return s


def dfs_path(G: DirectedWeightedGraph, source, target):
    path = []
    vis = {u: False for u in range(G.n_nodes + 1)}

    def do_dfs(u):
        if u == target:
            return True

        for v in G[u]:
            if not vis[v] and G.residual[(u, v)] > 0:
                vis[v] = True

                path.append(v)
                if do_dfs(v):
                    return True
                path.pop()

    vis[source] = True
    do_dfs(source)

    if not path:
        return False, None, None

    path.insert(0, source)
    min_flow = G.residual[(path[0], path[1])]
    for u, v in zip(path, path[1:]):
        min_flow = min(min_flow, G.residual[(u, v)])
    return True, path, min_flow


def naive_max_flow(G: DirectedWeightedGraph, source, target):
    G.reset_residual()

    while True:
        found, path, min_flow = dfs_path(G, source, target)
        if not found:
            break

        for u, v in zip(path, path[1:]):
            G.residual[(u, v)] -= min_flow

    flow = 0
    for v in G[source]:
        flow += G.capacity[(source, v)] - G.residual[(source, v)]

    return flow


def ford_fulkerson(G: DirectedWeightedGraph, source, target):
    RG = deepcopy(G)
    RG.reset_residual()

    while True:
        found, path, min_flow = dfs_path(RG, source, target)
        if not found:
            break

        for u, v in zip(path, path[1:]):
            RG.residual[(u, v)] -= min_flow
            if (v, u) not in RG.residual:
                RG.add(v, u, min_flow)
            else:
                RG.residual[(v, u)] += min_flow

    flow = 0
    for v in RG[source]:  # Original Graph
        flow += RG.capacity[(source, v)] - RG.residual[(source, v)]

    return flow


if __name__ == "__main__":
    # G = DirectedWeightedGraph(5)
    # source, target = 0, 5
    # # book = [(0, 1, 4), (0, 2, 2), (1, 2, 1), (1, 3, 2), (1, 4, 4), (2, 4, 2), (3, 5, 3), (4, 5, 3)]
    # book = [(0, 1, 5), (0, 2, 2), (1, 2, 2), (1, 3, 2), (1, 4, 4), (2, 4, 2), (3, 5, 3), (4, 5, 3)]

    # for u, v, cap in book:
    #     G.add(u, v, cap)

    # print(G)

    # print("naive_max_flow:", naive_max_flow(G, source, target))
    # print("ford_fulkerson:", ford_fulkerson(G, source, target))

    from pathlib import Path

    with Path("./P3376_7.in").open("r") as f:
        num_nodes, num_edges, source, target = [int(e) for e in f.readline().strip().split(" ")]
        G = DirectedWeightedGraph(num_nodes)

        for _ in range(num_edges):
            u, v, cap = [int(e) for e in f.readline().strip().split(" ")]
            G.add(u, v, cap)
        print("naive_max_flow:", naive_max_flow(G, source, target))
        print("ford_fulkerson:", ford_fulkerson(G, source, target))

