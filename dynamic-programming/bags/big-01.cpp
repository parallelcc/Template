#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
const LL INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    LL W;
    while (cin >> n >> W) {
        list<pair<LL, LL>> a;
        a.emplace_back(0, 0);
        for (int i = 0; i < n; i++) {
            LL v, w;
            cin >> w >> v;
            if (w > W || v <= 0) continue;
            auto b = a;
            auto s = a.begin();
            for (auto& i : b) {
                i.first += w;
                if (i.first > W) break;
                i.second += v;
                while (s != a.end() && s->first < i.first) s++;
                if (s != a.end()) {
                    if (s->first == i.first) {
                        if (s->second < i.second) s->second = i.second;
                        else continue;
                    } else {
                        if (prev(s)->second < i.second) s = a.insert(s, move(i));
                        else continue;
                    }
                } else {
                    s = a.insert(s, move(i));
                }
                s++;
                while (s != a.end() && s->second <= i.second) s = a.erase(s);
            }
        }
        LL ans = 0;
        for (auto& i : a) ans = max(ans, i.second);
        cout << ans << '\n';
    }
    return 0;
}
