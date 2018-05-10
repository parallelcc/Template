#include <bits/stdc++.h>
using namespace std;
int count3cyc(const vector<vector<int>>& lj, const vector<int>& deg) {
    auto cmp = [&](const int &x, const int &y)->bool {
        return deg[x] < deg[y] || (deg[x] == deg[y] && x < y);
    };
    int n = lj.size();
    vector<int> ord(n), vis(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), cmp);
    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        int u = ord[i];
        for(auto &v : lj[u]) if(cmp(u, v)) vis[v] = i + 1;
        for(auto &v : lj[u]) {
            if(!cmp(u, v)) continue;
            for(auto &w : lj[v]) {
                if(!cmp(v, w) || vis[w] != i + 1) continue;
                cnt++;
            }
        }
    }
    return cnt;
}
