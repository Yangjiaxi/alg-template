#include <algorithm>
#include <iostream>

// #define DEBUG

using std::cout;
using std::endl;
using std::memcpy;
using std::sort;
using std::string;

/*
    优化后的倍增法求后缀数组
*/

void print(const int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << "\t";
    }
    cout << "\n";
    cout.flush();
}

void debug(const int *arr, int n) {
#ifdef DEBUG
    print(arr, n);
#endif
}

const int MAXN = 1010;
// rx[i]: 缓存rank[id[i]]
int sa[MAXN], rank[MAXN << 1], bk_rank[MAXN << 1], id[MAXN], cnt[MAXN], rx[MAXN];

const string str = "aabaaaab";

int main() {
    int n  = str.size();
    int m  = std::max(n, 300); // 基数排序值域
    int rk = m;

    // 第一遍基数排序
    for (int i = 1; i <= n; ++i) ++cnt[rank[i] = str[i - 1]];
    for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; --i) sa[cnt[rank[i]]--] = i;

    for (int w = 1; w < n; w <<= 1, m = rk) {
        // 关键字2不再需要排序
        rk = 0;
        for (int i = n; i > n - w; --i) id[++rk] = i;
        for (int i = 1; i <= n; ++i) {
            if (sa[i] > w) id[++rk] = sa[i] - w;
        }

        memset(cnt, 0, sizeof(cnt));
        // 对关键字1进行计数排序
        for (int i = 1; i <= n; ++i) ++cnt[rx[i] = rank[id[i]]];
        for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; --i) sa[cnt[rx[i]]--] = id[i];

        memcpy(bk_rank, rank, sizeof(rank));
        for (int rk = 0, i = 1; i <= n; ++i) {
            int p = sa[i];
            int q = sa[i - 1];
            if (bk_rank[p] == bk_rank[q] && bk_rank[p + w] == bk_rank[q + w]) {
                rank[p] = rk;
            } else {
                rank[p] = ++rk;
            }
        }
        debug(rank + 1, n);
    }

    cout << "Rank: " << endl;
    print(rank + 1, n);
    cout << "Suffix Array: " << endl;
    print(sa + 1, n);

    return 0;
}