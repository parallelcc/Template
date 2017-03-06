// Copyright 2017 Parallelc
// o(ElogV) sparse map, from 1 to n
#include <bits/stdc++.h>
using namespace std;  // NOLINT
using LL = int64_t;
using T = int;
const T INF = 0x3f3f3f3f;
struct edge {
    int num;
    T wei;
    bool operator<(const edge& a) const {return wei > a.wei;}
};
T prim(const vector<vector<edge> >& lj) {
    vector<int> us(lj.size());
    T qz = 0;
    int us_num = 0, n = lj.size() - 1;
    vector<T> a(n + 1, INF);
    a[1] = 0;
    priority_queue<edge> q;
    q.push({1, 0});
    edge mini;
    while (!q.empty() && us_num < n) {
        do {
            mini = q.top();
            q.pop();
        }while(us[mini.num] == 1 && !q.empty());
        if (us[mini.num] == 0) {
            qz += mini.wei;
            us[mini.num] = 1;
            us_num++;
            for (auto& i : lj[mini.num]) {
                if (us[i.num] == 0) {
                    if (a[i.num] > i.wei) {
                        a[i.num] = i.wei;
                        q.push({i.num, i.wei});
                    }
                }
            }
        }
    }
    if (us_num == n) return qz;
    else return INF;
}
