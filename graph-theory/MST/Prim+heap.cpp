// Copyright 2017 Parallelc
// o(ElogV) sparse map, from 1 to n
#include <bits/stdc++.h>
using namespace std;  // NOLINT
using LL = int64_t;
using T = int;
const T INF = 0x3f3f3f3f;
struct edge {
    int v;
    T w;
    bool operator<(const edge& e) const {return w > e.w;}
};
T prim(const vector<vector<edge>>& lj) {
    int num = 0, n = lj.size();
    T qz = 0;
    vector<T> a(n, INF);
    a[0] = 0;
    priority_queue<edge> q;
    q.push({0, 0});
    edge mini;
    while (!q.empty() && num < n) {
        do {
            mini = q.top();
            q.pop();
        }while(mini.w > a[mini.v] && !q.empty());
        if (mini.w == a[mini.v]) {
            qz += mini.w;
            num++;
            for (auto& i : lj[mini.v]) {
                if (a[i.v] > i.w) {
                    a[i.v] = i.w;
                    q.push({i.v, i.w});
                }
            }
        }
    }
    if (num == n) return qz;
    else return INF;
}
