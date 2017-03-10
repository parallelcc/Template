// Copyright 2017 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
template<typename T>
class BIT {
 private:
     vector<T> tr;
     T lowbit(T x) {return x & (-x);}

 public:
     explicit BIT(int n) {
         tr.resize(n + 1);
     }
     void add(int x, T k) {
         while (x < tr.size()) {
             tr[x] += k;
             x += lowbit(x);
         }
     }
     T sum(int x) {
         T ans = 0;
         while (x) {
             ans += tr[x];
             x -= lowbit(x);
         }
         return ans;
     }
};
