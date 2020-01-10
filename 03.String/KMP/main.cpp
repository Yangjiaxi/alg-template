#include <iostream>
#include <vector>

using namespace std;

vector<int> kmp_pre(const string &s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return move(pi);
}

vector<int> kmp_pos(const string &pattern, const string &text) {
    auto next = kmp_pre(pattern);
    vector<int> pos;

    int n = text.size();
    int m = pattern.size();

    for (int i = 0, j = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) j = next[j - 1];
        if (text[i] == pattern[j]) ++j;
        if (j == m) {
            pos.push_back(i + 1 - m);
            j = next[j - 1];
        }
    }
    return move(pos);
}

int main() {
    const string pattern = "ababaca";
    const string text    = "bacbababadababacambabacaddababacasdsd";

    auto pos = kmp_pos(pattern, text);

    int n = text.size();

    for (int i = 0; i < n; ++i) cout << i << (i < 10 ? "  " : " ");
    cout << endl;

    for (auto c : text) cout << c << "  ";
    cout << endl;

    for (auto c : pos) cout << c << "\n";
    cout << endl;

    return 0;
}