#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
using T = LL;
struct node {
    int ls, rs;
    T v, lazy;
    void mod(int l, int r, T k) {  // mutable
        v += k * (r - l);
        lazy += k;
    }
};
const int N = 1e5;
node tr[30 * N];  // 4n + mlogn
int cur = 0;

template <class op = plus<T>>
class PerTree {
 private:
     int n;
     int pd(int l, int r, int now) {
         if (!tr[now].lazy) return 0;
         tr[cur] = tr[tr[now].ls];
         tr[now].ls = cur++;
         tr[cur] = tr[tr[now].rs];
         tr[now].rs = cur++;
         int m = (l + r) >> 1;
         tr[tr[now].ls].mod(l, m, tr[now].lazy);
         tr[tr[now].rs].mod(m, r, tr[now].lazy);
         tr[now].lazy = 0;
         return 1;
     }
     int upd(int now, int L, int R, int l, int r, T tag, int f) {
         if (f) {
             tr[cur] = tr[now];
             now = cur++;
         } else f = 1;
         if (L == l && R == r) tr[now].mod(l, r, tag);
         else {
             if (pd(l, r, now)) f = 0;
             int m = (l + r) >> 1;
             if (R <= m) tr[now].ls = upd(tr[now].ls, L, R, l, m, tag, f);
             else if (L >= m) tr[now].rs = upd(tr[now].rs, L, R, m, r, tag, f);
             else {
                 tr[now].ls = upd(tr[now].ls, L, m, l, m, tag, f);
                 tr[now].rs = upd(tr[now].rs, m, R, m, r, tag, f);
             }
             tr[now].v = op()(tr[tr[now].ls].v, tr[tr[now].rs].v);
         }
         return now;
     }
     T que(int now, int L, int R, int l, int r) {
         if (L == l && R == r) return tr[now].v;
         else {
             int ls = tr[now].ls, rs = tr[now].rs;
             int m = (l + r) >> 1;
             if (tr[now].lazy) {
                 ls = cur;
                 tr[cur++] = tr[tr[now].ls];
                 rs = cur;
                 tr[cur++] = tr[tr[now].rs];
                 tr[ls].mod(l, m, tr[now].lazy);
                 tr[rs].mod(m, r, tr[now].lazy);
             }
             if (R <= m) return que(ls, L, R, l, m);
             else if (L >= m) return que(rs, L, R, m, r);
             else {
                 return op()(que(ls, L, m, l, m), que(rs, m, R, m, r));
             }
         }
     }

 public:
     vector<int> root;
     int tim = 0;
     PerTree() {}
     PerTree(int n, int m) : PerTree(vector<T>(n), m) {}
     PerTree(const vector<T>& a, int m) : n(a.size()) {
         root.resize(m + 233);
         function<int(int, int)> cre = [&](int l, int r) {
             int now = cur++;
             tr[now].lazy = 0;
             if (l + 1 == r) tr[now].v = a[l];
             else {
                 int m = (l + r) >> 1;
                 tr[now].ls = cre(l, m);
                 tr[now].rs = cre(m, r);
                 tr[now].v = op()(tr[tr[now].ls].v, tr[tr[now].rs].v);
             }
             return now;
         };
         root[0] = cre(0, n);
     }
     void back(int now) {
         if (now >= tim) return;
         tim = now;
         cur = root[now + 1];
     }
     void upd(int now, int l, int r, T tag) {
         if (l >= r) root[++tim] = root[now];
         else root[++tim] = upd(root[now], l, r, 0, n, tag, 1);
     }
     void upd(int l, int r, T tag) { upd(tim, l, r, tag); }
     T que(int now, int l, int r) {
         if (l >= r) return 0;
         int tmp = cur;
         T ans = que(root[now], l, r, 0, n);
         cur = tmp;
         return ans;
     }
     T que(int l, int r) { return que(tim, l, r); }
};
