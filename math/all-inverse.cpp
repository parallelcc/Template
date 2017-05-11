#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;

vector<LL> inv;
void init(int n, LL mod) {
    inv.resize(n);
    inv[1] = 1;
    for(int i = 2; i < n; i++)
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}
