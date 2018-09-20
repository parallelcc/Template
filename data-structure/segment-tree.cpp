#include <bits/stdc++.h>
#include <ext/numeric>
using namespace std;
using namespace __gnu_cxx;
template <typename T, size_t N = 100005, class op = plus<T>>
class SegTree {
 private:
     struct node {
         int l, r;
         T v, lazy = 0;
         node() {}
         node(int l, int r, T v) : l(l), r(r), v(v) {}
     };
     static node tr[4 * N];
     inline void mod(int now, T k) {  // mutable
         tr[now].v += k * (tr[now].r - tr[now].l);
         tr[now].lazy += k;
     }
     inline void pd(int now) {
         if (tr[now].lazy) {
            mod(now * 2 + 1, tr[now].lazy);
            mod(now * 2 + 2, tr[now].lazy);
            tr[now].lazy = 0;
         }
     }

 public:
     SegTree() {}
     SegTree(int n) : SegTree(vector<T>(n, identity_element(op()))) {}
     SegTree(const vector<T>& a) {
         function<void(int, int, int)> cre = [&](int l, int r, int now) {
             if (l + 1 == r) tr[now] = node(l, r, a[l]);
             else {
                 int mid = (l + r) / 2;
                 cre(l, mid, now * 2 + 1);
                 cre(mid, r, now * 2 + 2);
                 tr[now] = node(l, r, op()(tr[now * 2 + 1].v, tr[now * 2 + 2].v));
             }
         };
         cre(0, a.size(), 0);
     }
     void upd(int l, int r, T tag, int now = 0) {
         if (l >= r || tr[now].r <= l || tr[now].l >= r) return;
         else if (tr[now].r <= r && tr[now].l >= l) mod(now, tag);
         else {
             pd(now);
             upd(l, r, tag, now * 2 + 1);
             upd(l, r, tag, now * 2 + 2);
             tr[now].v = op()(tr[now * 2 + 1].v, tr[now * 2 + 2].v);
         }
     }
     T que(int l, int r, int now = 0) {
         if (l >= r || tr[now].r <= l || tr[now].l >= r) return identity_element(op());
         else if (tr[now].r <= r && tr[now].l >= l) return tr[now].v;
         else {
             pd(now);
             return op()(que(l, r, now * 2 + 1), que(l, r, now * 2 + 2));
         }
     }
};
template<typename T, size_t N, class op> struct SegTree<T, N, op>::node SegTree<T, N, op>::tr[4 * N];

const int INF = 0x3f3f3f3f;
template<typename T>
struct Max {
    T operator()(const T& a, const T& b) const { return max(a, b); }
    friend T identity_element(const Max& s) { return -INF; }
};

template<typename T>
struct Min {
    T operator()(const T& a, const T& b) const { return min(a, b); }
    friend T identity_element(const Min& s) { return INF; }
};
