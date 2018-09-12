#include <bits/stdc++.h>
using namespace std;

const int TB = 26;
const char init = 'a';

using sz = uint32_t;

struct node {
    sz size, num;
    int nxt[TB];
};

const int N = 1000005;
node tr[N];
int cur = 1;

class null_tag { 
 protected:
     int root = 0;
     inline int getr() { return root; } 
     inline void setr(int x) { root = x; }
     inline int copy(int x) { return x; }
};

class pers_tag {
 protected:
     vector<int> root;
     int tim = 0;
     inline int getr() { return root[tim]; }
     inline void setr(int x) { tim = root.size(); root.push_back(x); }
     inline int copy(int x) { tr[cur] = tr[x]; return cur++; }

 public:
     pers_tag() { setr(0); }
     explicit pers_tag(int n) { root.reserve(n); setr(0); }
     inline void back(int x) { if (x >= root.size()) return; tim = x; }
};

template <class tag = null_tag>
class Trie : public tag {
    using tag::tag;
    using tag::getr;
    using tag::setr;
    using tag::copy;
 private:
    int newnode() {
        memset(tr[cur].nxt, 0, sizeof(tr[cur].nxt)); // if single case, don't need
        tr[cur].size = tr[cur].num = 0; return cur++;
    }
    int join(int u, int v) {
        if (!u) return v;
        if (!v) return u;
        u = copy(u);
        tr[u].num += tr[v].num; tr[u].size = tr[u].num;
        for (int i = 0; i < TB; i++) {
            tr[u].nxt[i] = join(tr[u].nxt[i], tr[v].nxt[i]);
            tr[u].size += tr[tr[u].nxt[i]].size;
        }
        return u;
    }
    void do_erase(string& s, sz num) {
        int x = copy(getr()); setr(x);
        for (auto i : s) {
            tr[x].size -= num;
            x = tr[x].nxt[i - init] = copy(tr[x].nxt[i - init]);
        }
        tr[x].size -= num; tr[x].num -= num;
    }

 public:
    Trie() {}
    Trie& join(Trie& x) { setr(join(getr(), x.getr())); x.setr(0); return *this; }
    Trie& join(Trie&& x) { setr(join(getr(), x.getr())); return *this; }
    sz size() { return tr[getr()].size; }
    bool empty() { return size() == 0; }
    void insert(string& s, sz num = 1) {
        int r = getr(), x;
        if (!r) x = newnode();
        else x = copy(r);
        setr(x);
        for (auto i : s) {
            tr[x].size += num;
            int& y = tr[x].nxt[i - init];
            if (!y) y = newnode();
            else y = copy(y);
            x = y;
        }
        tr[x].num += num; tr[x].size += num;
    }
    bool erase(string& s, sz num = 1) { num = min(num, find(s)); if (num > 0) { do_erase(s, num); return true; } else return false; }
    bool erase_all(string& s) { sz num = find(s); if (num > 0) { do_erase(s, num); return true; } else return false; }
    bool erase_pre(string& s) {
        sz num = find_pre(s);
        if (num) {
            int x = copy(getr()); setr(x);
            for (int i = 0; i < (int)s.length() - 1; i++) {
                tr[x].size -= num;
                x = tr[x].nxt[s[i] - init] = copy(tr[x].nxt[s[i] - init]);
            }
            tr[x].size -= num; tr[x].nxt[s.back() - init] = 0;
            return true;
        }
        return false;
    }
    sz find(string& s) {
        if (empty()) return 0;
        int x = getr();
        for (auto i : s) {
            x = tr[x].nxt[i - init];
            if (!tr[x].size) return 0;
        }
        return tr[x].num;
    }
    sz find_pre(string& s) {
        if (empty()) return 0;
        int x = getr();
        for (auto i : s) {
            x = tr[x].nxt[i - init];
            if (!tr[x].size) return 0;
        }
        return tr[x].size;
    }
};
// cur = 1;
