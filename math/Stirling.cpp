#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
const LL mod = 1e9 + 7;
const int N = 1005;
LL S[N][N];
// divide i to j circles
void init1() {
    for (int i = 0; i < N; i++) {
        for (int j = 1; j < i; j++) {
            S[i][j] = (i - 1) * S[i - 1][j] % mod + S[i - 1][j - 1];
            if (S[i][j] >= mod) S[i][j] -= mod;
        }
        S[i][i] = 1;
    }
}

// divide i to j sets
void init2() {
    for (int i = 0; i < N; i++) {
        for (int j = 1; j < i; j++) {
            S[i][j] = j * S[i - 1][j] % mod + S[i - 1][j - 1];
            if (S[i][j] >= mod) S[i][j] -= mod;
        }
        S[i][i] = 1;
    }
}
