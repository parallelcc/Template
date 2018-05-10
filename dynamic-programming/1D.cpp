#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
using LD = long double;
const LL INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;

using T = LL;
T DD(int n) {
    vector<T> dp(n + 1);
    auto f = [&](int i, int k) {
        return 0;
    };
    auto get = [&](int i, int k) {
        return dp[k] + f(i, k);
    };
    struct node {
        int x, y, k;
    };
    dp[0] = 0;
    dp[1] = get(1, 0);
    deque<node> s;
    s.push_back({1, n + 1, 0});
    for (int i = 1; i < n; i++) {
        while (s.back().x > i && get(s.back().x, s.back().k) >= get(s.back().x, i)) s.pop_back();
        int pre = s.back().k;
        int l = max(i, s.back().x) + 1, r = n + 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (get(mid, pre) < get(mid, i)) l = mid + 1;
            else r = mid;
        }
        s.back().y = r;
        if (r != n + 1) s.push_back({r, n + 1, i});
        while (s.front().y <= i + 1) s.pop_front();
        dp[i + 1] = get(i + 1, s.front().k);
    }
    return dp[n];
}
