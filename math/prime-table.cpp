// Copyright 2016 Parallelc
#include <bits/stdc++.h>
using namespace std; // NOLINT
vector<int> prime, pd;
void db(int n) {
    pd.resize(n);
    prime.reserve(n);
    for (int i = 2; i < n; i++) {
        if (pd[i] == 0) {
            prime.push_back(i);
        }
        for (auto j : prime) {
            if (i * j >= n) break;
            pd[i * j] = 1;
            if (i % j == 0) break;
        }
    }
}
