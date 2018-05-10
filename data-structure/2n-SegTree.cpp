#include <bits/stdc++.h>
#include <ext/numeric>
using namespace std;
using namespace __gnu_cxx;
template <typename T, class op = plus<T>>
class SegTree {
 private:
     struct node {
         int len;
         T v, lazy = 0;
         node() {}
         node(int len, T v) : len(len), v(v) {}
         void mod(T k) {  // mutable
             v += k * len;
             if (len != 1) lazy += k;
         }
     };
     vector<node> tr;
     int L(int now) { return now + 1; }
     int R(int now) { return now + (tr[now].len & (~1)); }
     void pd(int now) {
         if (!tr[now].lazy) return;
         tr[L(now)].mod(tr[now].lazy);
         tr[R(now)].mod(tr[now].lazy);
         tr[now].lazy = 0;
     }
     void pu(int now) {
         tr[now].v = op()(tr[L(now)].v, tr[R(now)].v);
     }

 public:
     SegTree() {}
     SegTree(int n) : SegTree(vector<T>(n, identity_element(op()))) {}
     SegTree(const vector<T>& a) {
         int n = a.size();
         tr.resize(2 * n);
         function<void(int, int, int)> cre = [&](int l, int r, int now) {
             if (l + 1 == r) tr[now] = node(1, a[l]);
             else {
                 tr[now].len = r - l;
                 int mid = (l + r) / 2;
                 cre(l, mid, L(now));
                 cre(mid, r, R(now));
                 pu(now);
             }
         };
         cre(0, n, 0);
     }
     void upd(int l, int r, T tag, int now = 0) {
         if (l == 0 && r == tr[now].len) tr[now].mod(tag);
         else {
             pd(now);
             int len = tr[now].len / 2;
             if (len >= r) upd(l, r, tag, L(now));
             else if (len <= l) upd(l - len, r - len, tag, R(now));
             else {
                 upd(l, len, tag, L(now));
                 upd(0, r - len, tag, R(now));
             }
             pu(now);
         }
     }
     T que(int l, int r, int now = 0) {
         if (l == 0 && r == tr[now].len) return tr[now].v;
         else {
             pd(now);
             int len = tr[now].len / 2;
             if (len >= r) return que(l, r, L(now));
             else if (len <= l) return que(l - len, r - len, R(now));
             else return op()(que(l, len, L(now)), que(0, r - len, R(now)));
         }
     }
};

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
