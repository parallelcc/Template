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
