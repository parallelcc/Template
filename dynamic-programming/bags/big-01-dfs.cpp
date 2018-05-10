#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
const LL INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;

struct bag {
    LL w, v;
    double r;
    bool operator<(const bag& e) const {
        if (r == e.r) return w > e.w;
        return r > e.r;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    LL W;
    while (cin >> n >> W) {
        vector<bag> bags;
        for (int i = 0; i < n; i++) {
            LL w, v;
            cin >> w >> v;
            if (w > W || v <= 0) continue;
            double r = (double)v / w;
            bags.push_back({w, v, r});
        }
        n = bags.size();
        sort(bags.begin(), bags.end());
        LL ans = 0;
        auto check = [&](int x, LL nw, LL nv) {
            for (int j = x; j < n && nw < W; j++) {
                if (bags[j].w + nw <= W) nw += bags[j].w, nv += bags[j].v;
                else nv += bags[j].r * (W - nw), nw = W;
            }
            return nv > ans;
        };
        function<void(int, LL, LL)> solve = [&](int x, LL nw, LL nv) {
            if (x == n) ans = max(ans, nv);
            else if (check(x, nw, nv)) {
                if (nw + bags[x].w <= W) solve(x + 1, nw + bags[x].w, nv + bags[x].v);
                solve(x + 1, nw, nv);
            }
        };
        solve(0, 0, 0);
        cout << ans << '\n';
    }
    return 0;
}
