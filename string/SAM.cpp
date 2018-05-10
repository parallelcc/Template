#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
using LD = long double;
const LL INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;

template<typename T>
class LCT {
 private:
     struct node {
         int l, r, f;
         T k, tag;
         void mod(T v) {
             k += v;
             tag += v;
         }
     };
     vector<node> tr;
     void pd(int now) {
         if (tr[tr[now].f].l == now || tr[tr[now].f].r == now) pd(tr[now].f);
         if (tr[now].tag) {
             if (tr[now].l) tr[tr[now].l].mod(tr[now].tag);
             if (tr[now].r) tr[tr[now].r].mod(tr[now].tag);
             tr[now].tag = 0;
         }
     }
     void rotate(int x) {
         int y = tr[x].f, z = tr[y].f;
         if (tr[z].l == y || tr[z].r == y) {
             if (tr[z].l == y) tr[z].l = x;
             else tr[z].r = x;
         }
         tr[x].f = z; tr[y].f = x;
         if (tr[y].l == x) {
             tr[tr[x].r].f = y;
             tr[y].l = tr[x].r;
             tr[x].r = y;
         } else {
             tr[tr[x].l].f = y;
             tr[y].r = tr[x].l;
             tr[x].l = y;
         }
     }
     void splay(int x) {
         pd(x);
         while (tr[tr[x].f].l == x || tr[tr[x].f].r == x) {
             int y = tr[x].f, z = tr[y].f;
             if (tr[z].l == y || tr[z].r == y) {
                 if (tr[z].l == y ^ tr[y].l == x) rotate(x);
                 else rotate(y);
             }
             rotate(x);
         }
     }

 public:
     node& operator[] (size_t k) { return tr[k]; }
     LCT() {}
     LCT(size_t n) { resize(n); }
     void resize(size_t n) { tr.resize(n + 1); }
     void access(int x) {
         for (int y = 0; x; y = x, x = tr[x].f) {
             splay(x), tr[x].r = y;
         }
     }
     void link(int x, int y) {
         access(y); splay(y); tr[y].mod(tr[x].k);
         tr[x].f = y;
     }
     void cut(int x) {
         access(x); splay(x); tr[tr[x].l].mod(-tr[x].k);
         tr[x].l = tr[tr[x].l].f = 0;
     }
     T que(int x) {
         splay(x); return tr[x].k;
     }
};

struct SAM {
    // LCT<int> lct;
    const static int SZ = 26;
    char a = 'a';
    struct state {
        int max, fa, go[SZ];
    };
    vector<state> st;
    int last = 1, cnt = 2;  // 0 is NULL, 1 is empty string

    SAM(int n) { st.resize(2 * n + 10); }  // lct.resize(2 * n + 10); }
    SAM(const string& s, int n) : SAM(n) { for (auto i : s) push_back(i); }
    void push_back(char ch) {
        int c = ch - a;
        int now = last;
        last = cnt++;
        // lct[last].k = 1;
        st[last] = {st[now].max + 1, 1};
        while (now && !st[now].go[c]) st[now].go[c] = last, now = st[now].fa;
        if (now) {
            int nex = st[now].go[c];
            if (st[now].max + 1 == st[nex].max) st[last].fa = nex;  // , lct.link(last, nex);
            else {
                st[cnt] = st[nex];
                st[cnt].max = st[now].max + 1;
                // lct.link(cnt, st[cnt].fa);
                st[last].fa = st[nex].fa = cnt;
                // lct.cut(nex), lct.link(last, cnt), lct.link(nex, cnt);
                while (now && st[now].go[c] == nex) st[now].go[c] = cnt, now = st[now].fa;
                cnt++;
            }
        }  // else lct.link(last, 1);
    }
    state& operator[] (size_t k) { return st[k]; }
    int match(string& s) {
        int tmp = 1;
        for (auto i : s) {
            tmp = st[tmp].go[i - a];
            if (!tmp) break;
        }
        return tmp;
    }
    vector<int> topsort() {
        int len = st[last].max + 1;
        vector<int> sum(len), res(cnt);
        for (int i = 1; i < cnt; i++) sum[st[i].max]++;
        for (int i = 1; i < len; i++) sum[i] += sum[i - 1];
        for (int i = 1; i < cnt; i++) res[sum[st[i].max]--] = i;
        return res;
    }
    // int num(int x) { return lct.que(x); }
};
