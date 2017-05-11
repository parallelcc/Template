#include <bits/stdc++.h>
#include <ext/numeric>
using namespace std;
using namespace __gnu_cxx;
template <typename T, class op = plus<T>>
class SegTree {
 private:
     struct node {
         int l, r;
         T v, lazy = 0;
         node() {}
         node(int l, int r, T v) : l(l), r(r), v(v) {}
         void mod(int k) {  // mutable
             v += k * (r - l);
             lazy += k;
         }
     };
     vector<node> tr;
     void pd(int now) {
         if (!tr[now].lazy) return;
         tr[now * 2 + 1].mod(tr[now].lazy);
         tr[now * 2 + 2].mod(tr[now].lazy);
         tr[now].lazy = 0;
     }

 public:
     SegTree() {}
     SegTree(int n) : SegTree(vector<int>(n)) {}
     SegTree(const vector<T>& a) {
         int n = a.size();
         tr.resize(4 * n);
         function<void(int, int, int)> cre = [&](int l, int r, int now) {
             if (l + 1 == r) tr[now] = node(l, r, a[l]);
             else {
                 int mid = (l + r) / 2;
                 cre(l, mid, now * 2 + 1);
                 cre(mid, r, now * 2 + 2);
                 tr[now] = node(l, r, op()(tr[now * 2 + 1].v, tr[now * 2 + 2].v));
             }
         };
         cre(0, n, 0);
     }
     void upd(int l, int r, T tag, int now = 0) {
         if (tr[now].r <= l || tr[now].l >= r) return;
         else if (tr[now].r <= r && tr[now].l >= l) tr[now].mod(tag);
         else {
             pd(now);
             upd(l, r, tag, now * 2 + 1);
             upd(l, r, tag, now * 2 + 2);
             tr[now].v = op()(tr[now * 2 + 1].v, tr[now * 2 + 2].v);
         }
     }
     T que(int l, int r, int now = 0) {
         if (tr[now].r <= l || tr[now].l >= r) return identity_element(op());
         else if (tr[now].r <= r && tr[now].l >= l) return tr[now].v;
         else {
             pd(now);
             return op()(que(l, r, now * 2 + 1), que(l, r, now * 2 + 2));
         }
     }
};
