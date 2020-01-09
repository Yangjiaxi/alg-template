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

const string str = "heheda";

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

int main() {
    int n = str.size();
    int sa[n + 1];
    int rank[n + 1];
    int bk_rank[n + 1];

    sa[0] = rank[0] = bk_rank[0] = 0;

    // 第一次rank
    for (int i = 1; i <= n; ++i) rank[i] = str[i - 1];

    for (int w = 1; w < n; w <<= 1) {
        // 初始化sa
        for (int i = 1; i <= n; ++i) sa[i] = i;
        // step-1 利用rank排序sa
        sort(sa + 1, sa + n + 1, [&](int x, int y) {
            int a = (x + w > n) ? 0 : rank[x + w];
            int b = (y + w > n) ? 0 : rank[y + w];
            return rank[x] == rank[y] ? a < b : rank[x] < rank[y];
        });
        debug(sa, n + 1);
        memcpy(bk_rank, rank, sizeof(rank));
        // step-2 利用sa计算rank，主要利用反函数性质
        for (int i = 1, rk = 0; i <= n; ++i) {
            int p = sa[i];
            int q = sa[i - 1];
            int a = (p + w > n) ? 0 : bk_rank[p + w];
            int b = (q + w > n) ? 0 : bk_rank[q + w];
            if (bk_rank[p] == bk_rank[q] && a == b) {
                rank[p] = rk; // 值相同的，排位相同
            } else {
                rank[p] = ++rk; // 与前一位值不同，排位后移
            }
        }
        debug(rank, n + 1);
    }
    cout << "Rank: " << endl;
    print(rank + 1, n);
    cout << "Suffix Array: " << endl;
    print(sa + 1, n);
    return 0;
}