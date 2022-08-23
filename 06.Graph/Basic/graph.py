class DirectedWeightedGraph:
    def __init__(self, n_nodes):
        self.n_nodes = n_nodes

        self.vis = {u: False for u in range(self.n_nodes)}
        self.edges = {u: [] for u in range(self.n_nodes)}
        self.W = {}

    def __getitem__(self, u):
        return self.edges[u]

    def clear_tags(self):
        self.g_time = 0
        self.vis = {u: False for u in range(self.n_nodes)}

    def add(self, u, v, w=1):  # (u, v) = w
        self.edges[u].append(v)
        self.W[(u, v)] = w
        return self

    def weight(self, u, v):
        return self.W.get((u, v), None)

    def _name(self):
        return "DirectedWeightedGraph"

    def __repr__(self):
        s = f"{self._name()}:\n"
        for u, vs in self.edges.items():
            s += f"\t{u} => ["
            s += ", ".join([f"{v}({self.weight(u,v)})" for v in vs])
            s += "]\n"
        return s


class UndirectedWeightedGraph(DirectedWeightedGraph):
    def __init__(self, n_nodes):
        super().__init__(n_nodes)

    def add(self, u, v, w=1):  # (u, v) = (v, u) = w
        super().add(u, v, w)
        super().add(v, u, w)
        return self

    def _name(self):
        return "UndirectedWeightedGraph"


if __name__ == "__main__":
    g_dw = DirectedWeightedGraph(4)  # 0123
    g_dw.add(0, 1).add(0, 2).add(2, 3).add(3, 0).add(1, 3)
    print(g_dw)

    g_uw = UndirectedWeightedGraph(4)  # 0123
    g_uw.add(0, 1).add(0, 2).add(2, 3).add(3, 0).add(1, 3)
    print(g_uw)

