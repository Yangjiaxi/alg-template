#include <iostream>
#include <vector>

#define DEBUG

using std::cout;
using std::endl;
using std::max;
using std::min;
using std::strlen;
using std::vector;

const char ori[] = "abababc";

int main() {
    int len = strlen(ori);
    int n = len * 2 + 1;

    char str[n];
    for (int i = 0; i < len; ++i) {
        str[i << 1] = '#';
        str[(i << 1) + 1] = ori[i];
    }
    str[n - 1] = '#';

    int max_r = -1;
    vector<int> d(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        /*
            Case.1 当前元素在最大半径之外 i > r => 1
            Case.2 在内，而且
                Case.2.1 对称位置所指出的回文串没有超出右边界 => d[l + r - i]
                Case.2.2 超出了右边界 => r - i
        */
        int k = (i > r) ? 1 : min(d[l + r - i], r - i);

        while (i - k >= 0 && i + k < n && str[i - k] == str[i + k]) {
            k++;
        }
        d[i] = k--;
        max_r = max(max_r, d[i] / 2);

        // 每次都要维护最大边界
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
#ifdef DEBUG
    for (int i = 0; i < n; ++i) {
        cout << d[i] << " ";
    }
    cout << endl;
#endif

    cout << "Max: " << max_r << endl;
    return 0;
}