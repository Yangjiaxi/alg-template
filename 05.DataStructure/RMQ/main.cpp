#include "utils.h"
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1005;

int d[MAXN][MAXN];

/*
    d[i][j]:
        从i开始，长度为2^j的一段元素中的最小值

    因此具有递推关系：
        d[i][j] = min(d[i][j-1], d[i+2^{j-1}][j-1])
*/
void RMQ_init(const vector<int> &A) {
    int n = A.size();
    for (int i = 0; i < n; ++i) d[i][0] = A[i];
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 0; i + (1 << j) - 1 < n; ++i) {
            d[i][j] = min(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int RMQ(size_t L, size_t R) {
    int k = 0;
    while (1 << (k + 1) <= R - L + 1) ++k;
    return min(d[L][k], d[R - (1 << k) + 1][k]);
}

int main() {
    const int N = 10;
    // vector<int> A = array_init(N);
    vector<int> A{40, 64, 11, 52, 77, 83, 13, 29, 56, 79};

    RMQ_init(A);

    for (int i = 0; i < N; ++i) {
        for (int j = 1; (1 << j) <= N; ++j) printf("d[%d][%d]=%d\t", i, j, d[i][j]);
        cout << endl;
    }

    output_array(A, true);

    for (int L = 0; L < N; ++L) {
        for (int R = L + 1; R < N; ++R) printf("[%d,%d]=%d\t", L, R, RMQ(L, R));
        cout << endl;
    }

    return 0;
}