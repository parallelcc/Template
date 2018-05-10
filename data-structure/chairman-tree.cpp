#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
using T = int;
struct node {
    int ls, rs;
    T v;
    void mod(T k) {  // mutable
        v += k;
    }
};
const int N = 1e5;
node tr[30 * N];  // 4n + mlogn
int cur = 0;

template <class op = plus<T>>
class PerTree {
 protected:
     int n;
     void bui(const vector<T>& a, int m) {
         n = a.size();
         root.resize(m + 233);
         function<int(int, int)> cre = [&](int l, int r) {
             int now = cur++;
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
     int upd(int now, int x, int l, int r, T tag) {
         tr[cur] = tr[now];
         now = cur++;
         if (l + 1 == r) tr[now].mod(tag);
         else {
             int m = (l + r) >> 1;
             if (x < m) tr[now].ls = upd(tr[now].ls, x, l, m, tag);
             else tr[now].rs = upd(tr[now].rs, x, m, r, tag);
             tr[now].v = op()(tr[tr[now].ls].v, tr[tr[now].rs].v);
         }
         return now;
     }
     T que(int now, int L, int R, int l, int r) {
         if (L == l && R == r) return tr[now].v;
         else {
             int m = (l + r) >> 1;
             if (R <= m) return que(tr[now].ls, L, R, l, m);
             else if (L >= m) return que(tr[now].rs, L, R, m, r);
             else return op()(que(tr[now].ls, L, m, l, m), que(tr[now].rs, m, R, m, r));
         }
     }

 public:
     vector<int> root;
     int tim = 0;
     PerTree() {}
     PerTree(int n, int m) : PerTree(vector<T>(n), m) {}
     PerTree(const vector<T>& a, int m) { bui(a, m); }
     void back(int now) {
         if (now >= tim) return;
         tim = now;
         cur = root[now + 1];
     }
     void upd(int now, int x, T tag) { root[++tim] = upd(root[now], x, 0, n, tag); }
     void upd(int x, T tag) { upd(tim, x, tag); }
     T que(int now, int l, int r) { 
         if (l >= r) return 0;
         return que(root[now], l, r, 0, n); 
     }
     T que(int l, int r) { return que(tim, l, r); }
};

template<typename T>
class ChaTree : public PerTree<> {
    T find_by_order(int L, int R, int l, int r, int k) {
        if (l + 1 == r) return b[l];
        int m = (l + r) >> 1;
        int o = tr[tr[R].ls].v - tr[tr[L].ls].v;
        if (k < o) return find_by_order(tr[L].ls, tr[R].ls, l, m, k);
        else return find_by_order(tr[L].rs, tr[R].rs, m, r, k - o);
    }

 public:
    vector<T> b;
    ChaTree() {}
    ChaTree(const vector<T>& a) {
        b = a;
        sort(b.begin(), b.end());
        b.erase(unique(b.begin(), b.end()), b.end());
        bui(vector<int>(b.size()), a.size());
        for (auto& i : a) {
            int k = lower_bound(b.begin(), b.end(), i) - b.begin();
            upd(k, 1);
        }
    }
    T find_by_order(int l, int r, int k) {
        return find_by_order(root[l], root[r], 0, n, k);
    }
    int order_of_key(int l, int r, T v) {
        int k = lower_bound(b.begin(), b.end(), v) - b.begin();
        return que(r, 0, k) - que(l, 0, k);
    }
};

// cur = 0;
