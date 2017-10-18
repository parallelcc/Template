// Copyright 2017 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
using LL = int64_t;
using T = LL;
const T INF = 0x3f3f3f3f;
T floyd(vector<vector<T>>& lj) { // notice: lj[i][i] = 0
    int n = lj.size();
    vector<vector<T>> dis = lj;
    vector<vector<int>> path(n);
    for (auto& i : path) {
        i.resize(n);
        iota(i.begin(), i.end(), 0);
    }
    T ans = INF;
    tuple<int, int, int> pash;
    for (int k = 0; k < n; k++) {
        // min circle
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < i; j++) {
                if (ans > dis[i][j] + lj[i][k] + lj[k][j]) {
                    ans = dis[i][j] + lj[i][k] + lj[k][j];
                    pash = {i, j, k};
                }
            }
        }
        // short path
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dis[i][k] + dis[k][j] < dis[i][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }
    auto print = [&](int u, int v) {
        while (u != v) {
            cout << u << ' ';
            u = path[u][v];
        }
        cout << v << '\n';
    };
    // cout << get<2>(pash) << ' ';
    // print(get<0>(pash), get<1>(pash));
    return ans;
}
