#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
using LD = long double;

inline LL mul(LL x, LL y, LL mod) {
    return x * y % mod;
    // return (x * y - (LL)((LD)x / mod * y) * mod) % mod;
}
LL PowMod(LL a, LL n, LL mod) {
    LL ans = 1;
    while (n) {
        if (n & 1) ans = mul(ans, a, mod);
        a = mul(a, a, mod);
        n >>= 1;
    }
    return ans;
}
using T = LL;
T exgcd(T a, T b, T& x, T& y) {  // a solution of ax + by = gcd(a, b)
    if (b == 0) return x = 1, y = 0, a;
    T d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
T inv(T a, T mod) {  // ax = 1(mod p)
    T x, y;
    T d = exgcd(a, mod, x, y);
    if (d == 1) return (x % mod + mod) % mod;
    else return -1;
}

class NTT {
 private:
     vector<LL> wn;
     void rader(vector<LL>& y) {
         int len = y.size();
         for (int i = 1, j = len / 2; i < len - 1; i++) {
             if (i < j) swap(y[i], y[j]);
             int k = len / 2;
             while (j >= k) {
                 j -= k;
                 k /= 2;
             }
             if (j < k) j += k;
         }
     }

 public:
     LL mod;
     int g;
     NTT() {}
     NTT(LL mod, int g = 3, int k = 20) : mod(mod), g(g) {
         wn.resize(k);
         for (int i = 1; i < k; i++) {
             int t = 1 << i;
             wn[i] = PowMod(g, (mod - 1) / t, mod);
         }
     }
     void DFT(vector<LL>& y, int on) {
         int len = y.size();
         rader(y);
         for (int h = 2, i = 1; h <= len; h <<= 1, i++) {
             for (int j = 0; j < len; j += h) {
                 LL w = 1;
                 for (int k = j; k < j + h / 2; k++) {
                     LL u = y[k];
                     LL t = mul(w, y[k + h / 2], mod);
                     y[k] = (u + t) % mod;
                     y[k + h / 2] = (u - t + mod) % mod;
                     w = mul(w, wn[i], mod);
                 }
             }
         }
         if (on == -1) {
             reverse(y.begin() + 1, y.end());
             LL inv = PowMod(len, mod - 2, mod);
             for (auto& i : y) i = mul(i, inv, mod);
         }
     }
     void conv(vector<LL>& a, vector<LL>& b) {
         int n = 1, m = a.size() + b.size() - 1;
         while (n < m) n <<= 1;
         a.resize(n), b.resize(n);
         DFT(a, 1);
         DFT(b, 1);
         for (int i = 0; i < n; i++) a[i] = mul(a[i], b[i], mod);
         DFT(a, -1);
         a.resize(m);
     }
     void conv2(vector<LL>& a, vector<LL>& b) {
         int n = max(a.size(), b.size());
         a.resize(n), b.resize(n);
         reverse(b.begin(), b.end());
         conv(a, b);
         for (int i = 0; i < n - 1; i++) a[i] += a[i + n];
         a.resize(n);
         reverse(a.begin(), a.end());
     }
     vector<LL> pinv(vector<LL>& a, int n, LL P) {  // ax = 1 (mod x^n)(mod P)
         LL k = inv(a[0], P);
         if (k == -1) return vector<LL>();
         function<vector<LL>(int)> inv;
         if (P == mod) {
             inv = [&](size_t n) {
                 if (n == 1) return vector<LL>{k};
                 else {
                     auto b = inv((n + 1) >> 1);
                     int len = 1;
                     while (len < n << 1) len <<= 1;
                     b.resize(len);
                     vector<LL> tmp(len);
                     copy_n(a.begin(), min(n, a.size()), tmp.begin());
                     DFT(b, 1);
                     DFT(tmp, 1);
                     for (int i = 0; i < len; i++) b[i] = mul(b[i], ((2 - mul(b[i], tmp[i], mod)) % mod + mod) % mod, mod);
                     DFT(b, -1);
                     b.resize(n);
                     return b;
                 }
             };
         } else {
             inv = [&](size_t n) {
                 if (n == 1) return vector<LL>{k};
                 else {
                     auto b = inv((n + 1) >> 1);
                     int len = 1;
                     while (len < n << 1) len <<= 1;
                     b.resize(len);
                     vector<LL> tmp(len);
                     copy_n(a.begin(), min(n, a.size()), tmp.begin());
                     DFT(b, 1);
                     DFT(tmp, 1);
                     for (int i = 0; i < len; i++) tmp[i] = mul(b[i], tmp[i], mod);
                     DFT(tmp, -1);
                     for (int i = 0; i < len; i++) {
                         tmp[i] = (tmp[i] % P + P) % P;
                         if (tmp[i]) tmp[i] = P - tmp[i];
                     }
                     tmp[0] = (tmp[0] + 2) % P;
                     DFT(tmp, 1);
                     for (int i = 0; i < len; i++) b[i] = mul(b[i], tmp[i], mod);
                     DFT(b, -1);
                     for (int i = 0; i < len; i++) b[i] = (b[i] % P + P) % P;
                     b.resize(n);
                     return b;
                 }
             };
         }
         return inv(n);
     }
     bool div(vector<LL>& a, vector<LL>& b, LL mod) {
         if (a.size() < b.size()) {
             b = move(a);
             return true;
         }
         int n = a.size() - b.size() + 1;
         int m = b.size();
         vector<LL> c(a.rbegin(), a.rbegin() + n), d(b.rbegin(), b.rend());
         d = pinv(d, n, mod);
         if (d.empty()) return false;
         conv(c, d);
         c.resize(n);
         reverse(c.begin(), c.end());
         conv(b, c);
         b.resize(m);
         for (int i = 0; i < m; i++) b[i] = ((a[i] - b[i]) % mod + mod) % mod;
         DFT(c, -1);
         c.resize(n);
         a = move(c);
         return true;
     }
};

/*
 * 2281701377 = 17 * 2 ^ 27 + 1 平方刚好不会爆 long long
 * 1004535809 = 479 * 2 ^ 21 + 1 加起来刚好不会爆int
 * 998244353 = 119 * 2 ^ 23 + 1
 * g均为3

 * mod                 r   k   g
 * 3                   1   1   2
 * 5                   1   2   2
 * 17                  1   4   3
 * 97                  3   5   5
 * 193                 3   6   5
 * 257                 1   8   3
 * 7681                15  9   17
 * 12289               3   12  11
 * 40961               5   13  3
 * 65537               1   16  3
 * 786433              3   18  10
 * 5767169             11  19  3
 * 7340033             7   20  3
 * 23068673            11  21  3
 * 104857601           25  22  3
 * 167772161           5   25  3
 * 469762049           7   26  3
 * 998244353           119 23  3
 * 1004535809          479 21  3
 * 2013265921          15  27  31
 * 2281701377          17  27  3
 * 3221225473          3   30  5
 * 75161927681         35  31  3
 * 77309411329         9   33  7
 * 206158430209        3   36  22
 * 2061584302081       15  37  7
 * 2748779069441       5   39  3
 * 6597069766657       3   41  5
 * 39582418599937      9   42  5
 * 79164837199873      9   43  5
 * 263882790666241     15  44  7
 * 1231453023109121    35  45  3
 * 1337006139375617    19  46  3
 * 3799912185593857    27  47  5
 * 4222124650659841    15  48  19
 * 7881299347898369    7   50  6
 * 31525197391593473   7   52  3
 * 180143985094819841  5   55  6
 * 1945555039024054273 27  56  5
 * 4179340454199820289 29  57  3
 */
