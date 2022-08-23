#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

constexpr int MAXN = 1010;
constexpr int MAX_LEN = 10;
constexpr int MAX_STATE = MAXN * MAX_LEN;
constexpr int CHAR_SET = 26;

class AC {
  public:
    AC() : idx_str() { init(); }

    void insert(const string &s) {
        int n = s.size();
        int now = root;
        for (int i = 0; i < n; ++i) {
            int c = into(s.at(i));
            if (next[now][c] == -1) {
                next[now][c] = new_node();
            }
            now = next[now][c];
        }
        idx_str.insert({now, s});
        ++exist[now];
    }

    void build() {
        queue<int> Q;

        // 如果查到了root还没能跳转，那就跳到root
        fail[root] = root;
        for (int i = 0; i < CHAR_SET; ++i) {
            if (next[root][i] == -1) {
                // 读入了无法引起跳转的字符
                next[root][i] = root;
            } else {
                // fail的直接后裔，失配了就直接跳回来
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }
        }

        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            for (int i = 0; i < CHAR_SET; ++i) {
                if (next[now][i] == -1) {
                    // 无边时需要失配跳转
                    next[now][i] = next[fail[now]][i];
                } else {
                    // 有边时根据匹配的最长前缀 的跳转(当前状态的某个后缀对应的前缀的跳转) 进行 跳转

                    // 注意fail[next[now][i]]，这意味着对于now，now之后的节点的fail指针在这里被处理
                    // 这句代码意味着，如果now的某个后裔失配，则根据now的失配后的跳转进行跳转
                    // 同时，也利用了路径压缩的思想，否则，在失配的时候就需要while来找到匹配的下一个状态
                    fail[next[now][i]] = next[fail[now]][i];
                    // BFS
                    Q.push(next[now][i]);
                }
            }
        }
    }

    pair<int, unordered_map<string, vector<int>>> query(const string &s) {
        int cnt = 0;
        int n = s.size();
        int now = root;
        unordered_map<string, vector<int>> pos;

        for (int i = 0; i < n; ++i) {
            now = next[now][into(s.at(i))];
            int tmp = now;
            while (tmp != root) {
                if (exist[tmp]) {
                    ++cnt;
                    auto s = idx_str.at(tmp);
                    int ls = s.size();
                    auto it = pos.find(s);
                    if (it != pos.end())
                        it->second.push_back(i - ls + 1);
                    else
                        pos.insert({s, {i - ls + 1}});
                }
                tmp = fail[tmp];
            }
        }
        return move(make_pair(cnt, pos));
    }

    void debug() {
        for (int i = 0; i < L; ++i) {
            printf("id=%3d, fail=%3d, exist=%3d, tr=[", i, fail[i], exist[i]);
            for (int j = 0; j < CHAR_SET; ++j) {
                if (next[i][j] > root) printf("%c[%d], ", (j + 'a'), next[i][j]);
            };
            printf("]");
        }
    }

  private:
    int new_node() {
        for (int i = 0; i < CHAR_SET; ++i) next[L][i] = -1;
        exist[L++] = 0;
        return L - 1;
    }

    void init() {
        L = 0;
        root = new_node();
    }

    int into(char c) { return c - 'a'; }

  private:
    int next[MAX_STATE][CHAR_SET];
    int fail[MAX_STATE];
    int exist[MAX_STATE];
    unordered_map<int, string> idx_str;
    int root;
    int L;
};

int main() {
    vector<string> dict = {"i", "he", "his", "she", "hers"};
    const string text = "ushersheishis";

    AC ac;
    for (auto &s : dict) ac.insert(s);
    ac.build();

    auto [cnt, pos] = ac.query(text);
    cout << "Total: " << cnt << endl;

    int n = text.size();
    for (int i = 0; i < n; ++i) cout << i << (i < 10 ? "  " : " ");
    cout << endl;
    for (auto c : text) cout << c << "  ";
    cout << endl;

    for (auto &[k, v] : pos) {
        cout << k << " : [";
        for (auto p : v) cout << p << " ";
        cout << "]" << endl;
    }
    return 0;
}