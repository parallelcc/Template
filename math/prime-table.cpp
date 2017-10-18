// Copyright 2016 Parallelc
#include <bits/stdc++.h>
using namespace std; // NOLINT
using LL = int64_t;
vector<int> prime, pd, u;
void db(int n) {
    pd.resize(n);
    u.resize(n);
    prime.reserve(n);
    u[1] = 1;
    for (int i = 2; i < n; i++) {
        if (pd[i] == 0) {
            prime.push_back(i);
            u[i] = -1;
        }
        for (auto j : prime) {
            if (i * j >= n) break;
            pd[i * j] = 1;
            if (i % j) u[i * j] = -u[i];
            else break;
        }
    }
}

vector<LL> bprime, bpd;
void getprime(LL l, LL r) {
    int n = r - l;
    bpd.clear();
    bprime.clear();
    bpd.resize(n);
    bprime.reserve(n);
    for (LL i : prime) {
        if (i * i >= r) break;
        LL s = l / i + !!(l % i);
        for (LL j = max(2LL, s); j * i < r; j++) bpd[j * i - l] = 1;
    }
    if (l < 2) for (int i = l; i < 2; i++) bpd[i] = 1;
    for (int i = 0; i < n; i++) if (!bpd[i]) bprime.push_back(l + i);
}
