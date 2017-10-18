//1e11 1500ms 6000k O(n^(3/4))
#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
LL countp(LL k){
    vector<LL> f(340000), g(340000);
    LL m;
    for (m = 1; m * m <= k; m++) f[m] = k / m - 1;
    iota(g.begin() + 1, g.begin() + m + 1, 0);
    for (LL i = 2; i <= m; i++){
        if (g[i] == g[i - 1]) continue;
        for (LL j = 1; j <= min(m - 1, k / i / i); j++) {
            if (i * j < m) f[j] -= f[i * j] - g[i - 1];
            else f[j] -= g[k / i / j] - g[i - 1];
        }
        for (LL j = m; j >= i * i; j--) g[j] -= g[j / i] - g[i - 1];
    }
    return f[1];
}
