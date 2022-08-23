#include <iostream>
#include <vector>

using namespace std;

vector<int> ekmp_pre(const string &s) {
    int n = s.size();
    vector<int> z(n);

    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        int k = z[i];

        if (i <= r) k = min(r - i + 1, z[i - l]);
        while (i + k < n && s[k] == s[i + k]) ++k;

        if (i + k - 1 > r) l = i, r = i + k - 1;
        z[i] = k;
    }
    return move(z);
}

vector<int> ekmp(const string &pattern, const string &text) {
    int m = pattern.size();
    auto combz = ekmp_pre(pattern + text);

    vector<int> pos;
    for (int i = m; i < combz.size(); ++i) {
        if (combz[i] >= m) pos.push_back(i - m);
    }
    return pos;
}

int main() {
    const string pattern = "ababaca";
    const string text = "bacbababadababacambabacaddababacasdsd";

    // auto zs = ekmp_pre("aaabaab");
    // for (auto &z : zs) cout << z << " ";
    // cout << endl;

    auto pos = ekmp(pattern, text);
    for (auto &z : pos) cout << z << " ";
    cout << endl;
    return 0;
}