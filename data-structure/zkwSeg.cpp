#include <bits/stdc++.h>
using namespace std;

template <typename T, class op = plus<T>>
class zkwSeg {
 private:
     int n;
     vector<T> tr;
     void pu(int x) { tr[x] = op()(tr[x << 1], tr[x << 1 | 1]); }

 public:
     zkwSeg() {}
     zkwSeg(int n) : n(n) { tr.resize(2 * n); }
     template <typename S>
     zkwSeg(const vector<S>& a) : zkwSeg(a.size()) {
         for (int i = 0; i < n; i++) tr[n + i] = T(a[i]);
         for (int i = n - 1; i; i--) pu(i);
     }
     void upd(int k, T& x, function<T(T&, T&)> f = plus<T>()) {
         k += n; tr[k] = f(tr[k], x); k >>= 1;
         while (k) pu(k), k >>= 1;
     } 
     T que(int l, int r) {
         T ansl{}, ansr{};
         for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
             if (l & 1) ansl = op()(ansl, tr[l++]);
             if (r & 1) ansr = op()(tr[--r], ansr);
         }
         return op()(ansl, ansr);
     }
};
