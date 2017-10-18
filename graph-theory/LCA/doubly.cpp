#include <bits/stdc++.h>
using namespace std;
using T = int;
struct node {
    int v;
    T w;
};
struct LCA {
    vector<int> dep;
    vector<vector<int>> fa;
    vector<T> dis;
    LCA(vector<vector<node>>& lj, int r) {
        int n = lj.size();
        int m = log2(n) + 1;
        fa.resize(n);
        for (auto& i : fa) i.resize(m);
        dep.resize(n);
        dis.resize(n);
        function<void(int, int)> dfs = [&](int k, int pre) {
            fa[k][0] = pre;
            dep[k] = dep[pre] + 1;
            for (auto& i : lj[k]) {
                if (i.v != pre) {
                    dis[i.v] = dis[k] + i.w;
                    dfs(i.v, k);
                }
            }
        };
        dfs(r, r);
        for (int j = 1; j < m; j++) {
            for (int i = 0; i < n; i++) {
                fa[i][j] = fa[fa[i][j - 1]][j - 1];
            }
        }
    }
    int que(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = log2(dep[u]); i >= 0; i--) {
            if (dep[u] - (1 << i) >= dep[v]) u = fa[u][i];
        }
        if (u == v) return u;
        for (int i = log2(dep[u]); i >= 0; i--) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    }
};
