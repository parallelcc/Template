#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
const LL mod = 1e9 + 7;

LL linear(const vector<LL>& a, const vector<LL>& b, LL n) {  // b[k + 1] = a[0] * b[0] + ... + a[k - 1] * b[k - 1];
    int k = a.size();
    vector<LL> d, res(k), base(k);
    for (int i = 0; i < k; i++) if (a[i]) d.push_back(i);
    res[0] = 1;
    int p = 0;
    while ((1LL << p) <= n) p++;
    for (; p >= 0; p--) {
        vector<LL> c(2 * k);
        for (int i = 0; i < k; i++) {
            if (res[i]) for (int j = 0; j < k; j++) {
                c[i + j] += res[i] * res[j] % mod;
                if (c[i + j] >= mod) c[i + j] -= mod;
            }
        }
        for (int i = 2 * k - 1; i >= k; i--) {
            if (c[i]) for (auto j : d) {
                c[i - k + j] += c[i] * a[j] % mod;
                if (c[i - k + j] >= mod) c[i - k + j] -= mod;
            }
        }
        c.resize(k);
        res = move(c);
        if ((n >> p) & 1) {
            LL tmp = res.back();
            for (int i = k - 1; i > 0; i--) res[i] = res[i - 1];
            res[0] = 0;
            for (auto i : d) {
                res[i] += tmp * a[i] % mod;
                if (res[i] >= mod) res[i] -= mod;
            }
        }
    }
    LL ans = 0;
    for (int i = 0; i < k; i++) {
        ans += res[i] * b[i] % mod;
        if (ans >= mod) ans -= mod;
    }
    return ans;
}
