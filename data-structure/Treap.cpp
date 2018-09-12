#include <bits/stdc++.h>
using namespace std;
using T = int;
const T INF = 0x3f3f3f3f;

struct node {
    int l, r, size;  // f
    uint32_t v; T k;  // m = INF;
    int rev;
    void mod() {
        swap(l, r);
        rev ^= 1;
    }
};
mt19937 rd(time(0));
const int N = 1e5;
node tr[N + 233];  // !!! 0
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

class Treap : public null_tag {
    // using pers_tag::pers_tag;
 protected:
    int newnode(T k, uint32_t v = rd()) { 
        tr[cur].k = k, tr[cur].size = 1, tr[cur].v = v, tr[cur].l = tr[cur].r = 0; 
        tr[cur].rev = 0;  // tr[cur].f = 0; tr[cur].m = INF;
        return cur++;
    }
    virtual void pd(int now) {}
    virtual void pu(int now) { tr[now].size = 1 + tr[tr[now].l].size + tr[tr[now].r].size; }
    // if join after split, needn't copy
    int join(int A, int B) {
        if (!A) return B; if (!B) return A;
        if (tr[A].v < tr[B].v) {
            A = copy(A); pd(A); tr[A].r = join(tr[A].r, B); pu(A); return A;
        } else {
            B = copy(B); pd(B); tr[B].l = join(A, tr[B].l); pu(B); return B;
        }
    }
    pair<int, int> split_by_order(int x, int k) {
        if (!x) return {0, 0};
        pair<int, int> y; 
        x = copy(x); pd(x);
        if (tr[tr[x].l].size >= k) {
            y = split_by_order(tr[x].l, k);
            tr[x].l = y.second; pu(x); y.second = x;
        } else {
            y = split_by_order(tr[x].r, k - tr[tr[x].l].size - 1);
            tr[x].r = y.first; pu(x); y.first = x;
        }
        return y;
    }

 public:
    Treap() {}
    size_t size() { return tr[getr()].size; }
    void build(vector<T>& a) {
        stack<int, vector<int>> s;
        for (auto i : a) {
            int x = newnode(i);
            while (!s.empty() && tr[s.top()].v > tr[x].v) pu(s.top()), s.pop();
            if (s.empty()) tr[x].l = getr(), setr(x);
            else tr[x].l = tr[s.top()].r, tr[s.top()].r = x;
            s.push(x);
        }
        while (!s.empty()) pu(s.top()), s.pop();
    }
    T find_by_order(int k) {
        int x = getr();
        while (tr[tr[x].l].size != k) {
            pd(x);
            if (tr[tr[x].l].size > k) x = tr[x].l;
            else { k -= tr[tr[x].l].size + 1; x = tr[x].r; }
        }
        return tr[x].k;
    }
    void show() {
        int f = 0;
        function<void(int)> dfs = [&](int now) {
            pd(now);
            if (tr[now].l) dfs(tr[now].l);
            if (f) cout << ' '; else f = 1; cout << tr[now].k;
            if (tr[now].r) dfs(tr[now].r);
        };
        dfs(getr());
    }
};

// change need pu
class BstTrp : public Treap {
    using Treap::Treap;
    using Treap::join;
    using Treap::split_by_order;
 private:
    pair<int, int> split_by_key(int x, T k) {
        if (!x) return {0, 0};
        pair<int, int> y;
        x = copy(x);
        if (k <= tr[x].k) { 
            y = split_by_key(tr[x].l, k); 
            tr[x].l = y.second; pu(x); y.second = x;
        } else {
            y = split_by_key(tr[x].r, k);
            tr[x].r = y.first; pu(x); y.first = x;
        }
        return y;
    }
    int insert(int &x, T k, uint32_t v) {
        int y;
        if (!x || tr[x].v > v) {
            y = newnode(k, v);
            tie(tr[y].l, tr[y].r) = split_by_key(x, tr[y].k); x = y;
        } else {
            x = copy(x);
            if (k < tr[x].k) y = insert(tr[x].l, k, v);
            else y = insert(tr[x].r, k, v);
        }
        pu(x); return y;
    }
    int erase(int &x, T k) {
        if (!x) return 0;
        int res = x;
        if (tr[x].k == k) { x = join(tr[x].l, tr[x].r); if (x) pu(x); }
        else {
            x = copy(x);
            if (k < tr[x].k) res = erase(tr[x].l, k);
            else res = erase(tr[x].r, k); 
            if (res) pu(x);
        }
        return res;
    }

