#include <fstream>
#include <iostream>

using namespace std;

const int MAXN = 101;
const int MAXM = MAXN;

int cnt = 0;
int head[MAXN];
int not_boss[MAXN];
bool vis[MAXN];

struct Edge {
    int to, next;
} E[MAXM];

void add_edge(int u, int v) {
    E[++cnt].next = head[u];
    E[cnt].to = v;
    head[u] = cnt;
}

int f[MAXN][2];

void solve(int u) {
    vis[u] = 1;
    for (int i = head[u]; i; i = E[i].next) {
        int v = E[i].to;
        if (vis[v]) continue;

        solve(v);

        f[u][1] += f[v][0]; // f[u][1]中原来就存有Ri
        f[u][0] += max(f[v][0], f[v][1]);
    }
}

int main() {
    ifstream ifs("./dance.txt");

    int n; // 总人数
    ifs >> n;

    // 快乐指数
    for (int i = 1; i <= n; ++i) ifs >> f[i][1];
    // 下属关系

    int v, u;
    while (ifs >> v >> u) {
        if (!u && !v) break;
        not_boss[v] = 1;
        add_edge(u, v);
    }

    int root;
    for (int i = 1; i <= n; ++i) {
        if (!not_boss[i]) {
            root = i;
            break;
        }
    }
    cout << "Boss: " << root << endl;

    solve(root);
    cout << "Max happiness: " << max(f[root][1], f[root][0]);

    return 0;
}