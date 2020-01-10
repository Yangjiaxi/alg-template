#include <iostream>

using namespace std;

const int MAX_STATE = 1010;

class Trie {
  public:
    Trie() {}

    void insert(const string &str) {
        int cur = 0;
        int l   = str.size();
        for (int i = 0; i < l; ++i) {
            int tr = mapper(str.at(i));
            if (!next[cur][tr]) next[cur][tr] = ++state;
            cur = next[cur][tr];
        }
        exist[cur] = true;
    }

    bool check(const string &str, bool not_ck) {
        int cur = 0;
        int l   = str.size();
        for (int i = 0; i < l; ++i) {
            int tr = mapper(str.at(i));
            if (!next[cur][tr]) return false;
            cur = next[cur][tr];
        }
        return not_ck || exist[cur];
    }

    bool find(const string &str) { return check(str, false); }
    bool prefix(const string &str) { return check(str, true); }
    int mapper(char c) { return c - 'a'; }

  private:
    unsigned next[MAX_STATE][26];
    bool exist[MAX_STATE];
    unsigned state = 0;
};

int main() {
    Trie T;
    T.insert("apple");
    T.insert("appear");
    cout << T.find("app") << endl;
    cout << T.prefix("app") << endl;
    cout << T.find("apple") << endl;
    cout << T.find("pear") << endl;
    return 0;
}