 public:
    BstTrp() {}
    BstTrp& join(int x) { setr(join(getr(), x)); return *this; }
    BstTrp& join(BstTrp& x) { setr(join(getr(), x.getr())); x.setr(0); return *this; }
    BstTrp& join(BstTrp&& x) { setr(join(getr(), x.getr())); return *this; }
    BstTrp& split_by_order(int k) { setr(split_by_order(getr(), k).first); return *this; }
    BstTrp& split_by_order(int k, BstTrp& x) { auto r = split_by_order(getr(), k); setr(r.first); x.setr(r.second); return *this;}
    BstTrp& split_by_key(T k) { setr(split_by_key(getr(), k).first); return *this; }
    BstTrp& split_by_key(T k, BstTrp& x) { auto r = split_by_key(getr(), k); setr(r.first); x.setr(r.second); return *this; }
    int insert(T k) { int r = getr(); int res = insert(r, k, rd()); setr(r); return res; }
    int erase(T k) { int r = getr(); int res = erase(r, k); setr(r); return res; }
    int order_of_key(T k) {
        int x = getr();
        int ans = 0;
        while (x) {
            if (tr[x].k < k) { ans += tr[tr[x].l].size + 1; x = tr[x].r; } 
            else x = tr[x].l;
        }
        return ans;
    }
    int find(T k) {
        int x = getr();
        while (x && tr[x].k != k) {
            if (k < tr[x].k) x = tr[x].l;
            else x = tr[x].r;
        }
        return x;
    }
    int lower_bound(T k) {
        int x = getr(), ans = 0;
        while (x) {
            if (tr[x].k >= k) ans = x, x = tr[x].l;
            else x = tr[x].r;
        }
        return ans;
    }
    int upper_bound(T k) {
        int x = getr(), ans = 0;
        while (x) {
            if (tr[x].k > k) ans = x, x = tr[x].l;
            else x = tr[x].r;
        }
        return ans;
    }
    T lower(T k) {
        T ans = -INF; int x = getr();
        while (x) {
            if (tr[x].k < k) { ans = max(ans, tr[x].k); x = tr[x].r; } 
            else x = tr[x].l;
        }
        return ans;
    }
    T upper(T k) {
        T ans = INF; int x = getr();
        while (x) {
            if (tr[x].k > k) { ans = min(ans, tr[x].k); x = tr[x].l; } 
            else x = tr[x].r;
        }
        return ans;
    }
};

