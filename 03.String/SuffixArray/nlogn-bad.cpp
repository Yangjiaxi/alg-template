#include <algorithm>
#include <iostream>

// #define DEBUG

using std::cout;
using std::endl;
using std::memcpy;
using std::sort;
using std::string;

/*
    计算后缀数组：
        rank[i]
          sa[i]
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
int sa[MAXN], rank[MAXN << 1], bk_rank[MAXN << 1], id[MAXN], cnt[MAXN];

const string str = "aabaaaab";

int main() {
    int n = str.size();
    int m = std::max(n, 300); // 基数排序值域

    // 第一遍基数排序
    for (int i = 1; i <= n; ++i) ++cnt[rank[i] = str[i - 1]];
    for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; --i) sa[cnt[rank[i]]--] = i;

    for (int w = 1; w < n; w <<= 1) {
        memset(cnt, 0, sizeof(cnt));
        // 对关键字2进行计数排序
        for (int i = 1; i <= n; ++i) id[i] = sa[i];
        for (int i = 1; i <= n; ++i) ++cnt[rank[id[i] + w]];
        for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; --i) sa[cnt[rank[id[i] + w]]--] = id[i];

        memset(cnt, 0, sizeof(cnt));
        // 对关键字1进行计数排序
        for (int i = 1; i <= n; ++i) id[i] = sa[i];
        for (int i = 1; i <= n; ++i) ++cnt[rank[id[i]]];
        for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; --i) sa[cnt[rank[id[i]]]--] = id[i];

        memcpy(bk_rank, rank, sizeof(rank));
        for (int rk = 0, i = 1; i <= n; ++i) {
            if (bk_rank[sa[i]] == bk_rank[sa[i - 1]] &&
                bk_rank[sa[i] + w] == bk_rank[sa[i - 1] + w]) {
                rank[sa[i]] = rk;
            } else {
                rank[sa[i]] = ++rk;
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