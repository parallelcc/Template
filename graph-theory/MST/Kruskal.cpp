// Copyright 2017 Parallelc
// o(ElogE) sparse map, from 1 to n
#include <bits/stdc++.h>
using namespace std;  // NOLINT
using LL = int64_t;
using T = int;
const T INF = 0x3f3f3f3f;

vector<int> bcj;
int gr(int k) {
    return k == bcj[k]?k:bcj[k] = gr(bcj[k]);
}

struct edge {
    int u, v;
    T w;
    bool operator<(const edge& a) const {return w < a.w;}
};
T kruskal(vector<edge>& ed, int n) {
    bcj.resize(n);
    iota(bcj.begin(), bcj.end(), 0);
    sort(ed.begin(), ed.end());
    T qz = 0;
    int us_num = 0;
    for (auto& i : ed) {
        if (gr(i.u) != gr(i.v)) {
            bcj[gr(i.u)] = gr(i.v);
            qz += i.w;
            us_num++;
        }
        if (us_num == n - 1) break;
    }
    if (us_num == n - 1) return qz;
    else return INF;
}
