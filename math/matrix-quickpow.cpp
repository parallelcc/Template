// Copyright 2017 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
using LL = int64_t;
const LL mod = 1e9 + 7;

struct Mat {
    int n;
    static const int N = 3;
    LL val[N][N] = {{0}};
    Mat(int n, int op = 0) : n(n) {
        if (op) {
            for (int i = 0; i < n; i++) val[i][i] = 1;
        }
    }
    friend const Mat operator+ (const Mat& t, const Mat& s) {
        auto ans = t;
        for (int i = 0; i < ans.n; i++) {
            for (int j = 0; j < ans.n; j++) {
                ans.val[i][j] += s.val[i][j];
                if (ans.val[i][j] >= mod) ans.val[i][j] -= mod;
            }
        }
        return ans;
    }
    friend const Mat operator* (const Mat& t, const Mat& s) {
        Mat ans(t.n);
        for (int i = 0; i < ans.n; i++) {
            for (int k = 0; k < ans.n; k++) {
                if (t.val[i][k]) {
                    for (int j = 0; j < ans.n; j++) {
                        ans.val[i][j] += t.val[i][k] * s.val[k][j] % mod;
                        if (ans.val[i][j] >= mod) ans.val[i][j] -= mod;
                    }
                }
            }
        }
        return ans;
    }
};

Mat PowMod(Mat a, LL n) {
    Mat ans(a.n, 1);
    while(n) {
        if(n & 1) ans = ans * a;
        a = a * a;
        n >>= 1;
    }
    return ans;
} 

Mat PowSumMod(Mat& a, LL n) {// return (a+ a^2 + ... + a^n) Mod p;
    Mat ans(a.n, 1);
    if(n == 1) return a;
    if (n % 2 == 0)
        return (ans + PowMod(a, n / 2)) * PowSumMod(a, n / 2);
    else
        return (ans + PowMod(a, (n - 1) / 2)) * PowSumMod(a, (n - 1) / 2) +
            PowMod(a, n);
}
