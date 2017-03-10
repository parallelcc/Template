// Copyright 2017 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
template<typename T>
class BIT {
 private:
     vector<vector<T>> tr;
     T lowbit(T x) {return x & (-x);}

 public:
     explicit BIT(int n, int m) {
         tr.resize(n + 1);
         for (auto& i : tr) i.resize(m + 1);
     }
     void add(int x, int y, T k) {
         while (x < tr.size()) {
             int tmp = y;
             while (tmp < tr[x].size()) {
                tr[x][tmp] += k;
                tmp += lowbit(tmp);
             }
             x += lowbit(x);
         }
     }
     T sum(int x, int y) {
         T ans = 0;
         while (x) {
             int tmp = y;
             while (tmp) {
                ans += tr[x][tmp];
                tmp -= lowbit(tmp);
             }
             x -= lowbit(x);
         }
         return ans;
     }
};
