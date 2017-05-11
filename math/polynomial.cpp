#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
using LD = long double;

inline LL mul(LL x, LL y, LL mod) {
    return x * y % mod;
    // return (x * y - (LL)((LD)x / mod * y + 1e-3) * mod + mod) % mod;
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
LL inv(LL a, LL mod) {return PowMod(a, mod - 2, mod);}

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
     vector<LL> conv(vector<LL>& a, vector<LL>& b) {
         int n = 1;
         while (n < a.size() + b.size() - 1) n <<= 1;
         vector<LL> c, d;
         c.reserve(n), d.reserve(n);
         for (auto& i : a) c.push_back(i % mod);
         for (auto& i : b) d.push_back(i % mod);
         c.resize(n), d.resize(n);
         DFT(c, 1);
         DFT(d, 1);
         for (int i = 0; i < n; i++) c[i] = mul(c[i], d[i], mod);
         DFT(c, -1);
         return c;
     }
     vector<LL> pinv(vector<LL>& a, int n, LL P) {  // ax = 1 (mod x^n)(mod P)
         if (n == 1) return vector<LL>{inv(a[0], mod)};
         else {
             auto b = pinv(a, (n + 1) >> 1, P);
             int len = 1;
             while (len < n << 1) len <<= 1;
             b.resize(len);
             vector<LL> tmp(len);
             copy_n(a.begin(), n, tmp.begin());
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
     }
};
