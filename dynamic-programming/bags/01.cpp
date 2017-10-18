#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
template <typename T>
T ZeroOne(vector<T>& val, vector<int>& wei, int w) {
    static vector<T> dp;
    fill(dp.begin(), dp.end(), 0);
    dp.resize(w + 1);
    // fill(dp.begin(), dp.end(), -INF);
    // dp.resize(w + 1, -INF);
    // dp[0] = 0;
    int n = val.size();
    int sum = accumulate(wei.begin(), wei.end(), 0);
    for (int i = 0; i < n; i++) {
        if (i) sum -= wei[i - 1];
        int bound = max(w - sum, wei[i]);
        for (int j = w; j >= bound; j--) dp[j] = max(dp[j], dp[j - wei[i]] + val[i]);
    }
    return dp[w];
    // if negative, can't fill fully
}
