#include <iostream>

using namespace std;

constexpr int CHAR_SET = 26;

class Node {
  public:
    Node(int id, int max = 0) : link(nullptr), max(max), id(id) {}

    int get_min() {
        if (link) return link->max + 1;
        return -1;
    }

    int get_max() { return max; }

    int get_link() {
        if (link) return link->id;
        return -1;
    }

    char get_minimal_next() {
        for (char i = 0; i < CHAR_SET; ++i) {
            if (ch[i]) return i;
        }
        return 0;
    }

    Node *ch[CHAR_SET]; // 转移表
    Node *link;         // 后缀连接
    int id;             // debug
    int max;
};

class SuffixAutomaton {
  public:
    SuffixAutomaton() {}

    void init() { start = last = new_node(); }

    Node *new_node(int max = 0) {
        auto tmp = new Node(cnt++, max);
        return tmp;
    }

    Node *extend(char ch) {
        int c   = into(ch);
        Node *u = new_node(last->max + 1);
        Node *v = last;

        // last引起的后缀连接路径上没有出边c的节点v全都连向u
        while (v && !v->ch[c]) {
            v->ch[c] = u;
            v        = v->link;
        }

        if (!v) {
            // v跳进了null，这意味着到了树根
            u->link = start;
        } else if (v->ch[c]->max == v->max + 1) {
            // 将要转移到的状态为q = v->ch[c]
            // case.1 q.max == p.max + 1
            u->link = v->ch[c];
        } else {
            // case.2 q.max != p.max + 1
            Node *clone = new_node(v->max + 1);
            Node *old   = v->ch[c];

            // 节点拷贝
            std::copy(old->ch, old->ch + CHAR_SET, clone->ch);
            clone->link = old->link;

            old->link = u->link = clone;

            // 只要存在一条由c引起的后缀连接节点的转移，就重定向到clone
            while (v && v->ch[c] == old) {
                v->ch[c] = clone;
                v        = v->link;
            }
        }
        // 都要更新last
        last = u;
        return u;
    }

    int into(char ch) { return ch - 'a'; }

    void dfs(Node *cur, const string &ident = "") {
        cout << ident << cur->id << " Min: " << cur->get_min() << " Max: " << cur->get_max()
             << " Link: " << cur->get_link() << endl;
        for (char i = 0; i < CHAR_SET; ++i) {
            if (cur->ch[i]) {
                cout << ident << ":`" << (char)('a' + i) << "` -> " << endl;
                dfs(cur->ch[i], ident + '\t');
            }
        }
    }
    void debug() { dfs(start); }

    int cnt = 0;
    Node *start;
    Node *last;
};

// 本质不同子串
void cnt_substrs(SuffixAutomaton &sam, const string &s) {
    sam.init();
    int ans   = 0;
    int len   = 0;
    auto calc = [](int a) { return a * (a + 1) / 2; };
    for (char c : s) {
        Node *now    = sam.extend(c);
        int now_max  = now->get_max();
        int link_max = now->get_min() - 1;
        ans += now_max - link_max;
        len += calc(now_max) - calc(link_max);
    }
    cout << "Total: " << ans << endl;
    cout << "Length of all: " << len << endl;
    cout << endl;
}

// 字符串最小表示（循环移位字典序最小）
void minimal_str(SuffixAutomaton &sam, const string &s) {
    sam.init();
    for (char c : s + s) sam.extend(c);

    int n     = s.size();
    Node *cur = sam.start;

    cout << "Min(`" << s << "`) = `";
    for (int i = 0; i < n; ++i) {
        char c = cur->get_minimal_next();
        cout << (char)(c + 'a');
        cur = cur->ch[c];
    }
    cout << "`" << endl;
}

int main() {
    SuffixAutomaton sam;

    // 1. 求本质不同子串数量与子串总长度
    // aba -> a b ab ba aba 5 9
    // abbaa -> a b ab bb ba aa abb bba baa abba bbaa abbaa 12 32
    cnt_substrs(sam, "abbaa");
    // sam.debug();

    // 2. 求字符串的最小表示
    minimal_str(sam, "abbaa"); // aaabb

    return 0;
}