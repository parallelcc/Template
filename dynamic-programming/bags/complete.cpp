#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
template <typename T>
T Complete(vector<T>& val, vector<int>& wei, int w) {
    static vector<T> dp;
    fill(dp.begin(), dp.end(), 0);
    dp.resize(w + 1);
    // fill(dp.begin(), dp.end(), -INF);
    // dp.resize(w + 1, -INF);
    // dp[0] = 0;
    int n = val.size();
    for (int i = 0; i < n; i++) {
        for (int j = wei[i]; j <= w; j++) dp[j] = max(dp[j], dp[j - wei[i]] + val[i]);
    }
    return dp[w];
    // if negative, can't fill fully
}
