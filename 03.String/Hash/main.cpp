#include <fstream>
#include <iostream>
#include <vector>

// #define DEBUG

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

using ull = unsigned long long;

/*
    题目描述：
        给出一字符串与n个查询，
        每个查询为[l, r]区间，
        返回每个区间不重复的子串个数
*/

const int SEED = 13331;
const int HASH = 10007;

struct HashMap {
  public:
    HashMap(int n) : size(0) {
        f = new int(n);
        next = new int(n);
        head = new int(HASH);
        state = new (unsigned long long)(n);
        memset(head, -1, sizeof(int) * HASH);
    }

    int insert(ull val, int id) {
        int hit = val % HASH;
        for (int i = head[hit]; i != -1; i = next[i]) {
            if (val == state[i]) {
                int tmp = f[i];
                f[i] = id;
                return tmp;
            }
        }
        f[size] = id;
        state[size] = val;
        next[size] = head[hit];
        head[hit] = size++;
        return 0;
    }

  private:
    int size;
    int *head, *next, *f;
    ull *state;
};

int main() {
    ifstream fin("in.txt");
    string str;
    fin >> str;
    int sz = str.size();

    ull P[sz + 1], S[sz + 1];
    int ans[sz + 2][sz + 1];

    P[0] = 1;
    S[0] = 0;
    for (int i = 1; i <= sz; ++i) {
        P[i] = P[i - 1] * SEED;
        S[i] = S[i - 1] * SEED + str[i - 1];
    }

    memset(ans, 0, sizeof(ans));

    HashMap H(sz);
    for (int L = 1; L <= sz; ++L) {
        for (int i = 1; i + L - 1 <= sz; ++i) {
            int l = H.insert(S[i + L - 1] - S[i - 1] * P[L], i);
            ++ans[i][i + L - 1];
            --ans[l][i + L - 1];
        }
    }

    for (int i = sz; i >= 0; --i) {
        for (int j = i; j <= sz; ++j) {
            ans[i][j] += ans[i + 1][j] + ans[i][j - 1] - ans[i + 1][j - 1];
        }
    }

#ifdef DEBUG
    for (int i = 0; i <= sz; ++i) {
        for (int j = 0; j <= sz; ++j) {
            cout << ans[i][j] << "\t";
        }
        cout << "\n";
    }
#endif

    int n, l, r;
    fin >> n;
    while (n--) {
        fin >> l >> r;
        cout << ans[l][r] << endl;
    }

    return 0;
}