// Copyright 2017 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
using T = int;
const T INF = 0x3f3f3f3f;
void floyd(vector<vector<T>>& lj) {
    int n = lj.size();
    vector<vector<T>> dis = lj;
    vector<vector<int>> path(n);
    for (auto& i : path) {
        i.resize(n);
        iota(i.begin(), i.end(), 0);
    }
    for (int k = 0; k < n; k++) {
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
}
