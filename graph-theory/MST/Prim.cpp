// Copyright 2017 Parallelc
// o(V*V) dense map, from 1 to n
#include <bits/stdc++.h>
using namespace std;  // NOLINT
using LL = int64_t;
using T = int;
const T INF = 0x3f3f3f3f;
T prim(const vector<vector<T> >& lj) {
    vector<int> us(lj.size());
    T qz = 0;
    int us_num = 0, n = lj.size() - 1;
    vector<T> a(n + 1, INF);
    a[1] = 0;
    while (us_num < n) {
        T minz = INF;
        int mini = 1;
        for (int i = 1; i <= n; i++) {
            if (us[i] == 0 && minz > a[i]) {
                minz = a[i];
                mini = i;
            }
        }
        if (minz == INF) break;
        us[mini] = 1;
        qz += minz;
        us_num++;
        for (int i = 1; i <= n; i++) {
            if (us[i] == 0 && a[i] > lj[mini][i]) {
                a[i] = lj[mini][i];
            }
        }
    }
    if (us_num == n) return qz;
    else return INF;
}
