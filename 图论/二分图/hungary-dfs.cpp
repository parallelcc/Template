// Copyright 2016 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
#define N 1005  // right max
#define M 1005  // left max
int link_edge_num;  // max linked egde number
vector<vector<int> > lj(M);  // from left to right
int link[N];  // right link to left
int used[N];  // record used right point in a dfs
int d;  // current root
bool dfs(int k) {  // find a method that can make k link to right
    for (int i = 0; i < lj[k].size(); i++) {
        if (used[lj[k][i]] != d) {
            used[lj[k][i]] = d;
            if (link[lj[k][i]] == -1 || dfs(link[lj[k][i]])) {
                link[lj[k][i]] = k;  // make or change link
                return true;
            }
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int k, m, n;  // edge, left, right num
    while (cin >> k >> m >> n) {
        // init
        link_edge_num = 0;
        fill(link, link + n + 1, -1);
        fill(used, used + n + 1, -1);
        for (int i = 1; i <= m; i++) lj[i].clear();
        for (int i = 0; i < k; i++) {
            int u, v;
            cin >> u >> v;
            lj[u].push_back(v);
        }
        // main program
        for (d = 1; d <= m; d++) if (dfs(d)) {  // link successfully
            link_edge_num++;
        }
        cout << link_edge_num << '\n';
    }
}
