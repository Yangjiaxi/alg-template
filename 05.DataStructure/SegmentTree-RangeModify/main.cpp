#include "utils.h"
#include <iostream>
#include <vector>

using namespace std;

#define MID(x, y) ((x) + ((y) - (x)) / 2)

/*
    线段树: 区间修改
    Add(L, R, v): A[L..R] += v

    Query(L, R):  计算min(A[L..R]) / max(A[L...R]) / sum(A[L..R])
*/

const int MAXN = 1005;
const int INF = 0x3f3f3f3f;
using LL = long long int;

struct Info {
    // Info to show
    LL maxv;
    LL minv;
    LL sumv;

    Info() : maxv(0), minv(0), sumv(0) {}
    Info(LL maxv, LL minv, LL sumv) : maxv(maxv), minv(minv), sumv(sumv) {}

    void set(LL n) { this->maxv = this->minv = this->sumv = n; }

    void merge(Info &a, Info &b) {
        this->maxv = max(a.maxv, b.maxv);
        this->minv = min(a.minv, b.minv);
        this->sumv = a.maxv + b.maxv;
    }

    void update(Info &other) { merge(*this, other); }
    void clear() { this->maxv = this->minv = this->sumv = 0; }
};

struct SegmentTree {
    using Interval = optional<pair<int, int>>;

    int y1, y2;
    int v;
    int n;

    LL a[MAXN];
    Info node[MAXN * 4];
    Interval seg[MAXN * 4];
    LL addv[MAXN * 4]; // inner maintain

    SegmentTree(int n) : seg(), node(), addv() { this->n = n; }

    void _build(int o, int L, int R) {
        seg[o] = make_pair(L, R);
        if (L == R) {
            node[o].set(a[L]);
        } else {
            int M = MID(L, R);
            int left = o * 2;
            int right = o * 2 + 1;

            _build(left, L, M);
            _build(right, M + 1, R);

            node[o].merge(node[left], node[right]);
        }
    }

    void maintain(int o, int L, int R) {
        node[o].clear();
        if (R > L) {
            node[o].merge(node[o * 2], node[o * 2 + 1]);
        }
        node[o].minv += addv[o];
        node[o].maxv += addv[o];
        node[o].sumv += addv[o] * (R - L + 1);
    }

    void update(int o, int L, int R) {
        int left = o * 2, right = o * 2 + 1;
        if (y1 <= L && y2 >= R) {
            addv[o] += v;
        } else {
            int M = MID(L, R);
            if (y1 <= M) {
                update(left, L, M);
            }
            if (y2 > M) update(right, M + 1, R);
        }
        maintain(o, L, R);
    }

    void _query(int o, int L, int R, int add, Info &ans) {
        if (y1 <= L && y2 >= R) {
            ans.sumv += node[o].sumv + add * (R - L + 1);
            ans.minv = min(ans.minv, node[o].minv + add);
            ans.maxv = max(ans.maxv, node[o].maxv + add);
        } else {
            int M = MID(L, R);
            if (y1 <= M) {
                _query(o * 2, L, M, add + addv[o], ans);
            }
            if (y2 > M) {
                _query(o * 2 + 1, M + 1, R, add + addv[o], ans);
            }
        }
    }

    void init() { _build(1, 1, n); }

    Info query(int L, int R) {
        this->y1 = L;
        this->y2 = R;

        Info ans(-INF, INF, 0);
        _query(1, 1, n, 0, ans);

        return move(ans);
    }

    // A[L..R] += v
    void add(int L, int R, int v) {
        this->v = v;
        this->y1 = L;
        this->y2 = R;
        for (int i = L; i <= R; ++i) a[i] += v;

        update(1, 1, n);
    }
};

int main() {
    int N = 10;
    auto array = random_arr(N, 2434);
    for (auto a : array) cout << a << "\t";
    cout << endl;

    SegmentTree tree(N);
    for (int i = 0; i < N; ++i) {
        tree.a[i + 1] = array[i];
    }
    tree.init();

    for (int i = 1; i <= 25; ++i) {
        auto seg = tree.seg[i];
        if (!seg.has_value()) {
            break;
        }

        auto segv = seg.value();
        auto node = tree.node[i];
        printf("[%d:(%d,%d)]:\t", i, segv.first, segv.second);
        printf("max=%lld  min=%lld  sumv=%lld\n", node.maxv, node.minv, node.sumv);
    }

    cout << endl;
    for (int l = 1; l <= N; ++l) {
        for (int r = l + 1; r <= N; ++r) {
            auto query = tree.query(l, r);
            auto a = query.maxv, b = query.minv, c = query.sumv;
            printf("(%d,%d)=max=%lld  min=%lld  sumv=%lld\n", l, r, a, b, c);
        }
    }

    tree.add(1, 5, 999);
    cout << endl;
    for (int l = 1; l <= N; ++l) {
        for (int r = l + 1; r <= N; ++r) {
            auto query = tree.query(l, r);
            printf("(%d,%d)=max=%lld  min=%lld  sumv=%lld\n", l, r, query.maxv, query.minv,
                   query.sumv);
        }
    }

    return 0;
}
