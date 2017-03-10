// Copyright 2017 Parallelc
// o(ElogE) sparse map, from 1 to n
#include <bits/stdc++.h>
using namespace std;  // NOLINT
using LL = int64_t;
class UFA {
 private:
     vector<int> bcj;

 public:
     explicit UFA(int n) {
         bcj.resize(n);
         iota(bcj.begin(), bcj.end(), 0);
     }
     const int gr(int k) {
         if (bcj[k] != k) bcj[k] = gr(bcj[k]);
         return bcj[k];
     }
     void mg(int k1, int k2) {
         int p1 = gr(k1);
         int p2 = gr(k2);
         if (p1 == p2) return;
         bcj[p1] = p2;
     }
};
using T = int;
const T INF = 0x3f3f3f3f;
struct edge {
    int u, v;
    T w;
    bool operator<(const edge& a) const {return w < a.w;}
};
T kruskal(vector<edge>& ed, int n) {
    UFA a(n);
    sort(ed.begin(), ed.end());
    T qz = 0;
    int us_num = 0;
    for (auto& i : ed) {
        if (a.gr(i.u) != a.gr(i.v)) {
            a.mg(i.u, i.v);
            qz += i.w;
            us_num++;
        }
        if (us_num == n - 1) break;
    }
    if (us_num == n - 1) return qz;
    else return INF;
}
