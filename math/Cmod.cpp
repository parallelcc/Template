#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;

namespace Cmod {
    const LL mod = 1e9 + 7;
    vector<LL> fac, finv;

    void init(int n) {
        fac.resize(n);
        finv.resize(n);
        fac[0] = 1;
        for (int i = 1; i < n; i++) {
            fac[i] = fac[i - 1] * i % mod;
        }
        finv[1] = 1;
        for (int i = 2; i < n; i++) {
            finv[i] = finv[mod % i] * (mod - mod / i) % mod;
        }
        finv[0] = 1;
        for (int i = 1; i < n; i++) {
            finv[i] = finv[i - 1] * finv[i] % mod;
        }
    }
    LL Comb(LL n, LL m) { 
        return fac[n] * finv[m] % mod * finv[n - m] % mod;
    }

    LL Lucas(LL n, LL m) {
        LL ans = 1;
        while (n && m) {
            if (n < m) return 0;
            ans = (ans * Comb(n % mod, m % mod)) % mod;
            n /= mod;
            m /= mod;
        }
        return ans;
    }
}
