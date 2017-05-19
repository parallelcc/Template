#include <bits/stdc++.h>
using namespace std;
template <typename T>
int lcs(vector<T>& a, vector<T>& b) {
    int n = a.size();
    int m = b.size();
    static vector<vector<int>> dp;
    dp.resize(n + 1);
    for (auto& i : dp) i.resize(m + 1);
    for (int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
    static vector<T> ans;
    ans.resize(dp[n][m]);
    while (dp[n][m]) {
        if (a[n - 1] == b[m - 1]) {
            ans[dp[n - 1][m - 1]] = a[n - 1];
            n--, m--;
        } else {
            if (dp[n][m] == dp[n - 1][m]) n--;
            else if (dp[n][m] == dp[n][m - 1]) m--;
        }
    }
    return ans;
}
