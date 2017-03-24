// Copyright 2017 Parallelc
// o(V*V)
#include <bits/stdc++.h>
using namespace std;  // NOLINT
using LL = int64_t;
using T = int;
const T INF = 0x3f3f3f3f;
T dij(const vector<vector<int>>& lj, int S, int N) {
    int n = lj.size();
    vector<int> us(n), pre(n);
    vector<T> a(n, INF);
    a[S] = 0;
    while (us[N] == 0) {
        T min = INF;
        int mini = S;
        for (int i = 0; i < n; i++) {
            if (us[i] == 0 && min > a[i]) {
                min = a[i];
                mini = i;
            }
        }
        if (min == INF) break;
        us[mini] = 1;
        for (int i = 0; i < n; i++) {
            if (us[i] == 0 && a[i] > a[mini] + lj[mini][i])  {
                a[i] = a[mini] + lj[mini][i];
                pre[i] = mini;
            }
        }
    }
    if (us[N]) {
        function<void(int)> pri = [&](int k)->void {
            if (k != S) pri(pre[k]);
            cout << k;
            if (k != N) cout << ' ';
        };
        pri(N);
    }
    return a[N];
}
