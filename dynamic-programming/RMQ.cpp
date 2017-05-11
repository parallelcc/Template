#include <bits/stdc++.h>
using namespace std;
template <typename T, class op = less<pair<T, int>>>
struct RMQ {
    vector<vector<pair<T, int>>> dp;
    RMQ() {}
    RMQ(vector<T>& a) {
        int n = a.size();
        int m = __lg(n) + 1;
        dp.resize(n);
        for (int i = 0; i < n; i++) {
            dp[i].resize(m);
            dp[i][0] = {a[i], i};
        }
        for (int j = 1; j < m; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1], op());
            }
        }
    }
    pair<T, int> que(int l, int r) {
        int k = 31 - __builtin_clz(r - l);
        return min(dp[l][k], dp[r - (1 << k)][k], op());
    }
};
