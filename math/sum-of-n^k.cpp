#include <bits/stdc++.h>
using namespace std;

using LL = int64_t;
using LD = long double;
const LL mod = 1e9 + 7;
inline LL mul(LL x, LL y, LL mod) {
    // return x * y % mod;
    return (x * y - (LL)((LD)x / mod * y) * mod) % mod;
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
LL CRT(LL mf, LL af, LL ms, LL as) {
    static LL x = PowMod(mf, ms - 2, ms);
    return (af % mod + mul(mul(((as - af) % ms + ms) % ms, x, ms) % mod, mf % mod, mod)) % mod;
}
class NTT {
  private:
    vector<LL> wn;
    void rader(vector<LL> &y) {
        int len = y.size();
        for (int i = 1, j = len / 2; i < len - 1; i++) {
            if (i < j)
                swap(y[i], y[j]);
            int k = len / 2;
            while (j >= k) {
                j -= k;
                k /= 2;
            }
            if (j < k)
                j += k;
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
    void DFT(vector<LL> &y, int on) {
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
            for (auto &i : y)
                i = mul(i, inv, mod);
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
    if (n == 1)
        return vector<LL>{1};
    else {
        vector<LL> b[2], tmp[2], d[2];
        b[0] = pinv(a, (n + 1) >> 1);
        int len = 1;
        while (len < n << 1)
            len <<= 1;
        b[0].resize(len);
        b[1] = b[0];
        tmp[0].resize(len);
        copy_n(a.begin(), n, tmp[0].begin());
        tmp[1] = tmp[0];
        ntt[0].DFT(b[0], 1);
        ntt[1].DFT(b[1], 1);
        d[0] = ntt[0].conv(b[0], tmp[0]);
        d[1] = ntt[1].conv(b[1], tmp[1]);
        for (int i = 0; i < len; i++)
            tmp[0][i] = CRT(ntt[0].mod, d[0][i], ntt[1].mod, d[1][i]),
            tmp[0][i] = tmp[0][i] ? mod - tmp[0][i] : 0;
        tmp[0][0] = (tmp[0][0] + 2) % mod;
        tmp[1] = tmp[0];
        d[0] = ntt[0].conv(b[0], tmp[0]);
        d[1] = ntt[1].conv(b[1], tmp[1]);
        for (int i = 0; i < len; i++)
            tmp[0][i] = CRT(ntt[0].mod, d[0][i], ntt[1].mod, d[1][i]);
        tmp[0].resize(n);
        return tmp[0];
    }
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
    for (int i = 0; i < k + 1; i++)
        B[i] = B[i] * jc[i] % mod;
    npo.resize(k + 2);
}
inline LL Comb(LL n, LL m) {
    return jc[n] * inv[m] % mod * inv[n - m] % mod;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    init(50000);
    vector<LL> inv(50005);
    inv[1] = 1;
    for(int i = 2; i < 50005; i++)
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    int t;
    cin >> t;
    while (t--) {
        LL n, k;
        cin >> n >> k;
        n %= mod;
        LL ans = 0;
        npo[0] = 1;
        for (int i = 1; i < k + 2; i++) {
            npo[i] = npo[i - 1] * (n + 1) % mod;
            ans += Comb(k + 1, i) * B[k + 1 - i] % mod * npo[i] % mod;
            ans %= mod;
        }
        ans *= inv[k + 1];
        cout << ans % mod << '\n';
    }
}
