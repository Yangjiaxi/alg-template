from queue import Queue


class DirectedWeightedGraph:
    def __init__(self, n_nodes):  # start from 1
        self.n_nodes = n_nodes

        self.edges = {u: [] for u in self.nodes()}

        self.ori_cap = {}
        self.cap = {}

        self.clean()

    def nodes(self):
        return list(range(1, self.n_nodes + 1))

    def clean(self):
        self.vis = {u: False for u in self.nodes()}
        self.level = {u: -1 for u in self.nodes()}

    def restore(self):
        for uv, cap in self.ori_cap.items():
            self.cap[uv] = cap

    def __getitem__(self, u):
        return self.edges[u]

    def _add(self, u, v, c):  # (u, v) = c
        if (u, v) not in self.ori_cap:
            self.edges[u].append(v)
            self.ori_cap[(u, v)] = 0
            self.cap[(u, v)] = 0

        self.ori_cap[(u, v)] += c
        self.cap[(u, v)] += c

    def add(self, u, v, c):
        self._add(u, v, c)
        self._add(v, u, 0)

    def _name(self):
        return "DirectedWeightedGraph"

    def __repr__(self):
        s = f"{self._name()}:\n"
        for u, vs in self.edges.items():
            s += f"\t{u} => ["
            s += ", ".join([f"{v}({self.cap[(u,v)]}|{self.ori_cap[(u,v)]})" for v in vs])
            s += "]\n"
        return s


class FordFulkerson:
    def __init__(self, G: DirectedWeightedGraph):
        self.G = G
        self.vis = {u: False for u in self.G.nodes()}  # clean

    def clean(self):
        self.vis = {u: False for u in self.G.nodes()}

    def dfs(self, u, target, u_in):
        if u == target:
            return u_in

        self.vis[u] = True
        for v in self.G[u]:
            if not self.vis[v] and self.G.cap[(u, v)] > 0:
                forward_min_f = self.dfs(v, target, min(u_in, self.G.cap[(u, v)]))
                if forward_min_f > 0:
                    self.G.cap[(u, v)] -= forward_min_f
                    self.G.cap[(v, u)] += forward_min_f  # reversed edge
                    return forward_min_f

        return 0

    def max_flow(self, source, target):
        self.G.restore()

        flow = 0
        while f := self.dfs(source, target, 1e18):
            flow += f
            self.clean()
        return flow


class Dinic:
    def __init__(self, G: DirectedWeightedGraph):
        self.G = G
        self.level = {u: -1 for u in self.G.nodes()}
        self.start = {u: 0 for u in self.G.nodes()}

    def clean(self):
        self.level = {u: -1 for u in self.G.nodes()}
        self.start = {u: 0 for u in self.G.nodes()}

    def bfs_init(self, source, target):
        self.clean()
        self.level[source] = 0

        Q = Queue()
        Q.put(source)
        while not Q.empty():
            u = Q.get()
            for v in self.G[u]:
                if self.G.cap[(u, v)] > 0 and self.level[v] < 0:
                    self.level[v] = self.level[u] + 1
                    Q.put(v)

        return self.level[target] >= 0

    def dfs(self, u, target, u_in):
        if u == target:
            return u_in

        while self.start[u] < len(self.G[u]):
            v = self.G[u][self.start[u]]  # get `self.start[u]`-th descendant
            if self.G.cap[(u, v)] > 0 and self.level[u] < self.level[v]:
                forward_f = self.dfs(v, target, min(u_in, self.G.cap[(u, v)]))
                if forward_f > 0:
                    self.G.cap[(u, v)] -= forward_f
                    self.G.cap[(v, u)] += forward_f
                    return forward_f
            self.start[u] += 1
            # for node `u`, its descendants from `0` to `self.start[u]-1` are all exhausted
            # and its descendant with index `self.start[u]` is next to be discovered

        return 0

    def max_flow(self, source, target):
        self.G.restore()

        flow = 0
        while self.bfs_init(source, target):
            while (blocking_f := self.dfs(source, target, 1e18)) > 0:
                flow += blocking_f
        return flow


if __name__ == "__main__":
    # GG = DirectedWeightedGraph(6)
    # source, target = 1, 6
    # # book = [(0, 1, 4), (0, 2, 2), (1, 2, 1), (1, 3, 2), (1, 4, 4), (2, 4, 2), (3, 5, 3), (4, 5, 3)]
    # book = [(0, 1, 5), (0, 2, 2), (1, 2, 2), (1, 3, 2), (1, 4, 4), (2, 4, 2), (3, 5, 3), (4, 5, 3)]

    # for u, v, cap in book:
    #     GG.add(u + 1, v + 1, cap)

    # print(GG)
    # # print("ford_fulkerson:", FordFulkerson(GG).max_flow(source, target))
    # print("dinic:", Dinic(GG).max_flow(source, target))

    from pathlib import Path

    with Path("./P3376_7.in").open("r") as f:
        num_nodes, num_edges, source, target = [int(e) for e in f.readline().strip().split(" ")]
        GG = DirectedWeightedGraph(num_nodes)

        for _ in range(num_edges):
            u, v, cap = [int(e) for e in f.readline().strip().split(" ")]
            GG.add(u, v, cap)

        print("ford_fulkerson:", FordFulkerson(GG).max_flow(source, target))
        print("dinic:", Dinic(GG).max_flow(source, target))

