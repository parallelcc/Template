// Copyright 2017 Parallelc
#include <bits/stdc++.h>
#include <ext/numeric>
using namespace std;
using namespace __gnu_cxx;
template<typename T, class op = plus<T>, class sub = minus<T>>
class BIT {
 private:
     vector<vector<T>> tr;
     T lowbit(T x) { return x & (-x); }

 public:
     BIT() {}
     BIT(int n, int m) {
         tr.resize(n + 1);
         for (auto& i : tr) i.resize(m + 1);
     }
     BIT(vector<vector<T>>& a) {
         int n = a.size();
         int m = a[0].size();
         tr.resize(n + 1);
         for (auto& i : tr) i.resize(m + 1);
         for (int i = 0; i < n; i++) {
             for (int j = 0; j < m; j++) {
                 add(i, j, a[i][j]);
             }
         }
     }
     void add(int x, int y, T k) {
         x++, y++;
         for (int i = x; i < tr.size(); i += lowbit(i)) {
             for (int j = y; j < tr[x].size(); j += lowbit(j)) {
                 tr[i][j] = op()(tr[i][j], k);
             }
         }
     }
     T sum(int x, int y) {
         T ans = identity_element(op());
         for (int i = x; i; i -= lowbit(i)) {
             for (int j = y; j; j -= lowbit(j)) {
                 ans = op()(ans, tr[i][j]);
             }
         }
         return ans;
     }
     T que(int x1, int y1, int x2, int y2) {
         return op()(sub()(sub()(sum(x2, y2), sum(x2, y1)), sum(x1, y2)), sum(x1, y1));
     }
};
