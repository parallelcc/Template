// Copyright 2017 Parallelc
#include <bits/stdc++.h>
#include <ext/numeric>
using namespace std;
using namespace __gnu_cxx;
template<typename T, class op = plus<T>, class sub = minus<T>>
class BIT {
 private:
     vector<T> tr;
     int lowbit(int x) {return x & (-x);}

 public:
     BIT() {}
     BIT(int n) {
         tr.resize(n + 1);
     }
     BIT(vector<T>& a) {
         int n = a.size();
         tr.resize(n + 1);
         for (int i = 0; i < n; i++) add(i, a[i]);
     }
     void add(int x, T k) {
         x++;
         for (int i = x; i < tr.size(); i += lowbit(i)) {
             tr[i] = op()(tr[i], k);
         }
     }
     T sum(int x) {
         T ans = identity_element(op());
         for (int i = x; i; i -= lowbit(i)) {
             ans = op()(ans, tr[i]);
         }
         return ans;
     }
     T que(int l, int r) {
         return sub()(sum(r), sum(l));
     }
};
