#include <bits/stdc++.h>
using namespace std;

using LL = int64_t;
using LD = long double;
const LL mod = 1e9 + 7;
const LL mf = 1231453023109121;
const LL ms = 1337006139375617;
inline LL add(LL x, LL y, LL mod) {
    x += y;
    if (x >= mod) x -= mod;
    return x;
}
inline LL sub(LL x, LL y, LL mod) {
    x -= y;
    if (x < 0) x += mod;
    return x;
}
inline LL mul(LL x, LL y, LL mod) {
    // return x * y % mod;
    LL res = x * y - (LL)((LD)x / mod * y) * mod;
    if (abs(res) >= mod) res %= mod;
    if (res < 0) res += mod;
    return res;
}
LL PowMod(LL a, LL n, LL mod) {
    LL ans = 1;
    while (n) {
        if (n & 1)
            ans = mul(ans, a, mod);
        a = mul(a, a, mod);
        n >>= 1;
    }
    return ans;
}
LL CRT(LL af, LL as) {
    static LL x = PowMod(mf, ms - 2, ms);
    static LL m = mf % mod;
    return add(af % mod, mul(mul(sub(as, af, ms), x, ms) % mod, m, mod), mod);
}
class NTT {
 private:
     vector<LL> wn, inv2;

 public:
     LL mod;
     int g;
     NTT() {}
     NTT(LL mod, int g = 3, int k = 20) : mod(mod), g(g) {
         wn.resize(1 << k);
         wn[0] = 1;
         wn[1] = PowMod(g, (mod - 1) >> k, mod);
         for (int i = 2; i < (1 << k); i++) {
             wn[i] = mul(wn[i - 1], wn[1], mod);
         }
         inv2.resize(k + 1);
         inv2[0] = 1;
         inv2[1] = (mod + 1) >> 1;
         for (int i = 2; i <= k; i++) {
             inv2[i] = mul(inv2[i - 1], inv2[1], mod);
         }
     }
     void DFT(vector<LL> &y, int on) {
         int len = y.size();
         for (int i = 0, j = 0; i < len; i++) {
             if (i > j) swap(y[i], y[j]);
             for (int l = len >> 1; (j ^= l) < l; l >>= 1);
         }
         for (int i = 1, d = 1; d < len; i++, d <<= 1) {
             for (int j = 0; j < len; j += d << 1) {
                 for (int k = 0; k < d; k++) {
                     LL t = mul(wn[(wn.size() >> i) * k], y[j + k + d], mod);
                     y[j + d + k] = sub(y[j + k], t, mod);
                     y[j + k] = add(y[j + k], t, mod);
                 }
             }
         }
         if (on == -1) {
             reverse(y.begin() + 1, y.end());
             LL val = inv2[__lg(len)];
             for (auto &i : y) i = mul(i, val, mod);
         }
     }
     vector<LL> conv(vector<LL> &a, vector<LL> &b) {
         DFT(b, 1);
         vector<LL> c(a.size());
         for (int i = 0; i < a.size(); i++)
             c[i] = mul(a[i], b[i], mod);
         DFT(c, -1);
         return c;
     }
};
NTT ntt[2];
vector<LL> pinv(const vector<LL> &a, int n) {
    vector<LL> tmp[2], b[2], d[2];
    b[0].push_back(1);
    for (int i = 2; (i >> 1) < n; i <<= 1) {
        int len = min(i, n);
        b[0].resize(i << 1);
        b[1] = b[0];
        tmp[0].resize(i << 1);
        copy_n(a.begin(), len, tmp[0].begin());
        tmp[1] = tmp[0];
        ntt[0].DFT(b[0], 1);
        ntt[1].DFT(b[1], 1);
        d[0] = ntt[0].conv(b[0], tmp[0]);
        d[1] = ntt[1].conv(b[1], tmp[1]);
        for (int j = 0; j < (i << 1); j++) {
            tmp[0][j] = CRT(d[0][j], d[1][j]);
            tmp[0][j] = tmp[0][j] ? mod - tmp[0][j] : 0;
        }
        tmp[0][0] = add(tmp[0][0], 2, mod);
        tmp[1] = tmp[0];
        d[0] = ntt[0].conv(b[0], tmp[0]);
        d[1] = ntt[1].conv(b[1], tmp[1]);
        for (int j = 0; j < (i << 1); j++) b[0][j] = CRT(d[0][j], d[1][j]);
        b[0].resize(len);
    }
    return b[0];
}
vector<LL> jc, inv, B, npo;
void init(LL k) {
    jc.resize(k + 2);
    jc[0] = 1;
    for (int i = 1; i < k + 2; i++)
        jc[i] = jc[i - 1] * i % mod;
    inv.resize(k + 2);
    inv[k + 1] = PowMod(jc[k + 1], mod - 2, mod);
    for (int i = k; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % mod;
    ntt[0] = NTT(1231453023109121);
    ntt[1] = NTT(1337006139375617);
    B = pinv(vector<LL>(inv.begin() + 1, inv.end()), k + 1);
    for (int i = 0; i < k + 1; i++) {
        B[i] = B[i] * jc[i] % mod;
    }
    npo.resize(k + 2);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    init(50000);
    int t;
    cin >> t;
    while (t--) {
        LL n, k;
        cin >> n >> k;
        if (n >= mod) n %= mod;
        LL ans = 0;
        npo[0] = 1;
        for (int i = 1; i < k + 2; i++) {
            npo[i] = npo[i - 1] * (n + 1) % mod;
            ans += jc[k + 1] * inv[i] % mod * inv[k + 1 - i] % mod * B[k + 1 - i] % mod * npo[i] % mod;
            if (ans >= mod) ans -= mod;
        }
        ans *= PowMod(k + 1, mod - 2, mod);
        cout << ans % mod << '\n';
    }
}
