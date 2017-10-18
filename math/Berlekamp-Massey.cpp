#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
const LL mod = 1e9 + 7;
LL PowMod(LL a, LL n) {
    LL ans = 1;
    while (n) {
        if (n & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

vector<LL> BM(const vector<LL>& a) {
    vector<LL> B{1}, C{1};
    int l = 0, m = 1, b = 1;
    for (int n = 0; n < a.size(); n++) {
        LL d = 0;
        for (int i = 0; i <= l; i++) d = (d + C[i] * a[n - i]) % mod;
        if (d == 0) m++;
        else {
            LL c = mod - d * PowMod(b, mod - 2) % mod;
            C.resize(B.size() + m);
            if (2 * l <= n) {
                auto T = C;
                for (int i = 0; i < B.size(); i++) C[i + m] = (C[i + m] + c * B[i]) % mod;
                l = n + 1 - l; B = move(T); b = d; m = 1;
            } else {
                for (int i = 0; i < B.size(); i++) C[i + m] = (C[i + m] + c * B[i]) % mod;
                m++;
            }
        }
    }
    reverse(C.begin(), C.end());
    C.pop_back();
    for (auto& i : C) i = (mod - i) % mod;
    return C;
}

void test(const vector<LL>& a) {
    auto ans = BM(a);
    int n = ans.size();
    vector<LL> b;
    for (int i = 0; i < n; i++) {
        b.push_back(a[i]);
        cout << b[i] << endl;
    }
    for (int i = n; i < 20; i++) {
        LL tmp = 0;
        for (int j = 0; j < n; j++) {
            tmp += b[i - n + j] * ans[j] % mod;
            tmp %= mod;
        }
        b.push_back(tmp);
        cout << tmp << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    test({2,24,96,416,1536,5504,18944,64000,212992,702464});
}
