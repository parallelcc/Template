#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;

LL PowMod(LL a, LL n, LL mod) {
    LL ans = 1;
    while (n) {
        if (n & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}
namespace Cmod {
    vector<LL> jc;
    const LL mod = 1e9 + 7;

    void init(LL n) {
        jc.resize(n);
        jc[0] = 1;
        for (int i = 1; i < n; i++) {
            jc[i] = jc[i - 1] * i % mod;
        }
    }
    LL Comb(LL n, LL m) { 
        return jc[n] * PowMod(jc[m] * jc[n - m] % mod, mod - 2, mod) % mod;
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