// all need pd
// change need pu (pd !-> pu)
class RgeTrp : public Treap {
    using Treap::Treap;
    using Treap::join;
 private:
    void pd(int now) {
        if (!tr[now].rev) return;
        if (tr[now].l) { tr[now].l = copy(tr[now].l); tr[tr[now].l].mod(); }
        if (tr[now].r) { tr[now].r = copy(tr[now].r); tr[tr[now].r].mod(); }
        tr[now].rev ^= 1;
    }
    void pu(int now) { 
        tr[now].size = 1 + tr[tr[now].l].size + tr[tr[now].r].size; 
        // tr[tr[now].l].f = now, tr[tr[now].r].f = now, tr[now].f = 0;
        // tr[now].m = min({tr[now].k, tr[tr[now].l].m, tr[tr[now].r].m});
        // if (tr[now].l)
        // if (tr[now].r)
    }
    int insert(int &x, int pos, T k, uint32_t v) {
        int y;
        if (!x || tr[x].v > v) {
            y = newnode(k, v);
            tie(tr[y].l, tr[y].r) = split_by_order(x, pos); x = y;
        } else {
            x = copy(x); pd(x);
            if (tr[tr[x].l].size >= pos) y = insert(tr[x].l, pos, k, v);
            else { pos -= tr[tr[x].l].size + 1; y = insert(tr[x].r, pos, k, v); }
        }
        pu(x); return y;
    }
    int erase_pos(int &x, int pos) {
        if (!x) return 0;
        int res = x;
        if (tr[tr[x].l].size == pos) { pd(x); x = join(tr[x].l, tr[x].r); if (x) pu(x); } 
        else {
            x = copy(x); pd(x);
            if (tr[tr[x].l].size > pos) res = erase_pos(tr[x].l, pos);
            else { pos -= tr[tr[x].l].size + 1; res = erase_pos(tr[x].r, pos); }
            if (res) pu(x);
        }
        return res;
    }
    int cover(int &x, int pos, T k) {
        if (!x) return 0;
        int res = x; x = copy(x); pd(x);
        if (tr[tr[x].l].size == pos) { tr[x].k = k; pu(x); } 
        else {
            if (tr[tr[x].l].size > pos) res = cover(tr[x].l, pos, k);
            else { pos -= tr[tr[x].l].size + 1; res = cover(tr[x].r, pos, k); }
            if (res) pu(x);
        }
        return res;
    }

 public:
    RgeTrp() {}
    RgeTrp& join(int x) { setr(join(getr(), x)); return *this; }
    RgeTrp& join(RgeTrp& x) { setr(join(getr(), x.getr())); x.setr(0); return *this; }
    RgeTrp& join(RgeTrp&& x) { setr(join(getr(), x.getr())); return *this; }
    RgeTrp& split(int k) { setr(split_by_order(getr(), k).first); return *this; }
    RgeTrp& split(int k, RgeTrp& x) { auto r = split_by_order(getr(), k); setr(r.first); x.setr(r.second); return *this;}
    int insert(int pos, T k) { int r = getr(); int res = insert(r, pos, k, rd()); setr(r); return res; }
    void insert(int pos, RgeTrp& k) { RgeTrp x; this->split(pos, x).join(k).join(x); }
    void insert(int pos, RgeTrp&& k) { RgeTrp x; this->split(pos, x).join(k).join(x); }
    int erase(int pos) { int r = getr(); int res = erase_pos(r, pos); setr(r); return res; }
    RgeTrp erase(int l, int r) {
        RgeTrp x, y; this->split(l, x);
        x.split(r - l, y); this->join(y);
        return x;
    }
    int cover(int pos, T k) { int r = getr(); int res = cover(r, pos, k); setr(r); return res; }
    void reverse(int l, int r) {
        RgeTrp x, y; this->split(l, x);
        x.split(r - l, y); tr[x.getr()].mod();
        this->join(x).join(y);
    }
    /*
    int order_of_key(int k) {
        int ans = tr[tr[k].l].size;
        while (tr[k].f) {
            if (tr[tr[k].f].r == k) ans += tr[tr[tr[k].f].l].size + 1;
            k = tr[k].f;
        }
        return ans;
    }
    int find_min_order() {
        int x = getr(); pd(x); int ans = tr[tr[x].l].size;
        while (tr[x].m != tr[x].k) {  // || tr[x].m == tr[tr[x].l].m  // leftmost
            if (tr[x].m == tr[tr[x].l].m) { x = tr[x].l; ans -= tr[tr[x].r].size + 1; }
            else { x = tr[x].r; ans += tr[tr[x].l].size + 1; }
            pd(x);
        }
        return ans;
    }
    */
};

// cur = 1;
