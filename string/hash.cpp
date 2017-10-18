#include <bits/stdc++.h>
using namespace std;
using ULL = uint64_t;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int maxn = 50000;
    ULL base = 31;
    vector<ULL> x(maxn + 1);
    x[0] = 1;
    for (int i = 1; i <= maxn; i++) {
        x[i] = x[i - 1] * base;
    }
    auto get = [&] (vector<ULL>& h, int l, int r) {
        return h[r] - h[l] * x[r - l];
    };
    string s;
    cin >> s;
    vector<ULL> h(s.length() + 1);
    for (int i = 1; i < h.size(); i++) {
        h[i] = h[i - 1] * base + s[i - 1] - 'a' + 1;
    }
}
