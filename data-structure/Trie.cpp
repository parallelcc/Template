#include <bits/stdc++.h>
using namespace std;

struct node {
    int l, r, num;
};

const int N = 100005;
node tr[33 * N];
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

template <typename T, class tag = null_tag>
class Trie : public tag {
    using tag::tag;
    using tag::getr;
    using tag::setr;
    using tag::copy;
 private:
     int newnode() { tr[cur].l = tr[cur].r = tr[cur].num = 0; return cur++; }
     static int join(int u, int v) {
         if (!u) return v;
         if (!v) return u;
         u = copy(u);
         tr[u].num += tr[v].num;
         tr[u].l = join(tr[u].l, tr[v].l);
         tr[u].r = join(tr[u].r, tr[v].r);
         return u;
     }

 public:
     Trie() {}
     Trie& join(Trie& x) { setr(join(getr(), x.getr())); x.setr(0); return *this; }
     Trie& join(Trie&& x) { setr(join(getr(), x.getr())); return *this; }
     size_t size() { return tr[getr()].num; }
     bool empty() { return size() == 0; }
     void insert(T v) {
         int x = copy(getr()); setr(x);
         for (int i = (sizeof(T) << 3) - 1; i >= 0; i--) {
             tr[x].num++;
             if (v >> i & 1) {
                 if (!tr[x].r) tr[x].r = newnode();
                 else tr[x].r = copy(tr[x].r);
                 x = tr[x].r;
             } else {
                 if (!tr[x].l) tr[x].l = newnode();
                 else tr[x].l = copy(tr[x].l);
                 x = tr[x].l;
             }
         }
         tr[x].num++;
     }
     bool erase(T v) {
         // if (!find(v)) return false;
         int x = copy(getr()); setr(x);
         for (int i = (sizeof(T) << 3) - 1; i >= 0; i--) {
             tr[x].num--;
             if (v >> i & 1) x = tr[x].r = copy(tr[x].r);
             else x = tr[x].l = copy(tr[x].l);
         }
         tr[x].num--;
         return true;
     }
     bool find(T v) {
         int x = getr();
         for (int i = (sizeof(T) << 3) - 1; i >= 0; i--) {
             if (v >> i & 1) x = tr[x].r;
             else x = tr[x].l;
             if (!tr[x].num) return false;
         }
         return true;
     }
     T Max(T v = 0) {
         if (empty()) return v;
         int x = getr();
         for (int i = (sizeof(T) << 3) - 1; i >= 0; i--) {
             if (v >> i & 1) {
                 if (tr[tr[x].l].num) x = tr[x].l;
                 else x = tr[x].r, v ^= T(1) << i;
             } else {
                 if (tr[tr[x].r].num) x = tr[x].r, v ^= T(1) << i;
                 else x = tr[x].l;
             }
         }
         return v;
     }
     T Min(T v = 0) {
         if (empty()) return v;
         int x = getr();
         for (int i = (sizeof(T) << 3) - 1; i >= 0; i--) {
             if (v >> i & 1) {
                 if (tr[tr[x].r].num) x = tr[x].r, v ^= T(1) << i;
                 else x = tr[x].l;
             } else {
                 if (tr[tr[x].l].num) x = tr[x].l;
                 else x = tr[x].r, v ^= T(1) << i;
             }
         }
         return v;
     }
     T find_by_order(int k) {
         if (empty()) return -1;
         k = min(k, size() - 1);
         int x = getr(); T v = 0;
         for (int i = (sizeof(T) << 3) - 1; i >= 0; i--) {
             if (tr[tr[x].l].num > k) x = tr[x].l;
             else k -= tr[tr[x].l].num, x = tr[x].r, v ^= T(1) << i;
         }
         return v;
     }
     int order_of_key(T v) {
         int x = getr(), k = 0;
         for (int i = (sizeof(T) << 3) - 1; i >= 0; i--) {
             if (v >> i & 1) k += tr[tr[x].l].num, x = tr[x].r;
             else x = tr[x].l;
         }
         return k;
     }
};

template <typename T>
class PerTrie : public Trie<T, pers_tag> {
    using Trie<T, pers_tag>::Trie;
    using Trie<T, pers_tag>::root;
 public:
    T Max(int L, int R, T v = 0) {
        if (L >= R || R >= root.size()) return v;
        L = root[L], R = root[R];
        if (!(tr[R].num - tr[L].num)) return v;
        for (int i = (sizeof(T) << 3) - 1; i >= 0; i--) {
            if (v >> i & 1) {
                if (tr[tr[R].l].num - tr[tr[L].l].num) L = tr[L].l, R = tr[R].l;
                else L = tr[L].r, R = tr[R].r, v ^= T(1) << i;
            } else {
                if (tr[tr[R].r].num - tr[tr[L].r].num) L = tr[L].r, R = tr[R].r, v ^= T(1) << i;
                else L = tr[L].l, R = tr[R].l;
            }
        }
        return v;
    }
    T Min(int L, int R, T v = 0) {
        if (L >= R || R >= root.size()) return v;
        L = root[L], R = root[R];
        if (!(tr[R].num - tr[L].num)) return v;
        for (int i = (sizeof(T) << 3) - 1; i >= 0; i--) {
            if (v >> i & 1) {
                if (tr[tr[R].r].num - tr[tr[L].r].num) L = tr[L].r, R = tr[R].r, v ^= T(1) << i;
                else L = tr[L].l, R = tr[R].l;
            } else {
                if (tr[tr[R].l].num - tr[tr[L].l].num) L = tr[L].l, R = tr[R].l;
                else L = tr[L].r, R = tr[R].r, v ^= T(1) << i;
            }
        }
        return v;
    }
    T find_by_order(int L, int R, int k) {
        if (L >= R || R >= root.size()) return -1;
        L = root[L], R = root[R];
        if (!(tr[R].num - tr[L].num)) return -1;
        k = min(k, tr[R].num - tr[L].num - 1);
        T v = 0;
        for (int i = (sizeof(T) << 3) - 1; i >= 0; i--) {
            if (tr[tr[R].l].num - tr[tr[L].l].num > k) L = tr[L].l, R = tr[R].l;
            else k -= tr[tr[R].l].num - tr[tr[L].l].num, L = tr[L].r, R = tr[R].r, v ^= T(1) << i;
        }
        return v;
    }
    int order_of_key(int L, int R, T v) {
        if (L >= R || R >= root.size()) return -1;
        L = root[L], R = root[R];
        int k = 0;
        for (int i = (sizeof(T) << 3) - 1; i >= 0; i--) {
            if (v >> i & 1) k += tr[tr[R].l].num - tr[tr[L].l].num, L = tr[L].r, R = tr[R].r;
            else L = tr[L].l, R = tr[R].l;
        }
        return k;
    }
};
// cur = 1;
