#include "utils.h"
#include <iostream>
#include <vector>

using namespace std;

/*
    线段树: 点修改
    Update(x, v): 修改A[x] 为 v
    Query(L, R):  计算min(A[L..R]) / max(A[L...R]) / sum(A[L..R])
*/

const int MAXN = 1005;
const int INF = 0x3f3f3f3f;
using LL = long long int;

struct Info {
    LL maxv;
    LL minv;
    LL sumv;
    Info() : maxv(0), minv(0), sumv(0) {}
    Info(LL maxv, LL minv, LL sumv) : maxv(maxv), minv(minv), sumv(sumv) {}
    void set(LL n) { this->maxv = this->minv = this->sumv = n; }
    void update(Info &other) {
        this->maxv = max(this->maxv, other.maxv);
        this->minv = min(this->minv, other.minv);
        this->sumv += other.sumv;
    }
};

struct SegmentTree {
    using Interval = optional<pair<int, int>>;

    int ql, qr;
    int p, v;
    int n;

    LL a[MAXN];
    Info node[MAXN * 4];
    Interval seg[MAXN * 4];

    SegmentTree(int n) : seg(), node() { this->n = n; }

    void _build(int o, int L, int R) {
        seg[o] = make_pair(L, R);
        if (L == R) {
            node[o].set(a[L]);
        } else {
            int M = L + (R - L) / 2; // 中点，分为两树
            int left = o * 2;
            int right = o * 2 + 1;

            _build(left, L, M);
            _build(right, M + 1, R);

            node[o].minv = min(node[left].minv, node[right].minv);
            node[o].maxv = max(node[left].maxv, node[right].maxv);
            node[o].sumv = node[left].sumv + node[right].sumv;
        }
    }

    Info _query(int o, int L, int R) {
        // 所查询包含于区间
        if (ql <= L && R <= qr) {
            return node[o];
        }

        int M = L + (R - L) / 2;
        Info ans(-INF, INF, 0); // max, min, sum
        if (ql <= M) {
            auto left = _query(o * 2, L, M);
            ans.update(left);
        }
        if (M < qr) {
            auto right = _query(o * 2 + 1, M + 1, R);
            ans.update(right);
        }
        return ans;
    }

    void _update(int o, int L, int R) {
        if (L == R) {
            node[o].set(a[L]);
        } else {
            int M = L + (R - L) / 2;
            int left = o * 2;
            int right = o * 2 + 1;

            if (p <= M) {
                _update(left, L, M);
            } else {
                _update(right, M + 1, R);
            }

            node[o].minv = min(node[left].minv, node[right].minv);
            node[o].maxv = max(node[left].maxv, node[right].maxv);
            node[o].sumv = node[left].sumv + node[right].sumv;
        }
    }

    void init() { _build(1, 1, n); }

    // min(A[L..R])
    Info query(int l, int r) {
        this->ql = l;
        this->qr = r;
        return _query(1, 1, n);
    }

    // A[x] = v
    void update(int p, int v) {
        this->p = p;
        this->v = v;
        a[p] = v;
        _update(1, 1, n);
    }
};

int main() {
    int N = 10;
    auto array = random_arr(N, 2434);
    for (auto a : array)
        cout << a << "\t";
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
            printf("(%d,%d)=max=%lld  min=%lld  sumv=%lld\n", l, r, query.maxv, query.minv,
                   query.sumv);
        }
    }

    tree.update(5, 999);
    tree.update(6, 1);
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
